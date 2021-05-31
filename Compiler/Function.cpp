#include "BasicType.h"
#include "BasicLLVM.h"
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
        throw("Redefine the Function "+this->function_name);
    } else {
        // printf("In Declare\n");
        std::vector<Type*> param_list;
        for (auto param_type_name:this->function_arg_types_names)
            param_list.push_back(type_map[param_type_name]);
        FunctionType* func_type = FunctionType::get(type_map[this->ret_type_name], param_list, false); // Un Support to variable Parameters
        Function* func_pointer = Function::Create(func_type, Function::ExternalLinkage, this->function_name, module.get());
        unsigned idx = 0;
        for (auto &arg: func_pointer->args())
            arg.setName(this->function_arg_names[idx++]);
        // printf("Out Declare\n");
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
    builder.CreateRet(this->val->code_gen()->get_value());
    return nullptr;
}

ASTNodes::CodeGenResult* ASTNodes::FunctionBodyNode::code_gen(){
    // printf("In Function Body\n");
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
        // std::cout << "Get "<<_name<<std::endl;
        // std::cout<<"Start Define"<<std::endl;
        // std::cout<<"End Define"<<std::endl;
        VariableDefineNode * arg_define = new VariableDefineNode(name_map[_type], false, 0, _name);
        arg_define->code_gen();
        VarBaseNode * arg_position = new VarBaseNode(_name, nullptr, nullptr);
        auto temp_mem = arg_position->code_gen()->mem;
        builder.CreateStore(arg, temp_mem);
    }

    VariableDefineNode * arg_define = new VariableDefineNode(
        name_map[func_pointer->getFunctionType()->getReturnType()], false, 0, now_function
    );
    arg_define->code_gen();

    // printf("Over Param Define\n");
    for (auto stmt: this->stmts){
        // printf("find a Node\n");
        stmt->code_gen();
    }
    stage--;
    return nullptr;
}

ASTNodes::CodeGenResult* ASTNodes::FunctionCallNode::code_gen(){
    std::vector <Value*> arg_val;
    arg_val.clear();
    // printf("Start build Call");
    for (auto arg_node:this->args)
        arg_val.push_back(arg_node->code_gen()->get_value());
    Function* func = module->getFunction(this->func_name);
    // printf("Find the function");
    if (func == nullptr){
        throw("No such Function " + this->func_name + "\n");
    }
    ArrayRef<Value*> arg_ref(arg_val);
    Value* ret = builder.CreateCall(func, arg_ref);
    
    // printf("Build Call Over");
    // std::cout<<"Return "<<ret->getType()<<std::endl;
    return new CodeGenResult(nullptr, ret->getType(), ret);
}