#include "BasicType.h"
#include "BasicLLVM.h"
#include "ASTNodes.h"

extern LLVMContext context;
extern IRBuilder<> builder;
extern std::shared_ptr<Module> module;

ASTNodes::CodeGenResult* ASTNodes::ConstantNode::code_gen(){
    return new CodeGenResult(nullptr, this->constant_type, this->constant_value);
}