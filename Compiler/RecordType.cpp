#include "ASTNodes.h"

extern LLVMContext context;
extern IRBuilder<> builder;
extern std::shared_ptr<Module> module;


extern int stage;
extern std::map<std::string, Type*> type_map;// TypeName -> Type Pointer
extern std::map<Type*, std::string> name_map;// Type -> TypeName Pointer <Global>
extern std::map<Type*, Constant*> zero_initial;// Type -> zeroinitial

extern std::map<std::string, Value*> table_mem[MAX_NESTED];// VarName -> Memory
extern std::map<std::string, Type*> table_type[MAX_NESTED];// VarName -> Type
extern std::map<std::string, bool> table_array[MAX_NESTED];// VarName -> Array

extern std::map<Type*, std::vector<Type*> > record_type_list;// StructType -> Member_Type_List
extern std::map<Type*, std::vector<std::string> > record_member_name_list;// StructType -> Member_Name_List
extern std::map<Type*, std::vector<bool> > record_member_array;// StructType -> Member_var_ame_List


ASTNodes::CodeGenResult* ASTNodes::RecordTypeDefineNode::code_gen(){

    if (type_map.count(this->record_name)>0){
        throw new IRBuilderMeesage("[IRBuilder] Error : ReDefine the Record type <"+this->record_name+">");
    }

    StructType* struct_type = StructType::create(context, this->record_name);
    type_map[this->record_name] = struct_type;
    name_map[struct_type] = this->record_name;

    record_type_list[struct_type] = *new std::vector<Type*>;
    record_member_name_list[struct_type] = *new std::vector<std::string>;
    record_member_array[struct_type] = *new std::vector<bool>;

    std::vector<Type*> elements;
    for (int i=0; i<this->member_type_name.size(); ++i){
        if (type_map.count(this->member_type_name[i])==0){
            throw new IRBuilderMeesage("[IRBuilder] Error : Cant Find the Type <"+this->member_type_name[i]+">");
        }
        auto member_type = type_map[this->member_type_name[i]];
        if (this->mem_is_array[i]){
            elements.push_back(ArrayType::get(member_type, this->mem_arrag_length[i]));
        } else {
            elements.push_back(member_type);
        }
        record_type_list[struct_type].push_back(member_type);
        record_member_name_list[struct_type].push_back(this->member_var_name[i]);
        record_member_array[struct_type].push_back(this->mem_is_array[i]);
    }
    struct_type->setBody(elements);

    std::vector<Constant*> init_values;
    for (auto _type: record_type_list[struct_type]){
        init_values.push_back(zero_initial[_type]);
    }
    Constant* init = ConstantStruct::get(struct_type, init_values);
    zero_initial[struct_type] = init;

    return nullptr;
}
