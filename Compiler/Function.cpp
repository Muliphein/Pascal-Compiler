#include "BasicType.h"
#include "BasicLLVM.h"
#include "ASTNodes.h"

extern LLVMContext context;
extern IRBuilder<> builder;
extern std::shared_ptr<Module> module;
extern std::string now_function;

extern int stage;
extern std::map<std::string, Type*> type_map;// TypeName -> Type Pointer <Global>
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
        FunctionType* func_type = FunctionType::get(this->ret_type, this->function_arg_types, false);
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
    builder.CreateRet(this->val->code_gen()->get_value());
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
    for (auto stmt: this->stmts){
        // printf("Find a Node\n");
        stmt->code_gen();
    }
    stage--;
    return nullptr;
}