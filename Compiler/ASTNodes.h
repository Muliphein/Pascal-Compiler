#ifndef __ASTNODES_H__
#define __ASTNODES_H__

#include "BinaryOp.h"
#include "BasicLLVM.h"
#include <iostream>

#define MAX_NESTED 50

using namespace llvm;
extern IRBuilder<> builder;
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
        std::shared_ptr<BasicNode> val;
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

}

#endif