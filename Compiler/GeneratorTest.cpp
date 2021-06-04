#include "ASTNodes.h"
using namespace llvm;
using namespace std;
using namespace ASTNodes;

extern void gene_init(std::string name);
extern void generator(ASTNodes::BasicNode* ASTRoot);

#ifdef fuck
void test1(){
    gene_init("test");
    StmtSeqNode* Root = new StmtSeqNode();

    VariableDefineNode* aDefine = new VariableDefineNode();
    aDefine->name="a";
    aDefine->type="integer";
    aDefine->is_array = false;

    VariableDefineNode* bDefine = new VariableDefineNode();
    bDefine->name="b";
    bDefine->type="integer";
    bDefine->is_array = false;

    VariableDefineNode* cDefine = new VariableDefineNode();
    cDefine->name="c";
    cDefine->type="integer";
    cDefine->is_array = false;

    Root->stmts.clear();
    Root->stmts.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<VariableDefineNode>(aDefine)));
    Root->stmts.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<VariableDefineNode>(bDefine)));
    Root->stmts.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<VariableDefineNode>(cDefine)));

    FunDeclareNode* funcDefine = new FunDeclareNode();
    funcDefine->function_name = "main";
    funcDefine->ret_type = Int64Type;
    funcDefine->function_arg_types.clear();
    funcDefine->function_arg_names.clear();

    VarAccessNode* aAccess = new VarAccessNode();
    aAccess->var_name = "a";
    aAccess->idx=0;
    
    VarAccessNode* bAccess = new VarAccessNode();
    bAccess->var_name = "b";
    bAccess->idx=0;

    VarAccessNode* cAccess = new VarAccessNode();
    cAccess->var_name = "c";
    cAccess->idx=0;

    SysReadNode* sysRead = new SysReadNode();
    sysRead->has_newline=true;
    sysRead->args.clear();
    sysRead->args.push_back(shared_ptr<VarAccessNode>(aAccess));
    sysRead->args.push_back(shared_ptr<VarAccessNode>(bAccess));

    BinaryExprNode* aPlusb = new BinaryExprNode();
    aPlusb->expr_op = BinaryOper::PLUS;
    aPlusb->LHS = dynamic_pointer_cast<BasicNode>(shared_ptr<VarAccessNode>(aAccess));
    aPlusb->RHS = dynamic_pointer_cast<BasicNode>(shared_ptr<VarAccessNode>(bAccess));

    AssignNode* cAssign = new AssignNode();
    cAssign->LHS = shared_ptr<VarAccessNode>(cAccess);
    cAssign->RHS = dynamic_pointer_cast<BasicNode>(shared_ptr<BinaryExprNode>(aPlusb));

    SysWriteNode* sysWrite = new SysWriteNode();
    sysWrite->has_newline = true;
    sysWrite->args.clear();
    sysWrite->args.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<VarAccessNode>(cAccess)));

    ConstantNode* zero = new ConstantNode();
    zero->constant_type = Int64Type;
    zero->constant_value = ConstantInt::get(Int64Type, 0);

    ReturnNode* ret = new ReturnNode();
    ret->val = dynamic_pointer_cast<BasicNode>(shared_ptr<ConstantNode>(zero));

    StmtSeqNode* stmts = new StmtSeqNode();
    stmts->stmts.clear();
    stmts->stmts.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<SysReadNode>(sysRead)));
    stmts->stmts.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<AssignNode>(cAssign)));
    stmts->stmts.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<SysWriteNode>(sysWrite)));
    stmts->stmts.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<ReturnNode>(ret)));

    FunctionNode* mainFun = new FunctionNode();
    mainFun->func_declare = shared_ptr<FunDeclareNode>(funcDefine);
    mainFun->func_body = dynamic_pointer_cast<BasicNode>(shared_ptr<StmtSeqNode>(stmts));
    
    Root->stmts.push_back(shared_ptr<FunctionNode>(mainFun));

    generator(Root);
}

void test2(){
    gene_init("test");
    StmtSeqNode* Root = new StmtSeqNode();

    VariableDefineNode* aDefine = new VariableDefineNode();
    aDefine->name="a";
    aDefine->type="bool";
    aDefine->is_array = false;

    Root->stmts.clear();
    Root->stmts.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<VariableDefineNode>(aDefine)));

    FunDeclareNode* funcDefine = new FunDeclareNode();
    funcDefine->function_name = "main";
    funcDefine->ret_type = Int64Type;
    funcDefine->function_arg_types.clear();
    funcDefine->function_arg_names.clear();

    VarAccessNode* aAccess = new VarAccessNode();
    aAccess->var_name = "a";
    aAccess->idx=0;
    
    SysReadNode* sysRead = new SysReadNode();
    sysRead->has_newline=true;
    sysRead->args.clear();
    sysRead->args.push_back(shared_ptr<VarAccessNode>(aAccess));

    SysWriteNode* sysWrite = new SysWriteNode();
    sysWrite->has_newline = true;
    sysWrite->args.clear();
    sysWrite->args.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<VarAccessNode>(aAccess)));

    ConstantNode* zero = new ConstantNode();
    zero->constant_type = Int64Type;
    zero->constant_value = ConstantInt::get(Int64Type, 0);

    ReturnNode* ret = new ReturnNode();
    ret->val = dynamic_pointer_cast<BasicNode>(shared_ptr<ConstantNode>(zero));

    StmtSeqNode* stmts = new StmtSeqNode();
    stmts->stmts.clear();
    // stmts->stmts.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<SysReadNode>(sysRead)));
    // stmts->stmts.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<SysWriteNode>(sysWrite)));
    stmts->stmts.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<ReturnNode>(ret)));

    FunctionNode* mainFun = new FunctionNode();
    mainFun->func_declare = shared_ptr<FunDeclareNode>(funcDefine);
    mainFun->func_body = dynamic_pointer_cast<BasicNode>(shared_ptr<StmtSeqNode>(stmts));
    
    Root->stmts.push_back(shared_ptr<FunctionNode>(mainFun));

    generator(Root);
}

