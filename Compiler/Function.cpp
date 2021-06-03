#include "ASTNodes.h"

extern LLVMContext context;
extern IRBuilder<> builder;
extern std::shared_ptr<Module> module;
extern std::string now_function;

extern int stage;
extern std::map<std::string, Type*> type_map;// TypeName -> Type Pointer <Global>
extern std::map<Type*, std::string> name_map;// Type -> TypeName Pointer <Global>
extern std::map<Type*, Constant*> zero_initial;// Type -> zeroinitial <Global>

extern std::map<std::string, Value*> table_mem[MAX_NESTED];// VarName -> Memory <Region>
extern std::map<std::string, Type*> table_type[MAX_NESTED];// VarName -> Type <Region>
extern std::map<std::string, bool> table_array[MAX_NESTED];// VarName -> Array <Region>

extern std::map<Type*, std::vector<Type*> > record_type_list;// StructType -> Member_Type_List <global>
extern std::map<Type*, std::vector<std::string> > record_member_name_list;// StructType -> Member_Name_List <global>
extern std::map<Type*, std::vector<bool> > record_member_array;// StructType -> Member_Name_List <global>
extern std::map<Function*, std::vector<bool> > function_var_arg;// Function* -> Var args array

Type* get_pointer(Type* _type)
{
    if (_type == IntType){
        return Type::getInt16PtrTy(context);
    } else if (_type == CharType){
        return Type::getInt8PtrTy(context);
    } else if (_type == BoolType){
        return Type::getInt1PtrTy(context);
    } else if (_type == RealType){
        return Type::getFloatPtrTy(context);
    } else {
        throw new IRBuilderMeesage("[IRBuilder] Error : Cant Get the Pointer Type");
    }
}


Type* get_data(Type* _type)
{
    if (_type == Type::getInt16PtrTy(context)){
        return IntType;
    } else if (_type == Type::getInt8PtrTy(context)){
        return CharType;
    } else if (_type == Type::getInt1PtrTy(context)){
        return BoolType;
    } else if (_type == Type::getFloatPtrTy(context)){
        return RealType;
    } else {
        throw new IRBuilderMeesage("[IRBuilder] Error : Cant Get the Pointer Type");
    }
}

ASTNodes::CodeGenResult* ASTNodes::FunDeclareNode::code_gen(){
    if (module->getFunction(this->function_name) != nullptr){
        throw new IRBuilderMeesage("[IRBuilder] Error : re-Define the Function <"+this->function_name+">");
    } else {
        // printf("Before Declare\n");
        std::vector<Type*> param_list;
        for (int i=0; i<this->function_arg_types_names.size(); ++i){
            if (this->function_arg_var[i]){
                param_list.push_back(get_pointer(type_map[this->function_arg_types_names[i]]));
            } else {
                param_list.push_back(type_map[this->function_arg_types_names[i]]);
            }
        }

        FunctionType* func_type = FunctionType::get(type_map[this->ret_type_name], param_list, false);
        Function* func_pointer = Function::Create(func_type, Function::ExternalLinkage, this->function_name, module.get());
        function_var_arg[func_pointer] = this->function_arg_var;
        unsigned idx = 0;
        for (auto &arg: func_pointer->args())
            arg.setName(this->function_arg_names[idx++]);
        // printf("End Declare\n");
        return nullptr;
    }
}

std::string ASTNodes::FunctionNode::get_name(){
    return this->func_declare->function_name;
}

ASTNodes::CodeGenResult* ASTNodes::FunctionNode::code_gen(){
    this->func_declare->code_gen();
    std::string func_name = this->get_name();
    now_function = func_name;
    this->func_body->code_gen();
    return nullptr;
}

ASTNodes::CodeGenResult* ASTNodes::ReturnNode::code_gen(){
    if (now_function == "main"){
        builder.CreateRet(builder.getInt16(0));
    } else {
        if (builder.getCurrentFunctionReturnType()==builder.getVoidTy()){
            builder.CreateRetVoid();
        } else {
            VarBaseNode* ret_val = new VarBaseNode(now_function, nullptr, nullptr);
            builder.CreateRet(ret_val->code_gen()->get_value());
        }
    }
    return nullptr;
}

ASTNodes::CodeGenResult* ASTNodes::FunctionBodyNode::code_gen(){
    stage++;
    table_mem[stage].clear();
    table_type[stage].clear();
    table_array[stage].clear();
    Function* func_pointer = module->getFunction(now_function);
    BasicBlock* func_block = BasicBlock::Create(context, "", func_pointer);
    builder.SetInsertPoint(func_block);
    
    auto arg_it = func_pointer->arg_begin();
    // printf("Build Initial\n");
    for (int i=0; i<function_var_arg[func_pointer].size(); ++i){
        auto arg = arg_it++;
        std::string _name = arg->getName();
        Type* _type = arg->getType();
        if (function_var_arg[func_pointer][i]){
            // std::cout << "name is "<<_name << std::endl;
            table_mem[stage][_name] = arg;
            table_type[stage][_name] = get_data(arg->getType());
            table_array[stage][_name] = false;
        } else {
            // Value* _mem = builder.CreateIntToPtr(arg, arg->getType());
            VariableDefineNode * arg_define = new VariableDefineNode(name_map[_type], false, 0, _name);
            arg_define->code_gen();
            VarBaseNode * arg_position = new VarBaseNode(_name, nullptr, nullptr);
            auto temp_mem = arg_position->code_gen()->mem;
            builder.CreateStore(arg, temp_mem);
        }
    }
    // printf("End Initial\n");

    if (func_pointer->getReturnType() != VoidType){
        VariableDefineNode * arg_define = new VariableDefineNode(
            name_map[func_pointer->getFunctionType()->getReturnType()], false, 0, now_function
        );
        arg_define->code_gen();
    }

    for (auto stmt: this->stmts){
        // printf("Find a Node\n");
        stmt->code_gen();
        // printf("Find another Node\n");
    }

    stage--;
    return nullptr;
}

ASTNodes::CodeGenResult* ASTNodes::FunctionCallNode::code_gen(){
    std::vector <Value*> arg_val;
    arg_val.clear();
    Function* func = module->getFunction(this->func_name);
    for (int i=0; i<this->args.size(); ++i){
        if (function_var_arg[func][i]){
            // printf("Enter a memory\n");
            arg_val.push_back(this->args[i]->code_gen()->mem);
            // printf("Exit a memory\n");
        } else {
            arg_val.push_back(this->args[i]->code_gen()->get_value());
        }
    }
        
    if (func == nullptr){
        throw new IRBuilderMeesage("[IRBuilder] Error : Cant Find the Function <"+this->func_name+">");
    }
    ArrayRef<Value*> arg_ref(arg_val);
    if (func->getReturnType()!=VoidType){
        Value* ret = builder.CreateCall(func, arg_ref);
        return new CodeGenResult(nullptr, ret->getType(), ret);
    }
    else{
        builder.CreateCall(func, arg_ref);
        return new CodeGenResult(nullptr, nullptr, nullptr);
    }
}