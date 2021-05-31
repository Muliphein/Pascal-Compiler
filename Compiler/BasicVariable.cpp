#include "ASTNodes.h"

extern LLVMContext context;
extern IRBuilder<> builder;
extern std::shared_ptr<Module> module;

extern int stage;
extern std::map<std::string, Type*> type_map;// TypeName -> Type Pointer
extern std::map<Type*, Constant*> zero_initial;// Type -> zeroinitial

extern std::map<std::string, Value*> table_mem[MAX_NESTED];// VarName -> Memory
extern std::map<std::string, Type*> table_type[MAX_NESTED];// VarName -> Type
extern std::map<std::string, bool> table_array[MAX_NESTED];// VarName -> Array

extern std::map<Type*, std::vector<Type*> > record_type_list;// StructType -> Member_Type_List
extern std::map<Type*, std::vector<std::string> > record_member_name_list;// StructType -> Member_Name_List
extern std::map<Type*, std::vector<bool> > record_member_array;// StructType -> Member_Name_List

bool is_basic_type(Type* _type){

    if (_type == ShortIntType){
        return true;
    } else if (_type == IntType){
        return true;
    } else if (_type == LongIntType){
        return true;
    } else if (_type == Int64Type){
        return true;
    } else if (_type == ByteType){
        return true;
    } else if (_type == WordType){
        return true;
    } else if (_type == DwordType){
        return true;
    } else if (_type == QwordType){
        return true;
    } else if (_type == RealType){
        return true;
    } else if (_type == DoubleType){
        return true;
    } else if (_type == CharType){
        return true;
    } else if (_type == BoolType){
        return true;
    }

    return false;
}

ASTNodes::CodeGenResult* ASTNodes::VariableDefineNode::code_gen(){
    if (stage == 0){ // Do on the Global Table
        if (type_map.count(this->type)==0){
            throw new IRBuilderMeesage("[IRBuilder] Error : Can't Find the Type <"+this->type+">");
        }
        Type* variable_type = type_map[this->type];
        if (table_mem[stage].count(this->name)>0){
            throw new IRBuilderMeesage("[IRBuilder] Error : reDefine of <"+this->name+">");
        }
        if (this->is_array){
            ArrayType* array_type = ArrayType::get(variable_type, this->array_length);
            
            std::vector<llvm::Constant*> init_values;
            for (int i=0; i<this->array_length; ++i) init_values.push_back(zero_initial[variable_type]);
            Constant* init = ConstantArray::get(array_type, init_values);

            GlobalVariable* global_variable = new GlobalVariable(
                *(module.get()), array_type, false,
                GlobalVariable::ExternalLinkage, init, this->name
            );
            table_mem[stage][this->name] = global_variable;
            table_type[stage][this->name] = variable_type;
            table_array[stage][this->name] = true;
        } else {
            GlobalVariable* global_variable = new GlobalVariable(
                *(module.get()), variable_type, false,
                GlobalVariable::ExternalLinkage, zero_initial[variable_type], this->name
            );
            table_mem[stage][this->name] = global_variable;
            table_type[stage][this->name] = variable_type;
            table_array[stage][this->name] = false;
        }
    } else {
        if (type_map.count(this->type)==0){
            throw new IRBuilderMeesage("[IRBuilder] Error : Can't Find the Type <"+this->type+">");
        }
        Type* variable_type = type_map[this->type];
        
        if (table_mem[stage].count(this->name)>0){
            throw new IRBuilderMeesage("[IRBuilder] Error : reDefine of <"+this->name+">");
        }
        if (this->is_array){
            ArrayType* array_type = ArrayType::get(variable_type, this->array_length);
            AllocaInst* local_variable = builder.CreateAlloca(array_type, nullptr, this->name);

            table_mem[stage][this->name] = local_variable;
            table_type[stage][this->name] = variable_type;
            table_array[stage][this->name] = true;
        } else {
            AllocaInst* local_variable = builder.CreateAlloca(variable_type, nullptr, this->name);
            table_mem[stage][this->name] = local_variable;
            table_type[stage][this->name] = variable_type;
            table_array[stage][this->name] = false;
        }
    }
    return nullptr;
}

extern std::vector<Value*> idx_set;