void test3(){
    gene_init("test");
    StmtSeqNode* Root = new StmtSeqNode();

    VariableDefineNode* aDefine = new VariableDefineNode();
    aDefine->name="a";
    aDefine->type="integer";
    aDefine->is_array = true;
    aDefine->array_length = 3;

    Root->stmts.clear();
    Root->stmts.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<VariableDefineNode>(aDefine)));

    FunDeclareNode* funcDefine = new FunDeclareNode();
    funcDefine->function_name = "main";
    funcDefine->ret_type = Int64Type;
    funcDefine->function_arg_types.clear();
    funcDefine->function_arg_names.clear();

    VarAccessNode* a0Access = new VarAccessNode();
    a0Access->var_name = "a";
    a0Access->idx=0;

    VarAccessNode* a1Access = new VarAccessNode();
    a1Access->var_name = "a";
    a1Access->idx=1;

    VarAccessNode* a2Access = new VarAccessNode();
    a2Access->var_name = "a";
    a2Access->idx=2;
    
    SysReadNode* sysRead = new SysReadNode();
    sysRead->has_newline=true;
    sysRead->args.clear();
    sysRead->args.push_back(shared_ptr<VarAccessNode>(a0Access));
    sysRead->args.push_back(shared_ptr<VarAccessNode>(a1Access));

    
    BinaryExprNode* aPlusb = new BinaryExprNode();
    aPlusb->expr_op = BinaryOper::PLUS;
    aPlusb->LHS = dynamic_pointer_cast<BasicNode>(shared_ptr<VarAccessNode>(a0Access));
    aPlusb->RHS = dynamic_pointer_cast<BasicNode>(shared_ptr<VarAccessNode>(a1Access));

    AssignNode* cAssign = new AssignNode();
    cAssign->LHS = shared_ptr<VarAccessNode>(a2Access);
    cAssign->RHS = dynamic_pointer_cast<BasicNode>(shared_ptr<BinaryExprNode>(aPlusb));


    SysWriteNode* sysWrite = new SysWriteNode();
    sysWrite->has_newline = true;
    sysWrite->args.clear();
    sysWrite->args.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<VarAccessNode>(a2Access)));

    ConstantNode* zero = new ConstantNode();
    zero->constant_type = Int64Type;
    zero->constant_value = ConstantInt::get(Int64Type, 0);

    ReturnNode* ret = new ReturnNode();
    ret->val = dynamic_pointer_cast<BasicNode>(shared_ptr<ConstantNode>(zero));

    StmtSeqNode* stmts = new StmtSeqNode();
    stmts->stmts.clear();
    stmts->stmts.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<SysReadNode>(sysRead)));
    stmts->stmts.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<AssignNode>(cAssign)));
    stmts->stmts.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<SysWriteNode>(sysWrite)));
    stmts->stmts.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<ReturnNode>(ret)));

    FunctionNode* mainFun = new FunctionNode();
    mainFun->func_declare = shared_ptr<FunDeclareNode>(funcDefine);
    mainFun->func_body = dynamic_pointer_cast<BasicNode>(shared_ptr<StmtSeqNode>(stmts));
    
    Root->stmts.push_back(shared_ptr<FunctionNode>(mainFun));

    generator(Root);
}

void test4(){
    gene_init("test");
    ProgramNode* Root = new ProgramNode();

    RecordTypeDefineNode* structDefine = new RecordTypeDefineNode();
    structDefine->record_name = "MyStruct";
    structDefine->member_type_name = *new std::vector<std::string>;
    structDefine->member_type_name.push_back("char");
    structDefine->member_type_name.push_back("char");
    structDefine->member_type_name.push_back("char");
    structDefine->member_var_name = *new std::vector<std::string>;
    structDefine->member_var_name.push_back("a");
    structDefine->member_var_name.push_back("b");
    structDefine->member_var_name.push_back("c");
    structDefine->mem_is_array = *new std::vector<bool>;
    structDefine->mem_is_array.push_back(false);
    structDefine->mem_is_array.push_back(false);
    structDefine->mem_is_array.push_back(false);
    structDefine->mem_arrag_length = *new std::vector<int>;
    structDefine->mem_arrag_length.push_back(0);
    structDefine->mem_arrag_length.push_back(0);
    structDefine->mem_arrag_length.push_back(0);

    VariableDefineNode* varStruct = new VariableDefineNode();
    varStruct->name="rec";
    varStruct->type="MyStruct";
    varStruct->is_array = false;
    varStruct->array_length = 0;


    Root->parts.clear();
    Root->parts.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<RecordTypeDefineNode>(structDefine)));
    Root->parts.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<VariableDefineNode>(varStruct)));

    FunDeclareNode* funcDefine = new FunDeclareNode();
    funcDefine->function_name = "main";
    funcDefine->ret_type = Int64Type;
    funcDefine->function_arg_types.clear();
    funcDefine->function_arg_names.clear();

    VarAccessNode* structAccess = new VarAccessNode();
    structAccess->var_name = "rec";
    structAccess->idx=0;
    structAccess->nested_var=nullptr;

    VarAccessNode* aAccess = new VarAccessNode();
    aAccess->var_name = "a";
    aAccess->idx=0;
    aAccess->nested_var = shared_ptr<VarAccessNode>(structAccess);

    VarAccessNode* bAccess = new VarAccessNode();
    bAccess->var_name = "b";
    bAccess->idx=0;
    bAccess->nested_var = shared_ptr<VarAccessNode>(structAccess);

    VarAccessNode* cAccess = new VarAccessNode();
    cAccess->var_name = "c";
    cAccess->idx=0;
    cAccess->nested_var = shared_ptr<VarAccessNode>(structAccess);

    SysReadNode* sysRead = new SysReadNode();
    sysRead->has_newline=true;
    sysRead->args.clear();
    sysRead->args.push_back(shared_ptr<VarAccessNode>(aAccess));
    sysRead->args.push_back(shared_ptr<VarAccessNode>(bAccess));

    
    BinaryExprNode* aPlusb = new BinaryExprNode();
    aPlusb->expr_op = BinaryOper::PLUS;
    aPlusb->LHS = dynamic_pointer_cast<BasicNode>(shared_ptr<VarAccessNode>(aAccess));
    aPlusb->RHS = dynamic_pointer_cast<BasicNode>(shared_ptr<VarAccessNode>(bAccess));

    AssignNode* cAssign = new AssignNode();
    cAssign->LHS = shared_ptr<VarAccessNode>(cAccess);
    cAssign->RHS = dynamic_pointer_cast<BasicNode>(shared_ptr<BinaryExprNode>(aPlusb));


    SysWriteNode* sysWrite = new SysWriteNode();
    sysWrite->has_newline = true;
    sysWrite->args.clear();
    sysWrite->args.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<VarAccessNode>(cAccess)));

    ConstantNode* zero = new ConstantNode();
    zero->constant_type = Int64Type;
    zero->constant_value = ConstantInt::get(Int64Type, 0);

    ReturnNode* ret = new ReturnNode();
    ret->val = dynamic_pointer_cast<BasicNode>(shared_ptr<ConstantNode>(zero));

    StmtSeqNode* stmts = new StmtSeqNode();
    stmts->stmts.clear();
    stmts->stmts.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<SysReadNode>(sysRead)));
    stmts->stmts.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<AssignNode>(cAssign)));
    stmts->stmts.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<SysWriteNode>(sysWrite)));
    stmts->stmts.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<ReturnNode>(ret)));

    FunctionNode* mainFun = new FunctionNode();
    mainFun->func_declare = shared_ptr<FunDeclareNode>(funcDefine);
    mainFun->func_body = dynamic_pointer_cast<BasicNode>(shared_ptr<StmtSeqNode>(stmts));
    
    Root->parts.push_back(shared_ptr<FunctionNode>(mainFun));

    generator(Root);
}

