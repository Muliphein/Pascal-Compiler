#include "ASTNodes.h"
#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <memory>
#include <string>
#include <vector>

using namespace llvm;

namespace ASTNodes{

    class BasicNode{
        public:
        virtual ~BasicNode() = default;
        virtual Value* code_gen() = 0;
    };

    class ConstantNode: public BasicNode{
      public:
        Type* constant_type;
        Value* constant_value;
        ConstantNode(){};
        Value* code_gen() override;
    };

    class VariableDefineNode: public BasicNode{
      public:
        Type* variable_type;
        std::string variable_name;
        VariableDefineNode(){};
        Value* code_gen() override;
    };

	class BinaryExprNode: public BasicNode{
      public:
		BinaryOper expr_op;
        std::unique_ptr<BasicNode> LHS, RHS;
        BinaryExprNode(){};
        Value* code_gen() override;
	};

    class CallNode: public BasicNode{
      public:
        std::string callee_name;
        std::vector<std::unique_ptr<BasicNode> > callee_args;
        CallNode(){};
        Value* code_gen() override;
    };

    class FunDeclareNode: public BasicNode{
      public:
        std::string function_name;
        std::vector<std::string> function_args;
        FunDeclareNode(){};
        Value* code_gen() override;
    };

    class FunctionNode: public BasicNode{
      public:
        std::unique_ptr<FunDeclareNode> func_declare;
        std::unique_ptr<BasicNode> func_body;
        FunctionNode(){};
        Value* code_gen() override;
    };

    class AssignNode: public BasicNode{
      public:
        std::unique_ptr<VarAccessNode> LHS;
        std::unique_ptr<BasicNode> RHS;
        AssignNode(){};
        Value* code_gen() override;
    };

    class StructDefineNode: public BasicNode{
      public:
        std::string struct_name;
        std::vector<llvm::Type*> struct_member_type;
        std::vector<std::string> struct_member_name;
        StructDefineNode(){};
        Value* code_gen() override;
    };

    class VarAccessNode: public BasicNode{
      public:
        std::string var_name;
        std::unique_ptr<VarAccessNode> nested_var = nullptr;
        VarAccessNode(){};
        AllocaInst* code_gen() override;
    };

    class SysWriteNode: public BasicNode{
      public:
        bool has_newline;
        std::vector<std::unique_ptr<BasicNode> > args;
        SysWriteNode(){};
        Value* code_gen() override;
    };

    class SysReadNode: public BasicNode{
      public:
        bool has_newline;
        std::vector<std::unique_ptr<VarAccessNode> > args;
        SysReadNode(){};
        Value* code_gen() override;
    };
}