ASTNodes::CodeGenResult* ASTNodes::VarAccessNode::code_gen(){
    if (this->nested_var == nullptr){
        for (int stage_pointer = stage; stage_pointer>=0; stage_pointer--){
            if (table_mem[stage_pointer].count(this->var_name)>0){
                Value* pointer = table_mem[stage_pointer][this->var_name];
                auto _type = table_type[stage_pointer][this->var_name];
                Value* _mem = pointer;
                if (table_array[stage_pointer][this->var_name]){ // array Var
                    Value* array_idx = this->idx->code_gen()->get_value();
                    idx_set.push_back(builder.getInt64(0));
                    idx_set.push_back(array_idx);
                } else { // Simple Var;
                    idx_set.push_back(builder.getInt64(0));
                }
                return new CodeGenResult(_mem, _type, nullptr);
            }
        }
        throw new IRBuilderMeesage("[IRBuilder] Error : unDefine of <"+this->var_name+">");
    } else {
        CodeGenResult* temp = this->nested_var->code_gen();
        Value* _mem = temp->mem;
        Type* _type = nullptr;
        Type* above_type = temp->type;
        std::vector<Type*> above_type_list = record_type_list[above_type];
        std::vector<std::string> above_name_list = record_member_name_list[above_type];
        std::vector<bool> above_array_list = record_member_array[above_type];
        int struct_position = -1;
        for (int i=0; i<above_type_list.size(); ++i){
            if (above_name_list[i] == this->var_name){
                struct_position = i;
                _type = above_type_list[i];
            }
        }
        if (above_array_list[struct_position]){ //array Var
            Value* array_idx = this->idx->code_gen()->get_value();
            idx_set.push_back(builder.getInt32(struct_position));
            idx_set.push_back(array_idx);
        } else { // Simple Var
            idx_set.push_back(builder.getInt32(struct_position));
        }
        return new CodeGenResult(_mem, _type, nullptr);
    }
}

ASTNodes::CodeGenResult* ASTNodes::VarBaseNode::code_gen(){
    int now_size = idx_set.size();
    if (this->nested_var == nullptr){
        for (int stage_pointer=stage; stage_pointer>=0; --stage_pointer){
            if (table_mem[stage_pointer].count(this->var_name)>0){
                Value* pointer = table_mem[stage_pointer][this->var_name];
                auto _type = table_type[stage_pointer][this->var_name];
                Value* _mem = pointer;
                if (table_array[stage_pointer][this->var_name]){ // array Var
                    Value* array_idx = this->idx->code_gen()->get_value();
                    idx_set.push_back(builder.getInt64(0));
                    idx_set.push_back(array_idx);
                } else { // Simple Var;
                    idx_set.push_back(builder.getInt64(0));
                }
                std::vector<Value*> now_set;
                now_set.clear();
                for (int i=now_size; i<idx_set.size(); ++i){
                    now_set.push_back(idx_set[i]);
                }
                while(idx_set.size()>now_size)
                    idx_set.pop_back();
                ArrayRef<Value*> idx_ref(now_set);
                _mem = builder.CreateGEP(_mem, idx_ref);
                return new CodeGenResult(_mem, _type, nullptr);
            }
        }
        throw new IRBuilderMeesage("[IRBuilder] Error : unDefine of <"+this->var_name+">");
    } else {
        CodeGenResult* temp = this->nested_var->code_gen();
        Value* _mem = temp->mem;
        Type* _type = nullptr;
        Type* above_type = temp->type;
        std::vector<Type*> above_type_list = record_type_list[above_type];
        std::vector<std::string> above_name_list = record_member_name_list[above_type];
        std::vector<bool> above_array_list = record_member_array[above_type];
        int struct_position = -1;
        for (int i=0; i<above_type_list.size(); ++i){
            if (above_name_list[i] == this->var_name){
                struct_position = i;
                _type = above_type_list[i];
            }
        }
        if (above_array_list[struct_position]){ //array Var
            Value* array_idx = this->idx->code_gen()->get_value();
            idx_set.push_back(builder.getInt32(struct_position));
            idx_set.push_back(array_idx);
        } else { // Simple Var
            idx_set.push_back(builder.getInt32(struct_position));
        }
        
        std::vector<Value*> now_set;
        now_set.clear();
        for (int i=now_size; i<idx_set.size(); ++i){
            now_set.push_back(idx_set[i]);
        }
        while(idx_set.size()>now_size)
            idx_set.pop_back();
        ArrayRef<Value*> idx_ref(now_set);
        _mem = builder.CreateGEP(_mem, idx_ref);
        return new CodeGenResult(_mem, _type, nullptr);
    }
}