void test5(){
    gene_init("test");
    ProgramNode* Root = new ProgramNode();

    RecordTypeDefineNode* structDefine = new RecordTypeDefineNode();
    structDefine->record_name = "MyStruct";
    structDefine->member_type_name = *new std::vector<std::string>;
    structDefine->member_type_name.push_back("integer");
    structDefine->member_var_name = *new std::vector<std::string>;
    structDefine->member_var_name.push_back("a");
    structDefine->mem_is_array = *new std::vector<bool>;
    structDefine->mem_is_array.push_back(true);
    structDefine->mem_arrag_length = *new std::vector<int>;
    structDefine->mem_arrag_length.push_back(10);

    VariableDefineNode* varStruct = new VariableDefineNode();
    varStruct->name="rec";
    varStruct->type="MyStruct";
    varStruct->is_array = false;
    varStruct->array_length = 0;

    Root->parts.clear();
    Root->parts.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<RecordTypeDefineNode>(structDefine)));
    Root->parts.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<VariableDefineNode>(varStruct)));

    FunDeclareNode* funcDefine = new FunDeclareNode();
    funcDefine->function_name = "main";
    funcDefine->ret_type = Int64Type;
    funcDefine->function_arg_types.clear();
    funcDefine->function_arg_names.clear();

    ConstantNode* zero = new ConstantNode();
    zero->constant_type = Int64Type;
    zero->constant_value = ConstantInt::get(Int64Type, 0);

    VarAccessNode* structAccess = new VarAccessNode();
    structAccess->var_name = "rec";
    structAccess->idx=dynamic_pointer_cast<BasicNode>(shared_ptr<ConstantNode>(zero));
    structAccess->nested_var=nullptr;

    
    ConstantNode* one = new ConstantNode();
    one->constant_type = Int64Type;
    one->constant_value = ConstantInt::get(Int64Type, 1);

    ConstantNode* two = new ConstantNode();
    two->constant_type = Int64Type;
    two->constant_value = ConstantInt::get(Int64Type, 2);

    ConstantNode* three = new ConstantNode();
    three->constant_type = Int64Type;
    three->constant_value = ConstantInt::get(Int64Type, 3);

    VarBaseNode* a1Access = new VarBaseNode();
    a1Access->var_name = "a";
    a1Access->idx=dynamic_pointer_cast<BasicNode>(shared_ptr<ConstantNode>(one));
    a1Access->nested_var = shared_ptr<VarAccessNode>(structAccess);

    VarBaseNode* a2Access = new VarBaseNode();
    a2Access->var_name = "a";
    a2Access->idx=dynamic_pointer_cast<BasicNode>(shared_ptr<ConstantNode>(two));
    a2Access->nested_var = shared_ptr<VarAccessNode>(structAccess);

    BinaryExprNode* Plus12 = new BinaryExprNode();
    Plus12->expr_op = BinaryOper::PLUS;
    Plus12->LHS = dynamic_pointer_cast<BasicNode>(shared_ptr<ConstantNode>(one));
    Plus12->RHS = dynamic_pointer_cast<BasicNode>(shared_ptr<ConstantNode>(two));

    VarBaseNode* a3Access = new VarBaseNode();
    a3Access->var_name = "a";
    a3Access->idx=dynamic_pointer_cast<BasicNode>(shared_ptr<VarBaseNode>(a2Access));
    a3Access->nested_var = shared_ptr<VarAccessNode>(structAccess);

    SysReadNode* sysRead = new SysReadNode();
    sysRead->has_newline=true;
    sysRead->args.clear();
    sysRead->args.push_back(shared_ptr<VarBaseNode>(a1Access));
    sysRead->args.push_back(shared_ptr<VarBaseNode>(a2Access));

    BinaryExprNode* aPlusb = new BinaryExprNode();
    aPlusb->expr_op = BinaryOper::PLUS;
    aPlusb->LHS = dynamic_pointer_cast<BasicNode>(shared_ptr<VarBaseNode>(a1Access));
    aPlusb->RHS = dynamic_pointer_cast<BasicNode>(shared_ptr<VarBaseNode>(a2Access));

    AssignNode* cAssign = new AssignNode();
    cAssign->LHS = shared_ptr<VarBaseNode>(a3Access);
    cAssign->RHS = dynamic_pointer_cast<BasicNode>(shared_ptr<BinaryExprNode>(aPlusb));

    SysWriteNode* sysWrite = new SysWriteNode();
    sysWrite->has_newline = true;
    sysWrite->args.clear();
    sysWrite->args.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<VarBaseNode>(a3Access)));

    ReturnNode* ret = new ReturnNode();
    ret->val = dynamic_pointer_cast<BasicNode>(shared_ptr<ConstantNode>(zero));

    FunctionBodyNode* funcBody = new FunctionBodyNode();
    funcBody->stmts.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<SysReadNode>(sysRead)));
    funcBody->stmts.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<AssignNode>(cAssign)));
    funcBody->stmts.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<SysWriteNode>(sysWrite)));
    funcBody->stmts.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<ReturnNode>(ret)));

    FunctionNode* mainFun = new FunctionNode();
    mainFun->func_declare = shared_ptr<FunDeclareNode>(funcDefine);
    mainFun->func_body = shared_ptr<FunctionBodyNode>(funcBody);
    
    Root->parts.push_back(shared_ptr<FunctionNode>(mainFun));

    generator(Root);
}


void test6(){
    gene_init("test");
    ProgramNode* Root = new ProgramNode();

    VariableDefineNode* aDefine = new VariableDefineNode();
    aDefine->name="a";
    aDefine->type="integer";
    aDefine->is_array = false;
    aDefine->array_length = 0;

    VariableDefineNode* bDefine = new VariableDefineNode();
    bDefine->name="b";
    bDefine->type="integer";
    bDefine->is_array = false;
    bDefine->array_length = 0;

    VariableDefineNode* cDefine = new VariableDefineNode();
    cDefine->name="c";
    cDefine->type="integer";
    cDefine->is_array = false;
    cDefine->array_length = 0;

    Root->parts.clear();
    Root->parts.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<VariableDefineNode>(aDefine)));
    Root->parts.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<VariableDefineNode>(bDefine)));
    Root->parts.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<VariableDefineNode>(cDefine)));

    FunDeclareNode* funcDefine = new FunDeclareNode();
    funcDefine->function_name = "main";
    funcDefine->ret_type = Int64Type;
    funcDefine->function_arg_types.clear();
    funcDefine->function_arg_names.clear();

    ConstantNode* zero = new ConstantNode();
    zero->constant_type = Int64Type;
    zero->constant_value = ConstantInt::get(Int64Type, 0);

    VarBaseNode* aAccess = new VarBaseNode();
    aAccess->var_name = "a";
    aAccess->idx=nullptr;
    aAccess->nested_var =nullptr;

    VarBaseNode* bAccess = new VarBaseNode();
    bAccess->var_name = "b";
    bAccess->idx=nullptr;
    bAccess->nested_var = nullptr;
    
    VarBaseNode* cAccess = new VarBaseNode();
    cAccess->var_name = "c";
    cAccess->idx=nullptr;
    cAccess->nested_var = nullptr;

    SysReadNode* sysRead = new SysReadNode();
    sysRead->has_newline=true;
    sysRead->args.clear();
    sysRead->args.push_back(shared_ptr<VarBaseNode>(aAccess));
    sysRead->args.push_back(shared_ptr<VarBaseNode>(bAccess));

    BinaryExprNode* aPlusb = new BinaryExprNode();
    aPlusb->expr_op = BinaryOper::PLUS;
    aPlusb->LHS = dynamic_pointer_cast<BasicNode>(shared_ptr<VarBaseNode>(aAccess));
    aPlusb->RHS = dynamic_pointer_cast<BasicNode>(shared_ptr<VarBaseNode>(bAccess));

    AssignNode* cAssign = new AssignNode();
    cAssign->LHS = shared_ptr<VarBaseNode>(cAccess);
    cAssign->RHS = dynamic_pointer_cast<BasicNode>(shared_ptr<BinaryExprNode>(aPlusb));

    SysWriteNode* sysWrite = new SysWriteNode();
    sysWrite->has_newline = true;
    sysWrite->args.clear();
    sysWrite->args.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<VarBaseNode>(cAccess)));

    ReturnNode* ret = new ReturnNode();
    ret->val = dynamic_pointer_cast<BasicNode>(shared_ptr<ConstantNode>(zero));

    FunctionBodyNode* funcBody = new FunctionBodyNode();
    funcBody->stmts.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<VariableDefineNode>(bDefine)));
    funcBody->stmts.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<VariableDefineNode>(cDefine)));
    funcBody->stmts.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<SysReadNode>(sysRead)));
    funcBody->stmts.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<AssignNode>(cAssign)));
    funcBody->stmts.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<SysWriteNode>(sysWrite)));
    funcBody->stmts.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<ReturnNode>(ret)));

    FunctionNode* mainFun = new FunctionNode();
    mainFun->func_declare = shared_ptr<FunDeclareNode>(funcDefine);
    mainFun->func_body = shared_ptr<FunctionBodyNode>(funcBody);
    
    Root->parts.push_back(shared_ptr<FunctionNode>(mainFun));

    generator(Root);
}

