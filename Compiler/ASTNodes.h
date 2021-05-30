#ifndef __ASTNODES_H__
#define __ASTNODES_H__

#include "BinaryOp.h"
#include "BasicLLVM.h"
#include <iostream>


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
                        // std::cerr<<"Before Load"<<std::endl;
                        value = builder.CreateLoad(type, mem);
                        // std::cerr<<"End Load"<<std::endl;
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
        static std::vector<Value*> idx_set;
        static int depth;
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
        std::string type;
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

}

#endif