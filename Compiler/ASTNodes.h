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

extern std::shared_ptr<Module> module;

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
                    module->print(outs(), nullptr);
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
        virtual void out_put(int tab_length = 0) = 0;
    };

    class VarAccessNode: public BasicNode{
    public:
        std::string var_name;
        std::shared_ptr<BasicNode> idx;
        std::shared_ptr<VarAccessNode> nested_var = nullptr;
        VarAccessNode(){};
        CodeGenResult* code_gen() override;

        void out_put(int tab_length = 0) override{
            for (int i=0; i<tab_length; ++i){
                std::cerr<<"\t";
            }
            std::cerr<<" Access "<< this->var_name << std::endl;
        }

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
        void out_put(int tab_length = 0) override{
            for (int i=0; i<tab_length; ++i){
                std::cerr<<"\t";
            }
            std::cerr<<" Base "<< this->var_name << std::endl;
            for (int i=0; i<tab_length; ++i){
                std::cerr<<"\t";
            }
            std::cerr<<" Index : " << std::endl;
            if (this->idx != nullptr) this->idx->out_put(tab_length+1);
            for (int i=0; i<tab_length; ++i){
                std::cerr<<"\t";
            }
            std::cerr<<" Nested Var : " << std::endl;
            if (this->nested_var != nullptr) this->nested_var->out_put(tab_length+1);
        }
    };

    class ConstantNode: public BasicNode{
    public:
        Type* constant_type;
        Value* constant_value;
        ConstantNode(){};
        CodeGenResult* code_gen() override;
        void out_put(int tab_length = 0) override{
            for (int i=0; i<tab_length; ++i){
                std::cerr<<"\t";
            }
            std::cerr<<" Constant " << std::endl;
        }
    };

    class VariableDefineNode: public BasicNode{
    public:
        std::string type;
        bool is_array;
        int array_length;
        int lower_bound;
        std::string name;
        VariableDefineNode(){};
        VariableDefineNode(std::string _type, bool _is_array, int _array_length, std::string _name){
            type = _type;
            is_array = _is_array;
            array_length=_array_length;
            name=_name;
        };
        CodeGenResult* code_gen() override;
        void out_put(int tab_length = 0) override{
            for (int i=0; i<tab_length; ++i){
                std::cerr<<"\t";
            }
            std::cerr<<" Define [" << this->name << "] Type: <" << this->type << ">" << std::endl;
        }
    };

	class BinaryExprNode: public BasicNode{
    public:
		BinaryOper expr_op;
        std::shared_ptr<BasicNode> LHS, RHS;
        BinaryExprNode(){};
        CodeGenResult* code_gen() override;
        void out_put(int tab_length = 0) override{
            for (int i=0; i<tab_length; ++i){
                std::cerr<<"\t";
            }
            std::cerr<<" Oper [" << this->expr_op << std::endl;
            this->LHS->out_put(tab_length+1);
            this->RHS->out_put(tab_length+1);
        }
	};
    class FunDeclareNode: public BasicNode{
    public:
        std::string function_name;
        std::string ret_type_name;
        std::vector<std::string> function_arg_types_names;
        std::vector<std::string> function_arg_names; // necessary
        std::vector<bool> function_arg_var;
        FunDeclareNode(){};
        CodeGenResult* code_gen() override;
        void out_put(int tab_length = 0) override{
            for (int i=0; i<tab_length; ++i){
                std::cerr<<"\t";
            }
            std::cerr<<" Function Declare [" << this->function_name << "] Return : <" << this->ret_type_name << ">" << std::endl;
        }
    };

    class FunctionBodyNode: public BasicNode{ // Will Add New Block And New Table And New Variable In Parameters
      public:
        std::vector<std::shared_ptr<BasicNode> > stmts;
        FunctionBodyNode(){};
        CodeGenResult* code_gen() override;
        void out_put(int tab_length = 0) override{
            for (int i=0; i<tab_length; ++i){
                std::cerr<<"\t";
            }
            std::cerr<<" Function Body " << std::endl;
			for (int i = 0; i < this->stmts.size(); ++i) {
				this->stmts[i]->out_put(tab_length + 1);
			}
        }
    };

    class FunctionNode: public BasicNode{
    public:
        std::shared_ptr<FunDeclareNode> func_declare;
        std::shared_ptr<FunctionBodyNode> func_body;
        FunctionNode(){};
        std::string get_name();
        CodeGenResult* code_gen() override;
        void out_put(int tab_length = 0) override{
            for (int i=0; i<tab_length; ++i){
                std::cerr<<"\t";
            }
            std::cerr<<" Function Node " << std::endl;
            this->func_declare->out_put(tab_length+1);
            this->func_body->out_put(tab_length+1);
        }
    };

    class AssignNode: public BasicNode{
    public:
        std::shared_ptr<VarBaseNode> LHS;
        std::shared_ptr<BasicNode> RHS;
        AssignNode(){};
        CodeGenResult* code_gen() override;
        void out_put(int tab_length = 0) override{
            for (int i=0; i<tab_length; ++i){
                std::cerr<<"\t";
            }
            std::cerr<<" Assign Node " << std::endl;
            this->LHS->out_put(tab_length+1);
            this->RHS->out_put(tab_length+1);
        }
    };

    class SysWriteNode: public BasicNode{
    public:
        bool has_newline;
        std::vector<std::shared_ptr<BasicNode> > args;
        SysWriteNode(){};
        CodeGenResult* code_gen() override;
        
        void out_put(int tab_length = 0) override{
            for (int i=0; i<tab_length; ++i){
                std::cerr<<"\t";
            }
            std::cerr<<" SystemWrite Node " << std::endl;
            for (int i=0; i<this->args.size(); ++i){
                this->args[i]->out_put(tab_length+1);
            }
        }
    };

    class SysReadNode: public BasicNode{
    public:
        bool has_newline;
        std::vector<std::shared_ptr<VarBaseNode> > args;
        SysReadNode(){};
        CodeGenResult* code_gen() override;
        void out_put(int tab_length = 0) override{
            for (int i=0; i<tab_length; ++i){
                std::cerr<<"\t";
            }
            std::cerr<<" SystemRead Node " << std::endl;
            for (int i=0; i<this->args.size(); ++i){
                this->args[i]->out_put(tab_length+1);
            }
        }
    };

    class StmtSeqNode: public BasicNode{ // will add to Table Stages
    public:
        std::vector<std::shared_ptr<BasicNode> > stmts;
        StmtSeqNode(){};
        CodeGenResult* code_gen() override;
        void out_put(int tab_length = 0) override{
            for (int i=0; i<tab_length; ++i){
                std::cerr<<"\t";
            }
            std::cerr<<" Stmt Node " << std::endl;
            for (int i=0; i<this->stmts.size(); ++i){
                this->stmts[i]->out_put(tab_length+1);
            }
        }
    };

    class ProgramNode: public BasicNode{ // won't add to Table Stages
      public:
        std::vector<std::shared_ptr<BasicNode> > parts;
        ProgramNode(){};
        CodeGenResult* code_gen() override;
        void out_put(int tab_length = 0) override{
            for (int i=0; i<tab_length; ++i){
                std::cerr<<"\t";
            }
            std::cerr<<" Program Node : Size = " << this->parts.size() <<std::endl;
            for (int i=0; i<this->parts.size(); ++i){
                this->parts[i]->out_put(tab_length+1);
            }
        }
    };

    class ReturnNode: public BasicNode{
      public:
        ReturnNode(){};
        CodeGenResult* code_gen() override;
        void out_put(int tab_length = 0) override{
            for (int i=0; i<tab_length; ++i){
                std::cerr<<"\t";
            }
            std::cerr<<" Return Node " << std::endl;
        }
    };

    class RecordTypeDefineNode: public BasicNode{
      public:
        std::string record_name; // rec
        std::vector<std::string> member_var_name; // a
        std::vector<std::string> member_type_name; // integer
        std::vector<bool> mem_is_array; //false
        std::vector<int> mem_array_length; //0
        std::vector<int> mem_array_lower;
        
        RecordTypeDefineNode(){};
        CodeGenResult* code_gen() override;
        void out_put(int tab_length = 0) override{
            for (int i=0; i<tab_length; ++i){
                std::cerr<<"\t";
            }
            std::cerr<<" Record Type Define Node [" << this->record_name <<"]" << std::endl;
        }
    };

    class FunctionCallNode: public BasicNode{
      public:
        std::string func_name;
        std::vector<std::shared_ptr<BasicNode> > args;

        FunctionCallNode(){};
        CodeGenResult* code_gen() override;
        void out_put(int tab_length = 0) override{
            for (int i=0; i<tab_length; ++i){
                std::cerr<<"\t";
            }
            std::cerr<<" Function Call Node [" << this->func_name <<"]" << std::endl;
        }
    };

    class RepeatNode: public BasicNode{
      public:
        std::shared_ptr<BasicNode> rep_con;
        bool reverse; // false When Meet Rep ---- true When Meen Jump Out
        bool is_start; // false At End Rep Condition ---- true At Begin Rep Condition
        std::shared_ptr<BasicNode> rep_body_node;
        RepeatNode(){};
        CodeGenResult* code_gen() override;
        void out_put(int tab_length = 0) override{
            for (int i=0; i<tab_length; ++i){
                std::cerr<<"\t";
            }
            std::cerr<<" Repeat Node " << std::endl;
            this->rep_con->out_put(tab_length);
            std::cerr<<" Rep Con ↑ Rep Body ↓ " << std::endl;
            this->rep_body_node->out_put(tab_length);        
        }
    };

    class IfElseNode: public BasicNode{
      public:
        std::shared_ptr<BasicNode> cond;
        std::shared_ptr<BasicNode> then_body;
        std::shared_ptr<BasicNode> else_body;
        CodeGenResult* code_gen() override;
        void out_put(int tab_length = 0) override{
            for (int i=0; i<tab_length; ++i){
                std::cerr<<"\t";
            }
            std::cerr<<" If-Else Node " << std::endl;
            this->cond->out_put(tab_length);
            std::cerr<<" If Con ↑" << std::endl;
            this->then_body->out_put(tab_length);  
            std::cerr<<" Then ↑ Else ↓ " << std::endl;   
            this->else_body->out_put(tab_length);     
        }
    };

    class ForNode: public BasicNode{
      public:
        std::string loop_var;
        std::shared_ptr<BasicNode> start_val;
        std::shared_ptr<BasicNode> end_val;
        std::shared_ptr<BasicNode> loop_body;
        bool is_to; // true to ; false downto
        CodeGenResult* code_gen() override;
        void out_put(int tab_length = 0) override{
            for (int i=0; i<tab_length; ++i){
                std::cerr<<"\t";
            }
            std::cerr<<" For Node  var [" << loop_var<< "]" << std::endl;
            this->start_val->out_put(tab_length);
            this->end_val->out_put(tab_length);
			this->loop_body->out_put(tab_length + 1);
        }
    };

}

#endif