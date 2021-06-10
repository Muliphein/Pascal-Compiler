#include "ASTNodes.h"

extern LLVMContext context;
extern IRBuilder<> builder;
extern std::shared_ptr<Module> module;

extern int stage;

extern std::map<std::string, Value*> table_mem[MAX_NESTED];// VarName -> Memory
extern std::map<std::string, Type*> table_type[MAX_NESTED];// VarName -> Type
extern std::map<std::string, bool> table_array[MAX_NESTED];// VarName -> Array

extern std::string now_function;

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
            throw new IRBuilderMeesage("[IRBuilder] Error : Type Wrong");
        }
    }
    throw new IRBuilderMeesage("[IRBuilder] Error : Type Wrong");
}

Value* assign_cast(Value* v, Type* dt){
    Type* vt = v->getType();
    if (vt == dt) return v;
    if (dt == BoolType){
        if (vt == RealType){
            throw new IRBuilderMeesage("[IRBuilder] Error : Type Wrong");
        } else if (vt == IntType){
            return builder.CreateICmpNE(v, ConstantInt::get(IntType, 0));
        } else if (vt == CharType){
            return builder.CreateICmpNE(v, ConstantInt::get(CharType, 0));
        } else throw new IRBuilderMeesage("[IRBuilder] Error : Type Wrong");
    } else if (dt == IntType){
        if (vt == RealType){
            return builder.CreateFPToSI(v, IntType);
        } else if (vt == BoolType){
            return builder.CreateZExt(v, IntType);
        } else if (vt == CharType){
            return builder.CreateZExt(v, IntType);
        } else throw new IRBuilderMeesage("[IRBuilder] Error : Type Wrong");
    } else if (dt == CharType){
        if (vt == RealType){
            return builder.CreateFPToUI(v, CharType);
        } else if (vt == BoolType){
            return builder.CreateZExt(v, CharType);
        } else if (vt == IntType){
            return builder.CreateTrunc(v, CharType);
        } else throw new IRBuilderMeesage("[IRBuilder] Error : Type Wrong");
    } else if (dt == RealType){
        if (vt == CharType){
            return builder.CreateUIToFP(v, RealType);
        } else if (vt == BoolType){
            return builder.CreateUIToFP(v, RealType);
        } else if (vt == IntType){
            return builder.CreateSIToFP(v, RealType);
        } else throw new IRBuilderMeesage("[IRBuilder] Error : Type Wrong");
    }
    throw new IRBuilderMeesage("[IRBuilder] Error : Type Wrong");
}

ASTNodes::CodeGenResult* ASTNodes::AssignNode::code_gen(){
    CodeGenResult* rhs = this->RHS->code_gen();
    CodeGenResult* lhs = this->LHS->code_gen();
    Value* rv = rhs->get_value();
    // module->print(outs(), nullptr);
    assign_cast(rv, lhs->type);
    builder.CreateStore(rv, lhs->mem);
    return rhs;
}

ASTNodes::CodeGenResult* ASTNodes::BinaryExprNode::code_gen(){

    CodeGenResult* lhs = this->LHS->code_gen();
    CodeGenResult* rhs = this->RHS->code_gen();
    
    Value* lv = lhs->get_value();
    Value* rv = rhs->get_value();

    // module->print(outs(), nullptr);

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
        // module->print(outs(), nullptr);
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
    if (this->else_body == nullptr){
        BasicBlock * then_block = BasicBlock::Create(context, "then_block", func);
        BasicBlock * end_block  = BasicBlock::Create(context, "end_block" , func);
        builder.CreateCondBr(this->cond->code_gen()->get_value(), then_block, end_block);

        builder.SetInsertPoint(then_block);
        this->then_body->code_gen();
        builder.CreateBr(end_block);

        builder.SetInsertPoint(end_block);
        return nullptr;
    } else {
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
}

ASTNodes::CodeGenResult* ASTNodes::ForNode::code_gen(){
    stage++;
    Function* func = module->getFunction(now_function);

    ASTNodes::VariableDefineNode* loop_var_define = new ASTNodes::VariableDefineNode();
    loop_var_define->is_array = false;
    loop_var_define->name = this->loop_var;
    loop_var_define->type = std::string("integer");
    loop_var_define->code_gen();

    ASTNodes::VarBaseNode* loop_var_access = new ASTNodes::VarBaseNode();
    loop_var_access->nested_var=nullptr;
    loop_var_access->var_name=this->loop_var;
    ASTNodes::AssignNode* loop_var_init = new ASTNodes::AssignNode();
    loop_var_init->LHS = std::shared_ptr<VarBaseNode>(loop_var_access);
    loop_var_init->RHS = this->start_val;
    loop_var_init->code_gen();

    BasicBlock * con_block = BasicBlock::Create(context, "con_block", func);
    BasicBlock * loop_block = BasicBlock::Create(context, "loop_block", func);
    BasicBlock * end_block = BasicBlock::Create(context, "end_block", func);
    builder.CreateBr(con_block);
    builder.SetInsertPoint(con_block);

    ASTNodes::ConstantNode* fixed_val = new ASTNodes::ConstantNode();
    fixed_val->constant_type = IntType;
    fixed_val->constant_value = ConstantInt::get(IntType, is_to?1:-1);

    ASTNodes::BinaryExprNode* end_val_fixed = new ASTNodes::BinaryExprNode();
    end_val_fixed->expr_op = BinaryOper::PLUS;
    end_val_fixed->LHS = this->end_val;
    end_val_fixed->RHS = std::dynamic_pointer_cast<BasicNode>(std::shared_ptr<ConstantNode>(fixed_val));

    ASTNodes::BinaryExprNode* loop_con = new ASTNodes::BinaryExprNode();
    loop_con->expr_op = BinaryOper::UNEQUAL;
    loop_con->LHS = std::dynamic_pointer_cast<BasicNode>(std::shared_ptr<VarBaseNode>(loop_var_access));
    loop_con->RHS = std::dynamic_pointer_cast<BasicNode>(std::shared_ptr<BinaryExprNode>(end_val_fixed));
    builder.CreateCondBr(loop_con->code_gen()->get_value(), loop_block, end_block);

    builder.CreateBr(loop_block);
    builder.SetInsertPoint(loop_block);
    this->loop_body->code_gen();
    builder.CreateBr(con_block);
    builder.SetInsertPoint(end_block);

    stage--;
}