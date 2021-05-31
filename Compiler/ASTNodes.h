#ifndef __ASTNODES_H__
#define __ASTNODES_H__

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

#include <cstdio>
#include <iostream>
#include <exception>

#define MAX_NESTED 50

using namespace llvm;
extern IRBuilder<> builder;

extern Type* ShortIntType; // 1 byte
extern Type* IntType;  // 2 byte *
extern Type* LongIntType;  // 4 byte
extern Type* Int64Type;    // 8 byte

extern Type* ByteType; // 1 byte Unsigned
extern Type* WordType; // 2 byte Unsigned
extern Type* DwordType;// 4 byte Unsigned
extern Type* QwordType;// 8 byte Unsigned

extern Type* RealType; // 4 byte float *
extern Type* DoubleType;   // 8 byte double
// extern Type* ExtendType;   // 10 byte ...

extern Type* CharType; // 1 byte *
extern Type* BoolType; // 1 bit *
extern Type* VoidType; // void * (procedure)

enum BinaryOper{
    GE,
    GT,
    LE,
    LT,
    EQUAL,
    UNEQUAL,
    OR,
    AND,
    MUL,
    DIVISION,
    DIV,
    MOD,
    PLUS,
    MINUS
};

class IRBuilderMeesage: public std::exception{
  private:
    std::string error_meesage;
  public:
    IRBuilderMeesage(std::string _error){error_meesage = _error;};
    std::string message(){
        return error_meesage;
    }
};

namespace ASTNodes{

    class CodeGenResult{
    private:
        Value* value;
    public:
        Value* mem;
        Type* type;

        CodeGenResult(Value* _mem, Type* _type, Value* _value){
            mem = _mem;
            type = _type;
            value = _value;
        }
        Value* get_value(){
            if (value == nullptr){
                if (mem == nullptr){
                    throw("Error : No Value And Mem for Variable, It's Unpossible\n");
                } else {
                    if (type == nullptr){
                        throw("Error : No type for Variable");
                    } else {
                        value = builder.CreateLoad(type, mem);
                    }
                }
            }
            return value;
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
        std::string var_name;
        std::shared_ptr<BasicNode> idx;
        std::shared_ptr<VarAccessNode> nested_var = nullptr;
        VarAccessNode(){};
        CodeGenResult* code_gen() override;
    };
    
    class VarBaseNode: public BasicNode{
    public:
        std::string var_name;
        std::shared_ptr<BasicNode> idx;
        std::shared_ptr<VarAccessNode> nested_var = nullptr;
        VarBaseNode(){};
        VarBaseNode(std::string _var_name, std::shared_ptr<BasicNode> _idx, std::shared_ptr<VarAccessNode> _nested_var){
            var_name = _var_name;
            idx = _idx;
            nested_var = _nested_var;
        };
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
        std::string type;
        bool is_array;
        int array_length;
        std::string name;
        VariableDefineNode(){};
        VariableDefineNode(std::string _type, bool _is_array, int _array_length, std::string _name){
            type = _type;
            is_array = _is_array;
            array_length=_array_length;
            name=_name;
        };
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
        std::string ret_type_name;
        std::vector<std::string> function_arg_types_names;
        std::vector<std::string> function_arg_names; // necessary
        FunDeclareNode(){};
        CodeGenResult* code_gen() override;
    };

    class FunctionBodyNode: public BasicNode{ // Will Add New Block And New Table And New Variable In Parameters
      public:
        std::vector<std::shared_ptr<BasicNode> > stmts;
        FunctionBodyNode(){};
        CodeGenResult* code_gen() override;
    };

    class FunctionNode: public BasicNode{
    public:
        std::shared_ptr<FunDeclareNode> func_declare;
        std::shared_ptr<FunctionBodyNode> func_body;
        FunctionNode(){};
        std::string get_name();
        CodeGenResult* code_gen() override;
    };

    class AssignNode: public BasicNode{
    public:
        std::shared_ptr<VarBaseNode> LHS;
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
        std::vector<std::shared_ptr<VarBaseNode> > args;
        SysReadNode(){};
        CodeGenResult* code_gen() override;
    };

    class StmtSeqNode: public BasicNode{ // will add to Table Stages
    public:
        std::vector<std::shared_ptr<BasicNode> > stmts;
        StmtSeqNode(){};
        CodeGenResult* code_gen() override;
    };

    class ProgramNode: public BasicNode{ // won't add to Table Stages
      public:
        std::vector<std::shared_ptr<BasicNode> > parts;
        ProgramNode(){};
        CodeGenResult* code_gen() override;
    };

    class ReturnNode: public BasicNode{
      public:
        ReturnNode(){};
        CodeGenResult* code_gen() override;
    };

    class RecordTypeDefineNode: public BasicNode{
      public:
        std::string record_name; // rec
        std::vector<std::string> member_var_name; // a
        std::vector<std::string> member_type_name; // integer
        std::vector<bool> mem_is_array; //false
        std::vector<int> mem_arrag_length; //0
        
        RecordTypeDefineNode(){};
        CodeGenResult* code_gen() override;
    };

    class FunctionCallNode: public BasicNode{
      public:
        std::string func_name;
        std::vector<std::shared_ptr<BasicNode> > args;

        FunctionCallNode(){};
        CodeGenResult* code_gen() override;
    };

    class RepeatNode: public BasicNode{
      public:
        std::shared_ptr<BasicNode> rep_con;
        bool reverse; // false When Meet Rep ---- true When Meen Jump Out
        bool is_start; // false At End Rep Condition ---- true At Begin Rep Condition
        std::shared_ptr<BasicNode> rep_body_node;
        RepeatNode(){};
        CodeGenResult* code_gen() override;
    };

    class IfElseNode: public BasicNode{
      public:
        std::shared_ptr<BasicNode> cond;
        std::shared_ptr<BasicNode> then_body;
        std::shared_ptr<BasicNode> else_body;
        CodeGenResult* code_gen() override;
    };

}

#endif