void test7(){
    gene_init("test");
    ProgramNode* Root = new ProgramNode();

    VariableDefineNode* aDefine = new VariableDefineNode();
    aDefine->name="a";
    aDefine->type="integer";
    aDefine->is_array = false;
    aDefine->array_length = 0;

    ConstantNode* zero = new ConstantNode();
    zero->constant_type = IntType;
    zero->constant_value = ConstantInt::get(IntType, 0);

    VarBaseNode* aAccess = new VarBaseNode();
    aAccess->var_name = "a";
    aAccess->idx=nullptr;
    aAccess->nested_var =nullptr;

    BinaryExprNode* aPlusa = new BinaryExprNode();
    aPlusa->expr_op = BinaryOper::PLUS;
    aPlusa->LHS = dynamic_pointer_cast<BasicNode>(shared_ptr<VarBaseNode>(aAccess));
    aPlusa->RHS = dynamic_pointer_cast<BasicNode>(shared_ptr<VarBaseNode>(aAccess));

    AssignNode* aAssign = new AssignNode();
    aAssign->LHS = shared_ptr<VarBaseNode>(aAccess);
    aAssign->RHS = dynamic_pointer_cast<BasicNode>(shared_ptr<BinaryExprNode>(aPlusa));

    SysReadNode* sysRead = new SysReadNode();
    sysRead->has_newline=true;
    sysRead->args.clear();
    sysRead->args.push_back(shared_ptr<VarBaseNode>(aAccess));

    SysWriteNode* sysWrite = new SysWriteNode();
    sysWrite->has_newline = true;
    sysWrite->args.clear();
    sysWrite->args.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<VarBaseNode>(aAccess)));

    // Mul Function
    FunDeclareNode* mulFunc = new FunDeclareNode();
    mulFunc->function_name = "mul2";
    mulFunc->ret_type_name = "integer";
    mulFunc->function_arg_types_names.push_back("integer");
    mulFunc->function_arg_names.push_back("a");

    ReturnNode* mulRet = new ReturnNode();
    mulRet->val = dynamic_pointer_cast<BasicNode>(shared_ptr<VarBaseNode>(aAccess));

    FunctionBodyNode* mulBody = new FunctionBodyNode();
    mulBody->stmts.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<AssignNode>(aAssign)));
    mulBody->stmts.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<ReturnNode>(mulRet)));

    FunctionNode* mulNode = new FunctionNode();
    mulNode->func_declare = shared_ptr<FunDeclareNode>(mulFunc);
    mulNode->func_body = shared_ptr<FunctionBodyNode>(mulBody);
    // Mul End

    // Main
    FunDeclareNode* mainFunc = new FunDeclareNode();
    mainFunc->function_name = "main";
    mainFunc->ret_type_name = "integer";
    mainFunc->function_arg_types_names.clear();
    mainFunc->function_arg_names.clear();


    FunctionCallNode* mulCall = new FunctionCallNode();
    mulCall->func_name = "mul2";
    mulCall->args.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<VarBaseNode>(aAccess)));

    AssignNode* callAssign = new AssignNode();
    callAssign->LHS = shared_ptr<VarBaseNode>(aAccess);
    callAssign->RHS = dynamic_pointer_cast<BasicNode>(shared_ptr<FunctionCallNode>(mulCall));

    ReturnNode* mainRet = new ReturnNode();
    mainRet->val = dynamic_pointer_cast<BasicNode>(shared_ptr<ConstantNode>(zero));



    FunctionBodyNode* mainBody = new FunctionBodyNode();
    mainBody->stmts.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<VariableDefineNode>(aDefine)));
    mainBody->stmts.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<SysReadNode>(sysRead)));
    // mainBody->stmts.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<SysWriteNode>(sysWrite)));
    mainBody->stmts.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<AssignNode>(callAssign)));
    mainBody->stmts.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<SysWriteNode>(sysWrite)));
    mainBody->stmts.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<ReturnNode>(mainRet)));

    FunctionNode* mainNode = new FunctionNode();
    mainNode->func_declare = shared_ptr<FunDeclareNode>(mainFunc);
    mainNode->func_body = shared_ptr<FunctionBodyNode>(mainBody);
    // Main End

    Root->parts.push_back(shared_ptr<FunctionNode>(mulNode));
    Root->parts.push_back(shared_ptr<FunctionNode>(mainNode));

    generator(Root);
}

