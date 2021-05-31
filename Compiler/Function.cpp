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

ASTNodes::CodeGenResult* ASTNodes::FunDeclareNode::code_gen(){
    if (module->getFunction(this->function_name) != nullptr){
        throw new IRBuilderMeesage("[IRBuilder] Error : re-Define the Function <"+this->function_name+">");
    } else {
        std::vector<Type*> param_list;
        for (auto param_type_name:this->function_arg_types_names)
            param_list.push_back(type_map[param_type_name]);
        FunctionType* func_type = FunctionType::get(type_map[this->ret_type_name], param_list, false);
        Function* func_pointer = Function::Create(func_type, Function::ExternalLinkage, this->function_name, module.get());
        unsigned idx = 0;
        for (auto &arg: func_pointer->args())
            arg.setName(this->function_arg_names[idx++]);
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
    while (arg_it!=func_pointer->arg_end()){
        auto arg = arg_it++;
        std::string _name = arg->getName();
        Type* _type = arg->getType();
        Value* _mem = builder.CreateIntToPtr(arg, arg->getType());
        VariableDefineNode * arg_define = new VariableDefineNode(name_map[_type], false, 0, _name);
        arg_define->code_gen();
        VarBaseNode * arg_position = new VarBaseNode(_name, nullptr, nullptr);
        auto temp_mem = arg_position->code_gen()->mem;
        builder.CreateStore(arg, temp_mem);
    }

    if (func_pointer->getReturnType() != VoidType){
        VariableDefineNode * arg_define = new VariableDefineNode(
            name_map[func_pointer->getFunctionType()->getReturnType()], false, 0, now_function
        );
        arg_define->code_gen();
    }

    for (auto stmt: this->stmts){
        stmt->code_gen();
    }

    stage--;
    return nullptr;
}

ASTNodes::CodeGenResult* ASTNodes::FunctionCallNode::code_gen(){
    std::vector <Value*> arg_val;
    arg_val.clear();
    for (auto arg_node:this->args)
        arg_val.push_back(arg_node->code_gen()->get_value());
    Function* func = module->getFunction(this->func_name);
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