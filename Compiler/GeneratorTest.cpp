#include "ASTNodes.h"
#include "BasicType.h"
#include "BinaryOp.h"
using namespace llvm;
using namespace std;
using namespace ASTNodes;

extern void gene_init(std::string name);
extern void generator(ASTNodes::BasicNode* ASTRoot);

void test1()
{
    gene_init("test");
    StmtSeqNode* Root = new StmtSeqNode();

    VariableDefineNode* aDefine = new VariableDefineNode();
    aDefine->name="a";
    aDefine->variable_type=IntType;
    aDefine->is_global = true;
    aDefine->is_array = false;

    VariableDefineNode* bDefine = new VariableDefineNode();
    bDefine->name="b";
    bDefine->variable_type=IntType;
    bDefine->is_global = true;
    bDefine->is_array = false;

    VariableDefineNode* cDefine = new VariableDefineNode();
    cDefine->name="c";
    cDefine->variable_type=IntType;
    cDefine->is_global = true;
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
    aAccess->is_global = true;
    aAccess->var_name = "a";
    aAccess->idx=0;
    
    VarAccessNode* bAccess = new VarAccessNode();
    bAccess->is_global = true;
    bAccess->var_name = "b";
    bAccess->idx=0;

    VarAccessNode* cAccess = new VarAccessNode();
    cAccess->is_global = true;
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
    aDefine->variable_type=BoolType;
    aDefine->is_global = true;
    aDefine->is_array = false;

    Root->stmts.clear();
    Root->stmts.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<VariableDefineNode>(aDefine)));

    FunDeclareNode* funcDefine = new FunDeclareNode();
    funcDefine->function_name = "main";
    funcDefine->ret_type = Int64Type;
    funcDefine->function_arg_types.clear();
    funcDefine->function_arg_names.clear();

    VarAccessNode* aAccess = new VarAccessNode();
    aAccess->is_global = true;
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
    stmts->stmts.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<SysReadNode>(sysRead)));
    stmts->stmts.push_back(dynamic_pointer_cast<BasicNode>(shared_ptr<SysWriteNode>(sysWrite)));
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
    aDefine->variable_type=IntType;
    aDefine->is_global = true;
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
    a0Access->is_global = true;
    a0Access->var_name = "a";
    a0Access->idx=0;

    VarAccessNode* a1Access = new VarAccessNode();
    a1Access->is_global = true;
    a1Access->var_name = "a";
    a1Access->idx=1;

    VarAccessNode* a2Access = new VarAccessNode();
    a2Access->is_global = true;
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

int main()
{

    // test1(); // Basic Test a(Int)+b(Int) Problem
    // test2(); //Bool Type Test
    test3(); //Array Type Test a+b Problem
    return 0;
}