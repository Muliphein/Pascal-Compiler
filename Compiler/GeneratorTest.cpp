#include "ASTNodes.h"
#include "BasicType.h"
#include "BinaryOp.h"
#include <iostream>
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
#endif
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

int main()
{

    // test1(); // Basic Test a(Int)+b(Int) Problem
    // test2(); // Bool Type Test
    // test3(); // Array Type Test a+b Problem
    // test4(); // Struct Type Test a+b Problem;
    try{
        test5(); // Variable Index
    } catch (char const * s){
        cout<<s<<endl;
    }
    return 0;
}