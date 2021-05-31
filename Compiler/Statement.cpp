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

extern std::string now_function;


ASTNodes::CodeGenResult* ASTNodes::AssignNode::code_gen(){
    CodeGenResult* rhs = this->RHS->code_gen();
    CodeGenResult* lhs = this->LHS->code_gen();
    builder.CreateStore(rhs->get_value(), lhs->mem);
    return rhs;
}

ASTNodes::CodeGenResult* ASTNodes::BinaryExprNode::code_gen(){
    // printf("Start Binary Expr Node\n");
    CodeGenResult* lhs = this->LHS->code_gen();
    CodeGenResult* rhs = this->RHS->code_gen();
    
    if (lhs->type != rhs->type){
        throw("Error : Not the same Type. UnSupport cast\n");
    } else {
        Type* _type;
        Value* _value;
        switch (this->expr_op){
            case PLUS:
                _type = lhs->type;
                _value=builder.CreateBinOp(Instruction::BinaryOps::Add, lhs->get_value(), rhs->get_value());
            break;
            case GE:
                _value=builder.CreateICmpSGE(lhs->get_value(), rhs->get_value());
                _type=_value->getType();
            break;
            default:
                throw("Error : UnSupport Binary Operation\n");
        }
        // printf("End Binary Expr Node\n");
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

ASTNodes::CodeGenResult* ASTNodes::RepeatNode::code_gen(){
    Function* func = module->getFunction(now_function);
    BasicBlock* rep_ent = BasicBlock::Create(context, "rep_ent", func);
    BasicBlock* rep_body = BasicBlock::Create(context, "rep_body", func);
    BasicBlock* rep_body_end = BasicBlock::Create(context, "rep_body_end", func);
    BasicBlock* rep_over = BasicBlock::Create(context, "rep_over", func);
    builder.CreateBr(rep_ent);
    builder.SetInsertPoint(rep_ent);

    if (this->is_start){
        if (!reverse){
            builder.CreateCondBr(this->rep_con->code_gen()->get_value(), rep_body, rep_body_end);
        } else {
            builder.CreateCondBr(this->rep_con->code_gen()->get_value(), rep_body_end, rep_body);
        }
        
    } else builder.CreateBr(rep_body);

    builder.SetInsertPoint(rep_body);
    this->rep_body_node->code_gen();

    if (!(this->is_start)){
        if (!reverse){
            builder.CreateCondBr(this->rep_con->code_gen()->get_value(), rep_body, rep_body_end);
        } else {
            builder.CreateCondBr(this->rep_con->code_gen()->get_value(), rep_body_end, rep_body);
        }
    } else builder.CreateBr(rep_body_end);

    builder.SetInsertPoint(rep_body_end);
    builder.CreateBr(rep_over);
    builder.SetInsertPoint(rep_over);
    return nullptr;
}

ASTNodes::CodeGenResult* ASTNodes::IfElseNode::code_gen(){
    // printf("Now Condition\n");
    Function* func = module->getFunction(now_function);
    // printf("Get Function Over\n");
    BasicBlock * then_block = BasicBlock::Create(context, "then_block", func);
    // printf("Get then Over\n");
    BasicBlock * else_block = BasicBlock::Create(context, "else_block", func);
    // printf("Get else Over\n");
    BasicBlock * end_block  = BasicBlock::Create(context, "end_block" , func);
    // printf("Get end Over\n");
    // printf("Build Condition Before\n");
    builder.CreateCondBr(this->cond->code_gen()->get_value(), then_block, else_block);
    // printf("Build Condition After\n");
    
    builder.SetInsertPoint(then_block);
    this->then_body->code_gen();
    builder.CreateBr(end_block);

    builder.SetInsertPoint(else_block);
    this->else_body->code_gen();
    builder.CreateBr(end_block);

    builder.SetInsertPoint(end_block);
    return nullptr;
}