void test8(){
    gene_init("test");
    ProgramNode* Root = new ProgramNode();

    VariableDefineNode* aDefine = new VariableDefineNode();
    aDefine->name="a";
    aDefine->type="integer";
    aDefine->is_array = false;
    aDefine->array_length = 0;


    VariableDefineNode* bDefine = new VariableDefineNode();
    bDefine->name="b";
    bDefine->type="integer";
    bDefine->is_array = false;
    bDefine->array_length = 0;

    ConstantNode* zero = new ConstantNode();
    zero->constant_type = IntType;
    zero->constant_value = ConstantInt::get(IntType, 0);

    VarBaseNode* aAccess = new VarBaseNode();
    aAccess->var_name = "a";
    aAccess->idx=nullptr;
    aAccess->nested_var =nullptr;
    
    VarBaseNode* bAccess = new VarBaseNode();
    bAccess->var_name = "b";
    bAccess->idx=nullptr;
    bAccess->nested_var =nullptr;

    VarBaseNode* maxAccess = new VarBaseNode();
    maxAccess->var_name = "max";
    maxAccess->idx=nullptr;
    maxAccess->nested_var =nullptr;

    SysReadNode* sysRead = new SysReadNode();
    sysRead->has_newline=true;
    sysRead->args.clear();
    sysRead->args.push_back(shared_ptr<VarBaseNode>(aAccess));
    sysRead->args.push_back(shared_ptr<VarBaseNode>(bAccess));

    // Max Function
    FunDeclareNode* mulFunc = new FunDeclareNode();
    mulFunc->function_name = "max";
    mulFunc->ret_type_name = "integer";
    mulFunc->function_arg_types_names.push_back("integer");
    mulFunc->function_arg_types_names.push_back("integer");
    mulFunc->function_arg_names.push_back("a");
    mulFunc->function_arg_names.push_back("b");

    ReturnNode* aRet = new ReturnNode();
    aRet->val = dynamic_pointer_cast<BasicNode>(shared_ptr<VarBaseNode>(aAccess));
    ReturnNode* bRet = new ReturnNode();
    bRet->val = dynamic_pointer_cast<BasicNode>(shared_ptr<VarBaseNode>(bAccess));
    ReturnNode* mulRet = new ReturnNode();
    mulRet->val = dynamic_pointer_cast<BasicNode>(shared_ptr<VarBaseNode>(maxAccess));

    AssignNode* aAssign = new AssignNode();
    aAssign->LHS = shared_ptr<VarBaseNode>(maxAccess);
    aAssign->RHS = dynamic_pointer_cast<BasicNode>(shared_ptr<VarBaseNode>(aAccess));

    AssignNode* bAssign = new AssignNode();
    bAssign->LHS = shared_ptr<VarBaseNode>(maxAccess);
    bAssign->RHS = dynamic_pointer_cast<BasicNode>(shared_ptr<VarBaseNode>(bAccess));

    BinaryExprNode* comp = new BinaryExprNode();
    comp->expr_op = BinaryOper::GE;
    comp->LHS = dynamic_pointer_cast<BasicNode>(shared_ptr<VarBaseNode>(aAccess));
    comp->RHS = dynamic_pointer_cast<BasicNode>(shared_ptr<VarBaseNode>(bAccess));

    IfElseNode* choice = new IfElseNode();
    choice->cond = dynamic_pointer_cast<BasicNode>(shared_ptr<BinaryExprNode>(comp));
    choice->then_body = dynamic_pointer_cast<BasicNode>(shared_ptr<AssignNode>(aAssign));
    choice->else_body = dynamic_pointer_cast<BasicNode>(shared_ptr<AssignNode>(bAssign));

    FunctionBodyNode* mulBody = new FunctionBodyNode();
    mulBody->stmts.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<IfElseNode>(choice)));
    mulBody->stmts.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<ReturnNode>(mulRet)));

    FunctionNode* mulNode = new FunctionNode();
    mulNode->func_declare = shared_ptr<FunDeclareNode>(mulFunc);
    mulNode->func_body = shared_ptr<FunctionBodyNode>(mulBody);
    // Max End

    // Main
    FunDeclareNode* mainFunc = new FunDeclareNode();
    mainFunc->function_name = "main";
    mainFunc->ret_type_name = "integer";
    mainFunc->function_arg_types_names.clear();
    mainFunc->function_arg_names.clear();

    FunctionCallNode* mulCall = new FunctionCallNode();
    mulCall->func_name = "max";
    mulCall->args.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<VarBaseNode>(aAccess)));
    mulCall->args.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<VarBaseNode>(bAccess)));

    SysWriteNode* sysWrite = new SysWriteNode();
    sysWrite->has_newline = true;
    sysWrite->args.clear();
    sysWrite->args.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<FunctionCallNode>(mulCall)));

    ReturnNode* mainRet = new ReturnNode();
    mainRet->val = dynamic_pointer_cast<BasicNode>(shared_ptr<ConstantNode>(zero));

    FunctionBodyNode* mainBody = new FunctionBodyNode();
    mainBody->stmts.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<VariableDefineNode>(aDefine)));
    mainBody->stmts.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<VariableDefineNode>(bDefine)));
    mainBody->stmts.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<SysReadNode>(sysRead)));
    mainBody->stmts.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<SysWriteNode>(sysWrite)));
    mainBody->stmts.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<ReturnNode>(mainRet)));

    FunctionNode* mainNode = new FunctionNode();
    mainNode->func_declare = shared_ptr<FunDeclareNode>(mainFunc);
    mainNode->func_body = shared_ptr<FunctionBodyNode>(mainBody);
    // Main End

    Root->parts.push_back(shared_ptr<FunctionNode>(mulNode));
    Root->parts.push_back(shared_ptr<FunctionNode>(mainNode));

    generator(Root);
}
#endif

