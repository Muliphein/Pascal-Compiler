#ifndef __ASTNODES_H__
#define __ASTNODES_H__

#include "BinaryOp.h"
#include "BasicLLVM.h"

using namespace llvm;
namespace ASTNodes{

    class CodeGenResult{
      public:
        Value* mem;
        Type* type;
        Value* value;

        CodeGenResult(Value* _mem, Type* _type, Value* _value){
            mem = _mem;
            type = _type;
            value = _value;
        }
        ~CodeGenResult();
    };

    class BasicNode{
      public:
        virtual ~BasicNode() = default;
        virtual CodeGenResult* code_gen() = 0;
    };

    class VarAccessNode: public BasicNode{
      public:
        bool is_global;
        std::string var_name;
        int idx = 0;
        std::shared_ptr<VarAccessNode> nested_var = nullptr;
        VarAccessNode(){};
        CodeGenResult* code_gen() override;
    };
    
    class ConstantNode: public BasicNode{
      public:
        Type* constant_type;
        Value* constant_value;
        ConstantNode(){};
        CodeGenResult* code_gen() override;
    };

    class VariableDefineNode: public BasicNode{
      public:
        Type* variable_type;
        // std::string variable_name;
        bool is_global;
        bool is_array;
        int array_length;
        std::string name;
        VariableDefineNode(){};
        CodeGenResult* code_gen() override;
    };

	class BinaryExprNode: public BasicNode{
      public:
		BinaryOper expr_op;
        std::shared_ptr<BasicNode> LHS, RHS;
        BinaryExprNode(){};
        CodeGenResult* code_gen() override;
	};

    class CallNode: public BasicNode{
      public:
        std::string callee_name;
        std::vector<std::shared_ptr<BasicNode> > callee_args;
        CallNode(){};
        CodeGenResult* code_gen() override;
    };

    class FunDeclareNode: public BasicNode{
      public:
        std::string function_name;
        Type* ret_type;
        std::vector<Type*> function_arg_types;
        std::vector<std::string> function_arg_names; // necessary
        FunDeclareNode(){};
        CodeGenResult* code_gen() override;
    };

    class FunctionNode: public BasicNode{
      public:
        std::shared_ptr<FunDeclareNode> func_declare;
        std::shared_ptr<BasicNode> func_body;
        FunctionNode(){};
        std::string get_name();
        CodeGenResult* code_gen() override;
    };

    class AssignNode: public BasicNode{
      public:
        std::shared_ptr<VarAccessNode> LHS;
        std::shared_ptr<BasicNode> RHS;
        AssignNode(){};
        CodeGenResult* code_gen() override;
    };

    class StructDefineNode: public BasicNode{
      public:
        std::string struct_name;
        std::vector<llvm::Type*> struct_member_type;
        std::vector<std::string> struct_member_name;
        StructDefineNode(){};
        CodeGenResult* code_gen() override;
    };

    class SysWriteNode: public BasicNode{
      public:
        bool has_newline;
        std::vector<std::shared_ptr<BasicNode> > args;
        SysWriteNode(){};
        CodeGenResult* code_gen() override;
    };

    class SysReadNode: public BasicNode{
      public:
        bool has_newline;
        std::vector<std::shared_ptr<VarAccessNode> > args;
        SysReadNode(){};
        CodeGenResult* code_gen() override;
    };

    class StmtSeqNode: public BasicNode{
      public:
        std::vector<std::shared_ptr<BasicNode> > stmts;
        StmtSeqNode(){};
        CodeGenResult* code_gen() override;
    };

    class ProgramNode: public BasicNode{
      public:
        std::vector<std::shared_ptr<BasicNode> > parts;
        ProgramNode(){};
        CodeGenResult* code_gen() override;
    };

    class ReturnNode: public BasicNode{
      public:
        std::shared_ptr<BasicNode> val;
        ReturnNode(){};
        CodeGenResult* code_gen() override;
    };


}

#endif