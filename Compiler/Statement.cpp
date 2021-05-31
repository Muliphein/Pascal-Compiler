#include "ASTNodes.h"

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

bool check_bool(Type* x){
    return x==BoolType;
}

Type* get_lcm_type(Type* a, Type* b){
    if ( a==RealType || b==RealType ) return RealType;
    if ( a==IntType || b==IntType ) return IntType;
    if ( a==CharType || b==CharType ) return CharType;
    return BoolType;
}

Value* type_cast(Value* v, Type* dt){
    Type* vt = v->getType();
    if (vt == dt){
        return v;
    } else {
        if (dt == RealType){
            if (vt==BoolType || vt == CharType){
                return builder.CreateUIToFP(v, RealType);
            } else { // IntType -> RealType
                return builder.CreateSIToFP(v, RealType);
            }
        } else if (dt == IntType){
            return builder.CreateZExt(v, IntType);
        } else if (dt == CharType){
            return builder.CreateZExt(v, IntType);
        } else {
            throw new IRBuilderMeesage("[IRBuilder] Error : {Convert Wrong} Report this Issue to Manager");
        }
    }
    throw new IRBuilderMeesage("[IRBuilder] Error : {Convert Wrong} Report this Issue to Manager");
}

ASTNodes::CodeGenResult* ASTNodes::BinaryExprNode::code_gen(){

    CodeGenResult* lhs = this->LHS->code_gen();
    CodeGenResult* rhs = this->RHS->code_gen();
    
    Value* lv = lhs->get_value();
    Value* rv = rhs->get_value();

    BinaryOper now_op = this->expr_op;
    bool ret_real = false;
    Type* lcm_type;

    if (now_op == AND || now_op == OR){
        if ( (!check_bool(lv->getType())) || (!check_bool(rv->getType())) )
            throw new IRBuilderMeesage("[IRBuilder] Error : AND/OR's Bboth Sides Should be Bool Type");
    } else {

        lcm_type = get_lcm_type(lv->getType(), rv->getType());
        if (lcm_type == RealType && (now_op==DIV||now_op==MOD) ){
            throw new IRBuilderMeesage("[IRBuilder] Error : DIV/MOS's Bboth Sides Shouldn't be Real Type");
        } else if (lcm_type == BoolType || lcm_type == CharType){
            lcm_type = IntType;
        }

        lv = type_cast(lv, lcm_type);
        rv = type_cast(rv, lcm_type);
    }

    Value* _value;
    switch (this->expr_op){
        // ---- Only For Bool
        case OR:
            _value=builder.CreateOr(lv, rv);
        break;
        case AND:
            _value=builder.CreateAnd(lv, rv);
        break;

        // ---- For Real Int
        case PLUS:
            _value=builder.CreateBinOp(Instruction::BinaryOps::Add, lv, rv);
        break;
        case MINUS:
            _value=builder.CreateBinOp(Instruction::BinaryOps::Sub, lv, rv);
        break;
        case MUL:
            _value=builder.CreateBinOp(Instruction::BinaryOps::Mul, lv, rv);
        break;
        case DIVISION:
            _value=builder.CreateBinOp(Instruction::BinaryOps::SDiv, lv, rv);
        break;

        // ---- Only For Int
        case DIV:
            _value=builder.CreateSDiv(lv, rv);
        break;
        case MOD:
            _value=builder.CreateSRem(lv, rv);
        break;

        // ---- For Real Int
        case GE:
            _value= lcm_type != RealType ? builder.CreateICmpSGE(lv, rv) : builder.CreateFCmpOGE(lv, rv);
        break;
        case GT:
            _value= lcm_type != RealType ? builder.CreateICmpSGT(lv, rv) : builder.CreateFCmpOGT(lv, rv);
        break;
        case LE:
            _value= lcm_type != RealType ? builder.CreateICmpSLE(lv, rv) : builder.CreateFCmpOLE(lv, rv);
        break;
        case LT:
            _value= lcm_type != RealType ? builder.CreateICmpSLT(lv, rv) : builder.CreateFCmpOLT(lv, rv);
        break;
        case EQUAL:
            _value= lcm_type != RealType ? builder.CreateICmpEQ(lv, rv) : builder.CreateFCmpOEQ(lv, rv);
        break;
        case UNEQUAL:
            _value= lcm_type != RealType ? builder.CreateICmpNE(lv, rv) : builder.CreateFCmpONE(lv, rv);
        break;

        default:
            throw new IRBuilderMeesage("[IRBuilder] Error : Undefined Binary Operand");
    }
    return new CodeGenResult(nullptr, _value->getType(), _value);
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
    } else builder.CreateBr(rep_ent);

    builder.SetInsertPoint(rep_body_end);
    builder.CreateBr(rep_over);
    builder.SetInsertPoint(rep_over);
    return nullptr;
}

ASTNodes::CodeGenResult* ASTNodes::IfElseNode::code_gen(){
    Function* func = module->getFunction(now_function);
    BasicBlock * then_block = BasicBlock::Create(context, "then_block", func);
    BasicBlock * else_block = BasicBlock::Create(context, "else_block", func);
    BasicBlock * end_block  = BasicBlock::Create(context, "end_block" , func);
    builder.CreateCondBr(this->cond->code_gen()->get_value(), then_block, else_block);
    
    builder.SetInsertPoint(then_block);
    this->then_body->code_gen();
    builder.CreateBr(end_block);

    builder.SetInsertPoint(else_block);
    this->else_body->code_gen();
    builder.CreateBr(end_block);

    builder.SetInsertPoint(end_block);
    return nullptr;
}