void test9(){
    gene_init("test");
    ProgramNode* Root = new ProgramNode();

    VariableDefineNode* iDefine = new VariableDefineNode();
    iDefine->name="i";
    iDefine->type="integer";
    iDefine->is_array = false;
    iDefine->array_length = 0;

    VariableDefineNode* nDefine = new VariableDefineNode();
    nDefine->name="n";
    nDefine->type="integer";
    nDefine->is_array = false;
    nDefine->array_length = 0;

    VariableDefineNode* sumDefine = new VariableDefineNode();
    sumDefine->name="sum";
    sumDefine->type="integer";
    sumDefine->is_array = false;
    sumDefine->array_length = 0;

    ConstantNode* zero = new ConstantNode();
    zero->constant_type = IntType;
    zero->constant_value = ConstantInt::get(IntType, 0);

    ConstantNode* one = new ConstantNode();
    one->constant_type = IntType;
    one->constant_value = ConstantInt::get(IntType, 1);

    VarBaseNode* iAccess = new VarBaseNode();
    iAccess->var_name = "i";
    iAccess->idx=nullptr;
    iAccess->nested_var =nullptr;
    
    VarBaseNode* sumAccess = new VarBaseNode();
    sumAccess->var_name = "sum";
    sumAccess->idx=nullptr;
    sumAccess->nested_var =nullptr;

    VarBaseNode* nAccess = new VarBaseNode();
    nAccess->var_name = "n";
    nAccess->idx=nullptr;
    nAccess->nested_var =nullptr;

    SysReadNode* sysRead = new SysReadNode();
    sysRead->has_newline=true;
    sysRead->args.clear();
    sysRead->args.push_back(shared_ptr<VarBaseNode>(nAccess));

    // Main

    AssignNode* i_init = new AssignNode();
    i_init->LHS = shared_ptr<VarBaseNode>(iAccess);
    i_init->RHS = dynamic_pointer_cast<BasicNode>(shared_ptr<ConstantNode>(zero));
    
    AssignNode* n_init = new AssignNode();
    n_init->LHS = shared_ptr<VarBaseNode>(nAccess);
    n_init->RHS = dynamic_pointer_cast<BasicNode>(shared_ptr<ConstantNode>(zero));
    
    AssignNode* sum_init = new AssignNode();
    sum_init->LHS = shared_ptr<VarBaseNode>(sumAccess);
    sum_init->RHS = dynamic_pointer_cast<BasicNode>(shared_ptr<ConstantNode>(zero));

    FunDeclareNode* mainFunc = new FunDeclareNode();
    mainFunc->function_name = "main";
    mainFunc->ret_type_name = "integer";
    mainFunc->function_arg_types_names.clear();
    mainFunc->function_arg_names.clear();

    SysWriteNode* sysWrite = new SysWriteNode();
    sysWrite->has_newline = true;
    sysWrite->args.clear();
    sysWrite->args.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<VarBaseNode>(sumAccess)));

    ReturnNode* mainRet = new ReturnNode();

    BinaryExprNode* comp = new BinaryExprNode();
    comp->expr_op = BinaryOper::GE;
    comp->LHS = dynamic_pointer_cast<BasicNode>(shared_ptr<VarBaseNode>(nAccess));
    comp->RHS = dynamic_pointer_cast<BasicNode>(shared_ptr<VarBaseNode>(iAccess));

    BinaryExprNode* addone = new BinaryExprNode();
    addone->expr_op = BinaryOper::PLUS;
    addone->LHS = dynamic_pointer_cast<BasicNode>(shared_ptr<VarBaseNode>(iAccess));
    addone->RHS = dynamic_pointer_cast<BasicNode>(shared_ptr<ConstantNode>(one));

    AssignNode* inc = new AssignNode();
    inc->LHS = shared_ptr<VarBaseNode>(iAccess);
    inc->RHS = dynamic_pointer_cast<BasicNode>(shared_ptr<BinaryExprNode>(addone));
    
    BinaryExprNode* sum_i = new BinaryExprNode();
    sum_i->expr_op = BinaryOper::PLUS;
    sum_i->LHS = dynamic_pointer_cast<BasicNode>(shared_ptr<VarBaseNode>(iAccess));
    sum_i->RHS = dynamic_pointer_cast<BasicNode>(shared_ptr<VarBaseNode>(sumAccess));

    AssignNode* addover = new AssignNode();
    addover->LHS = shared_ptr<VarBaseNode>(sumAccess);
    addover->RHS = dynamic_pointer_cast<BasicNode>(shared_ptr<BinaryExprNode>(sum_i));

    StmtSeqNode* seq = new StmtSeqNode();
    seq->stmts.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<AssignNode>(addover)));
    seq->stmts.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<AssignNode>(inc)));

    RepeatNode* rep = new RepeatNode();
    rep->is_start= false;
    rep->reverse = false;
    rep->rep_con = dynamic_pointer_cast<BasicNode>(shared_ptr<BinaryExprNode>(comp));
    rep->rep_body_node = dynamic_pointer_cast<BasicNode>(shared_ptr<StmtSeqNode>(seq));

    FunctionBodyNode* mainBody = new FunctionBodyNode();
    mainBody->stmts.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<VariableDefineNode>(nDefine)));
    mainBody->stmts.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<VariableDefineNode>(iDefine)));
    mainBody->stmts.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<VariableDefineNode>(sumDefine)));
    mainBody->stmts.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<AssignNode>(i_init)));
    mainBody->stmts.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<AssignNode>(n_init)));
    mainBody->stmts.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<AssignNode>(sum_init)));
    mainBody->stmts.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<SysReadNode>(sysRead)));
    mainBody->stmts.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<RepeatNode>(rep)));
    mainBody->stmts.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<SysWriteNode>(sysWrite)));
    mainBody->stmts.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<ReturnNode>(mainRet)));

    FunctionNode* mainNode = new FunctionNode();
    mainNode->func_declare = shared_ptr<FunDeclareNode>(mainFunc);
    mainNode->func_body = shared_ptr<FunctionBodyNode>(mainBody);
    // Main End

    Root->parts.push_back(shared_ptr<FunctionNode>(mainNode));

    generator(Root);
}

