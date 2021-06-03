#include "ASTNodes.h"
using namespace llvm;

LLVMContext context;
IRBuilder<> builder(context);
std::shared_ptr<Module> module;
std::vector<Value*> idx_set;

int stage = 0;
std::map<std::string, Type*> type_map;// TypeName -> Type Pointer
std::map<Type*, std::string> name_map;// Type -> TypeName Pointer <Global>
std::map<Type*, Constant*> zero_initial;// Type -> zeroinitial
std::string now_function;

std::map<std::string, Value*> table_mem[MAX_NESTED];// VarName -> Memory
std::map<std::string, Type*> table_type[MAX_NESTED];// VarName -> Type
std::map<std::string, bool> table_array[MAX_NESTED];// VarName -> Array
std::map<Function*, std::vector<bool> > function_var_arg;// Function* -> Var args array

std::map<Type*, std::vector<Type*> > record_type_list;// StructType -> Member_Type_List
std::map<Type*, std::vector<std::string> > record_member_name_list;// StructType -> Member_Name_List
std::map<Type*, std::vector<bool> > record_member_array;// StructType -> Member_Name_List

Type* ShortIntType; // 1 byte
Type* IntType;  // 2 byte *
Type* LongIntType;  // 4 byte
Type* Int64Type;    // 8 byte

Type* ByteType; // 1 byte Unsigned
Type* WordType; // 2 byte Unsigned
Type* DwordType;// 4 byte Unsigned
Type* QwordType;// 8 byte Unsigned

Type* RealType; // 4 byte float *
Type* DoubleType;   // 8 byte double
// Type* ExtendType;   // 10 byte ...

Type* CharType; // 1 byte *
Type* BoolType; // 1 bit *
Type* VoidType;

void build_basic_type()
{
    ShortIntType = Type::getInt8Ty(context);
    IntType = Type::getInt16Ty(context);
    LongIntType = Type::getInt32Ty(context);
    Int64Type = Type::getInt64Ty(context);

    ByteType = Type::getInt8Ty(context);
    WordType = Type::getInt16Ty(context);
    DwordType = Type::getInt32Ty(context);
    QwordType = Type::getInt64Ty(context);

    RealType = Type::getFloatTy(context);
    DoubleType = Type::getDoubleTy(context);
    // ExtendType = Type::getExtendedType(context);
    VoidType = Type::getVoidTy(context);

    CharType = Type::getInt8Ty(context);
    BoolType = Type::getInt1Ty(context);

    type_map["char"] = ByteType;
    name_map[ByteType] = "char";
    zero_initial[ByteType] = ConstantInt::get(ByteType, 0);

    type_map["integer"] = IntType;
    name_map[IntType] = "integer";
    zero_initial[IntType] = ConstantInt::get(IntType, 0);

    type_map["real"] = RealType;
    name_map[RealType] = "real";
    zero_initial[RealType] = ConstantFP::get(RealType, 0);
    
    type_map["bool"] = BoolType;
    name_map[BoolType] = "bool";
    zero_initial[BoolType] = ConstantInt::get(BoolType, 0);

    type_map["void"] = VoidType;
    name_map[VoidType] = "void";

}

void syscal_declare()
{
    std::vector<Type*> function_args;
    function_args.push_back(Type::getInt8PtrTy(context));
    FunctionType* printf_type = FunctionType::get(Type::getInt32Ty(context), function_args, true);
    Function* printf_fun = Function::Create(printf_type, Function::ExternalLinkage, "printf", module.get());
    FunctionType* scanf_type = FunctionType::get(Type::getInt32Ty(context), function_args, true);
    Function* scanf_fun = Function::Create(scanf_type, Function::ExternalLinkage, "scanf", module.get());
}

void gene_init(std::string name)
{
    module = std::make_shared<Module>(name, context);
    build_basic_type();
    syscal_declare();
    if (true){
        module->setDataLayout("e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128");
        module->setTargetTriple("x86_64-pc-linux-gnu");
    }
}

void generator(ASTNodes::BasicNode* ASTRoot)
{
    ASTRoot->code_gen();
    module -> print(outs(), nullptr);
}