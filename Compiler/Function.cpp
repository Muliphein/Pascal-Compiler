#include "BasicType.h"
#include "BasicLLVM.h"
#include "ASTNodes.h"

extern LLVMContext context;
extern IRBuilder<> builder;
extern std::shared_ptr<Module> module;

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
    Function* func_pointer = module->getFunction(func_name);
    BasicBlock* func_block = BasicBlock::Create(context, "", func_pointer);
    builder.SetInsertPoint(func_block);
    this->func_body->code_gen();
    return nullptr;
}

ASTNodes::CodeGenResult* ASTNodes::ReturnNode::code_gen(){
    builder.CreateRet(this->val->code_gen()->value);
    return nullptr;
}