void test10(){
    gene_init("test");
    ProgramNode* Root = new ProgramNode();

    VariableDefineNode* iDefine = new VariableDefineNode();
    iDefine->name="i";
    iDefine->type="integer";
    iDefine->is_array = false;
    iDefine->array_length = 0;

    VariableDefineNode* nDefine = new VariableDefineNode();
    nDefine->name="n";
    nDefine->type="integer";
    nDefine->is_array = false;
    nDefine->array_length = 0;

    VariableDefineNode* sumDefine = new VariableDefineNode();
    sumDefine->name="sum";
    sumDefine->type="integer";
    sumDefine->is_array = false;
    sumDefine->array_length = 0;

    ConstantNode* zero = new ConstantNode();
    zero->constant_type = IntType;
    zero->constant_value = ConstantInt::get(IntType, 0);

    ConstantNode* one = new ConstantNode();
    one->constant_type = IntType;
    one->constant_value = ConstantInt::get(IntType, 1);

    VarBaseNode* iAccess = new VarBaseNode();
    iAccess->var_name = "i";
    iAccess->idx=nullptr;
    iAccess->nested_var =nullptr;
    
    VarBaseNode* sumAccess = new VarBaseNode();
    sumAccess->var_name = "sum";
    sumAccess->idx=nullptr;
    sumAccess->nested_var =nullptr;

    VarBaseNode* nAccess = new VarBaseNode();
    nAccess->var_name = "n";
    nAccess->idx=nullptr;
    nAccess->nested_var =nullptr;

    SysReadNode* sysRead = new SysReadNode();
    sysRead->has_newline=true;
    sysRead->args.clear();
    sysRead->args.push_back(shared_ptr<VarBaseNode>(nAccess));

    AssignNode* i_init = new AssignNode();
    i_init->LHS = shared_ptr<VarBaseNode>(iAccess);
    i_init->RHS = dynamic_pointer_cast<BasicNode>(shared_ptr<ConstantNode>(zero));
    
    AssignNode* n_init = new AssignNode();
    n_init->LHS = shared_ptr<VarBaseNode>(nAccess);
    n_init->RHS = dynamic_pointer_cast<BasicNode>(shared_ptr<ConstantNode>(zero));
    
    AssignNode* sum_init = new AssignNode();
    sum_init->LHS = shared_ptr<VarBaseNode>(sumAccess);
    sum_init->RHS = dynamic_pointer_cast<BasicNode>(shared_ptr<ConstantNode>(zero));

    // Void Function
    FunDeclareNode* printDec = new FunDeclareNode();
    printDec->function_name = "print";
    printDec->ret_type_name = "void";


    SysWriteNode* printI = new SysWriteNode();
    printI->has_newline = true;
    printI->args.clear();
    printI->args.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<VarBaseNode>(iAccess)));

    FunctionBodyNode* printBodyNode = new FunctionBodyNode();
    printBodyNode->stmts.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<VariableDefineNode>(iDefine)));
    printBodyNode->stmts.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<AssignNode>(i_init)));
    printBodyNode->stmts.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<SysWriteNode>(printI)));
    printBodyNode->stmts.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<ReturnNode>(new ReturnNode())));

    FunctionNode* printFunc = new FunctionNode();
    printFunc->func_declare = shared_ptr<FunDeclareNode>(printDec);
    printFunc->func_body = shared_ptr<FunctionBodyNode>(printBodyNode);
    // Main

    FunDeclareNode* mainFunc = new FunDeclareNode();
    mainFunc->function_name = "main";
    mainFunc->ret_type_name = "integer";
    mainFunc->function_arg_types_names.clear();
    mainFunc->function_arg_names.clear();

    FunctionCallNode* printCall = new FunctionCallNode();
    printCall->func_name="print";

    SysWriteNode* sysWrite = new SysWriteNode();
    sysWrite->has_newline = true;
    sysWrite->args.clear();
    sysWrite->args.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<VarBaseNode>(sumAccess)));

    ReturnNode* mainRet = new ReturnNode();

    BinaryExprNode* comp = new BinaryExprNode();
    comp->expr_op = BinaryOper::GE;
    comp->LHS = dynamic_pointer_cast<BasicNode>(shared_ptr<VarBaseNode>(nAccess));
    comp->RHS = dynamic_pointer_cast<BasicNode>(shared_ptr<VarBaseNode>(iAccess));

    BinaryExprNode* addone = new BinaryExprNode();
    addone->expr_op = BinaryOper::PLUS;
    addone->LHS = dynamic_pointer_cast<BasicNode>(shared_ptr<VarBaseNode>(iAccess));
    addone->RHS = dynamic_pointer_cast<BasicNode>(shared_ptr<ConstantNode>(one));

    AssignNode* inc = new AssignNode();
    inc->LHS = shared_ptr<VarBaseNode>(iAccess);
    inc->RHS = dynamic_pointer_cast<BasicNode>(shared_ptr<BinaryExprNode>(addone));
    
    BinaryExprNode* sum_i = new BinaryExprNode();
    sum_i->expr_op = BinaryOper::PLUS;
    sum_i->LHS = dynamic_pointer_cast<BasicNode>(shared_ptr<VarBaseNode>(iAccess));
    sum_i->RHS = dynamic_pointer_cast<BasicNode>(shared_ptr<VarBaseNode>(sumAccess));

    AssignNode* addover = new AssignNode();
    addover->LHS = shared_ptr<VarBaseNode>(sumAccess);
    addover->RHS = dynamic_pointer_cast<BasicNode>(shared_ptr<BinaryExprNode>(sum_i));

    StmtSeqNode* seq = new StmtSeqNode();
    seq->stmts.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<AssignNode>(addover)));
    seq->stmts.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<AssignNode>(inc)));

    RepeatNode* rep = new RepeatNode();
    rep->is_start= false;
    rep->reverse = false;
    rep->rep_con = dynamic_pointer_cast<BasicNode>(shared_ptr<BinaryExprNode>(comp));
    rep->rep_body_node = dynamic_pointer_cast<BasicNode>(shared_ptr<StmtSeqNode>(seq));

    FunctionBodyNode* mainBody = new FunctionBodyNode();
    mainBody->stmts.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<FunctionCallNode>(printCall)));
    mainBody->stmts.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<VariableDefineNode>(nDefine)));
    mainBody->stmts.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<VariableDefineNode>(iDefine)));
    mainBody->stmts.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<VariableDefineNode>(sumDefine)));
    mainBody->stmts.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<AssignNode>(i_init)));
    mainBody->stmts.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<AssignNode>(n_init)));
    mainBody->stmts.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<AssignNode>(sum_init)));
    mainBody->stmts.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<SysReadNode>(sysRead)));
    mainBody->stmts.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<RepeatNode>(rep)));
    mainBody->stmts.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<SysWriteNode>(sysWrite)));
    mainBody->stmts.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<ReturnNode>(mainRet)));

    FunctionNode* mainNode = new FunctionNode();
    mainNode->func_declare = shared_ptr<FunDeclareNode>(mainFunc);
    mainNode->func_body = shared_ptr<FunctionBodyNode>(mainBody);
    // Main End

    Root->parts.push_back(shared_ptr<FunctionNode>(printFunc));
    Root->parts.push_back(shared_ptr<FunctionNode>(mainNode));

    generator(Root);
}

void test11(){
    gene_init("test");
    ProgramNode* Root = new ProgramNode();

    VariableDefineNode* aDefine = new VariableDefineNode();
    aDefine->name="a";
    aDefine->type="integer";
    aDefine->is_array = false;
    aDefine->array_length = 0;


    VariableDefineNode* bDefine = new VariableDefineNode();
    bDefine->name="b";
    bDefine->type="integer";
    bDefine->is_array = false;
    bDefine->array_length = 0;

    ConstantNode* zero = new ConstantNode();
    zero->constant_type = IntType;
    zero->constant_value = ConstantInt::get(IntType, 0);

    VarBaseNode* aAccess = new VarBaseNode();
    aAccess->var_name = "a";
    aAccess->idx=nullptr;
    aAccess->nested_var =nullptr;
    
    VarBaseNode* bAccess = new VarBaseNode();
    bAccess->var_name = "b";
    bAccess->idx=nullptr;
    bAccess->nested_var =nullptr;

    VarBaseNode* maxAccess = new VarBaseNode();
    maxAccess->var_name = "max";
    maxAccess->idx=nullptr;
    maxAccess->nested_var =nullptr;

    SysReadNode* sysRead = new SysReadNode();
    sysRead->has_newline=true;
    sysRead->args.clear();
    sysRead->args.push_back(shared_ptr<VarBaseNode>(aAccess));
    sysRead->args.push_back(shared_ptr<VarBaseNode>(bAccess));

    // Max Function
    FunDeclareNode* mulFunc = new FunDeclareNode();
    mulFunc->function_name = "max";
    mulFunc->ret_type_name = "integer";
    mulFunc->function_arg_types_names.push_back("integer");
    mulFunc->function_arg_types_names.push_back("integer");
    mulFunc->function_arg_names.push_back("a");
    mulFunc->function_arg_names.push_back("b");
    mulFunc->function_arg_var.push_back(true);
    mulFunc->function_arg_var.push_back(true);

    AssignNode* aAssign = new AssignNode();
    aAssign->LHS = shared_ptr<VarBaseNode>(maxAccess);
    aAssign->RHS = dynamic_pointer_cast<BasicNode>(shared_ptr<VarBaseNode>(aAccess));

    AssignNode* bAssign = new AssignNode();
    bAssign->LHS = shared_ptr<VarBaseNode>(maxAccess);
    bAssign->RHS = dynamic_pointer_cast<BasicNode>(shared_ptr<VarBaseNode>(bAccess));

    BinaryExprNode* comp = new BinaryExprNode();
    comp->expr_op = BinaryOper::GE;
    comp->LHS = dynamic_pointer_cast<BasicNode>(shared_ptr<VarBaseNode>(aAccess));
    comp->RHS = dynamic_pointer_cast<BasicNode>(shared_ptr<VarBaseNode>(bAccess));

    IfElseNode* choice = new IfElseNode();
    choice->cond = dynamic_pointer_cast<BasicNode>(shared_ptr<BinaryExprNode>(comp));
    choice->then_body = dynamic_pointer_cast<BasicNode>(shared_ptr<AssignNode>(aAssign));
    choice->else_body = dynamic_pointer_cast<BasicNode>(shared_ptr<AssignNode>(bAssign));

    AssignNode* maxAssign = new AssignNode();
    maxAssign->LHS = shared_ptr<VarBaseNode>(bAccess);
    maxAssign->RHS = dynamic_pointer_cast<BasicNode>(shared_ptr<VarBaseNode>(maxAccess));


    FunctionBodyNode* mulBody = new FunctionBodyNode();
    mulBody->stmts.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<IfElseNode>(choice)));
    mulBody->stmts.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<AssignNode>(maxAssign)));
    mulBody->stmts.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<ReturnNode>(new ReturnNode())));

    FunctionNode* mulNode = new FunctionNode();
    mulNode->func_declare = shared_ptr<FunDeclareNode>(mulFunc);
    mulNode->func_body = shared_ptr<FunctionBodyNode>(mulBody);
    // Max End

    // Main
    FunDeclareNode* mainFunc = new FunDeclareNode();
    mainFunc->function_name = "main";
    mainFunc->ret_type_name = "integer";
    mainFunc->function_arg_types_names.clear();
    mainFunc->function_arg_names.clear();

    FunctionCallNode* mulCall = new FunctionCallNode();
    mulCall->func_name = "max";
    mulCall->args.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<VarBaseNode>(aAccess)));
    mulCall->args.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<VarBaseNode>(bAccess)));

    SysWriteNode* sysWrite = new SysWriteNode();
    sysWrite->has_newline = true;
    sysWrite->args.clear();
    sysWrite->args.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<FunctionCallNode>(mulCall)));

    SysWriteNode* sysWrite2 = new SysWriteNode();
    sysWrite2->has_newline = true;
    sysWrite2->args.clear();
    sysWrite2->args.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<VarBaseNode>(aAccess)));
    sysWrite2->args.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<VarBaseNode>(bAccess)));

    ReturnNode* mainRet = new ReturnNode();

    FunctionBodyNode* mainBody = new FunctionBodyNode();
    mainBody->stmts.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<VariableDefineNode>(aDefine)));
    mainBody->stmts.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<VariableDefineNode>(bDefine)));
    mainBody->stmts.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<SysReadNode>(sysRead)));
    mainBody->stmts.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<SysWriteNode>(sysWrite)));
    mainBody->stmts.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<SysWriteNode>(sysWrite2)));
    mainBody->stmts.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<ReturnNode>(mainRet)));

    FunctionNode* mainNode = new FunctionNode();
    mainNode->func_declare = shared_ptr<FunDeclareNode>(mainFunc);
    mainNode->func_body = shared_ptr<FunctionBodyNode>(mainBody);
    // Main End

    Root->parts.push_back(shared_ptr<FunctionNode>(mulNode));
    Root->parts.push_back(shared_ptr<FunctionNode>(mainNode));

    generator(Root);
}


