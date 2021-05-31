#include "SystemCall.h"
#include "BasicType.h"
#include "BinaryOp.h"

extern LLVMContext context;
extern IRBuilder<> builder;
extern std::shared_ptr<Module> module;

extern int stage;

extern std::map<std::string, Value*> table_mem[MAX_NESTED];// VarName -> Memory
extern std::map<std::string, Type*> table_type[MAX_NESTED];// VarName -> Type
extern std::map<std::string, bool> table_array[MAX_NESTED];// VarName -> Array


ASTNodes::CodeGenResult* ASTNodes::AssignNode::code_gen(){
    CodeGenResult* rhs = this->RHS->code_gen();
    CodeGenResult* lhs = this->LHS->code_gen();
    builder.CreateStore(rhs->get_value(), lhs->mem);
    return rhs;
}

ASTNodes::CodeGenResult* ASTNodes::BinaryExprNode::code_gen(){
    CodeGenResult* lhs = this->LHS->code_gen();
    CodeGenResult* rhs = this->RHS->code_gen();
    
    if (lhs->type != rhs->type){
        throw("Error : Not the same Type. UnSupport cast\n");
    } else {
        Type* _type = lhs->type;
        Value* _value;
        switch (this->expr_op){
            case PLUS:
                _value=builder.CreateBinOp(Instruction::BinaryOps::Add, lhs->get_value(), rhs->get_value());
            break;
            default:
                throw("Error : UnSupport Binary Operation\n");
        }
        return new CodeGenResult(nullptr, _type, _value);
    }
}

ASTNodes::CodeGenResult* ASTNodes::StmtSeqNode::code_gen(){
    stage++;
    table_mem[stage].clear();
    table_type[stage].clear();
    table_array[stage].clear();
    for (auto arg: this->stmts)
        arg->code_gen();
    stage--;
    return nullptr;
}

ASTNodes::CodeGenResult* ASTNodes::ProgramNode::code_gen(){
    // printf("In Program\n");
    for (auto arg: this->parts)
        arg->code_gen();
    // printf("Out Program\n");
    return nullptr;
}