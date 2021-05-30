#include "BasicType.h"
#include "BasicLLVM.h"
#include "ASTNodes.h"

extern LLVMContext context;
extern IRBuilder<> builder;
extern std::shared_ptr<Module> module;
// extern int stage;
// extern std::map<std::string, Type*> stage_table[];
extern std::map<std::string, GlobalVariable*> global_table;
extern std::map<std::string, Type*> global_table_type;
extern std::map<std::string, bool> global_table_array;

ASTNodes::CodeGenResult* ASTNodes::VariableDefineNode::code_gen(){

    if (this->is_global){
        if (global_table.count(this->name)>0){
            throw("Error : Redefine of "+this->name);
        }
        if (this->is_array){
            ArrayType* array_type = ArrayType::get(this->variable_type, this->array_length);
            std::vector <Constant*> init_values;
            Constant* zero; 
            if (this->variable_type == IntType){
                zero = ConstantInt::get(IntType, 0);
            } else if (this->variable_type == CharType){
                zero = ConstantInt::get(CharType, 0);
            } else if (this->variable_type == RealType){
                zero = ConstantFP::get(RealType, 0);
            } else if (this->variable_type == BoolType){
                zero = ConstantInt::get(BoolType, 0);
            } else {
                throw("Error : Unspport Type\n");
            }

            for (int i=0; i<this->array_length; ++i){
                init_values.push_back(zero);
            }
            Constant* init = ConstantArray::get(array_type, init_values);
            // set the initializer

            GlobalVariable* global_variable = new GlobalVariable(
                *(module.get()), array_type, false,
                GlobalVariable::ExternalLinkage, init, this->name
            );
            global_table[this->name] = global_variable;
            global_table_type[this->name] = this->variable_type;
            global_table_array[this->name] = true;
        } else {
            Constant* zero; 
            if (this->variable_type == IntType){
                zero = ConstantInt::get(IntType, 0);
            } else if (this->variable_type == CharType){
                zero = ConstantInt::get(CharType, 0);
            } else if (this->variable_type == RealType){
                zero = ConstantFP::get(RealType, 0);
            } else if (this->variable_type == BoolType){
                zero = ConstantInt::get(BoolType, 0);
            } else {
                throw("Error : Unspport Type\n");
            }
            GlobalVariable* global_variable = new GlobalVariable(
                *(module.get()), this->variable_type, false,
                GlobalVariable::ExternalLinkage, zero, this->name
            );
            global_table[this->name] = global_variable;
            global_table_type[this->name] = this->variable_type;
            global_table_array[this->name] = false;
        }
    } else {
        throw("Error : Unspport Local Variable");
    }
    return nullptr;
}

ASTNodes::CodeGenResult* ASTNodes::VarAccessNode::code_gen(){
    if (this->is_global){
        if (global_table.count(this->var_name)==0){
            throw("Error : Undefined of "+this->var_name);
        }
        
        GlobalVariable* pointer = global_table[this->var_name];
        auto _type = global_table_type[this->var_name];
        Value* _mem;
        if (global_table_array[this->var_name]){ // array Var
            _mem = builder.CreateGEP(pointer, {builder.getInt64(0), builder.getInt64(this->idx)});
        } else { // Simple Var;
            _mem = builder.CreateGEP(pointer, builder.getInt64(0));
        }
        // auto _value = builder.CreateLoad(_type, pointer);
        Value* _value=nullptr;
        return new CodeGenResult(_mem, _type, _value);
        
    } else {
        throw("Error : Unspport Local Variable");
    }
}