void test12(){
    gene_init("test");
    ProgramNode* Root = new ProgramNode();

    VariableDefineNode* aDefine = new VariableDefineNode();
    aDefine->name="a";
    aDefine->type="integer";
    aDefine->is_array = true;
    aDefine->array_length = 3;
    aDefine->lower_bound = 50;

    ConstantNode* zero = new ConstantNode();
    zero->constant_type = IntType;
    zero->constant_value = ConstantInt::get(IntType, 0);

    ConstantNode* fifty = new ConstantNode();
    fifty->constant_type = IntType;
    fifty->constant_value = ConstantInt::get(IntType, 50);

    
    ConstantNode* fiftyone = new ConstantNode();
    fiftyone->constant_type = IntType;
    fiftyone->constant_value = ConstantInt::get(IntType, 51);

    ConstantNode* fiftytwo = new ConstantNode();
    fiftytwo->constant_type = IntType;
    fiftytwo->constant_value = ConstantInt::get(IntType, 52);


    VarBaseNode* aAccess = new VarBaseNode();
    aAccess->var_name = "a";
    aAccess->idx=dynamic_pointer_cast<BasicNode>(shared_ptr<ConstantNode>(fifty));
    aAccess->nested_var =nullptr;
    
    VarBaseNode* bAccess = new VarBaseNode();
    bAccess->var_name = "a";
    bAccess->idx=dynamic_pointer_cast<BasicNode>(shared_ptr<ConstantNode>(fiftyone));
    bAccess->nested_var =nullptr;

    VarBaseNode* cAccess = new VarBaseNode();
    cAccess->var_name = "a";
    cAccess->idx=dynamic_pointer_cast<BasicNode>(shared_ptr<ConstantNode>(fiftytwo));
    cAccess->nested_var =nullptr;

    SysReadNode* sysRead = new SysReadNode();
    sysRead->has_newline=true;
    sysRead->args.clear();
    sysRead->args.push_back(shared_ptr<VarBaseNode>(aAccess));
    sysRead->args.push_back(shared_ptr<VarBaseNode>(bAccess));

    BinaryExprNode* sum = new BinaryExprNode();
    sum->expr_op=BinaryOper::PLUS;
    sum->LHS = dynamic_pointer_cast<BasicNode>(shared_ptr<VarBaseNode>(aAccess));
    sum->RHS = dynamic_pointer_cast<BasicNode>(shared_ptr<VarBaseNode>(bAccess));

    AssignNode* cAssign = new AssignNode();
    cAssign->LHS = shared_ptr<VarBaseNode>(cAccess);
    cAssign->RHS = dynamic_pointer_cast<BasicNode>(shared_ptr<BinaryExprNode>(sum));


    // Main
    FunDeclareNode* mainFunc = new FunDeclareNode();
    mainFunc->function_name = "main";
    mainFunc->ret_type_name = "integer";
    mainFunc->function_arg_types_names.clear();
    mainFunc->function_arg_names.clear();

    SysWriteNode* sysWrite2 = new SysWriteNode();
    sysWrite2->has_newline = true;
    sysWrite2->args.clear();
    sysWrite2->args.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<VarBaseNode>(cAccess)));

    ReturnNode* mainRet = new ReturnNode();

    FunctionBodyNode* mainBody = new FunctionBodyNode();
    mainBody->stmts.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<VariableDefineNode>(aDefine)));
    mainBody->stmts.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<SysReadNode>(sysRead)));
    mainBody->stmts.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<AssignNode>(cAssign)));
    mainBody->stmts.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<SysWriteNode>(sysWrite2)));
    mainBody->stmts.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<ReturnNode>(mainRet)));

    FunctionNode* mainNode = new FunctionNode();
    mainNode->func_declare = shared_ptr<FunDeclareNode>(mainFunc);
    mainNode->func_body = shared_ptr<FunctionBodyNode>(mainBody);
    // Main End

    Root->parts.push_back(shared_ptr<FunctionNode>(mainNode));

    generator(Root);
}

int main()
{

    try{
        // test1(); // Basic Test a(Int)+b(Int) Problem
        // test2(); // Bool Type Test
        // test3(); // Array Type Test a+b Problem
        // test4(); // Struct Type Test a+b Problem;
        // test5(); // Variable Index
        // test6(); // Local Variable
        // test7(); // Local Var + Function Call
        // test8(); // If Condition
        // test9(); // Loop sum 1..n
        // test10(); // Void Function Call
        // test11(); // Var param
        test12(); // Var Lower
        // All Test Passed
    } catch (char const * s){
        cout<<s<<endl;
    } catch (string s){
        cout<<s<<endl;
    } catch (IRBuilderMeesage * err){
        cout << err->message() << endl;
    }
    return 0;
}