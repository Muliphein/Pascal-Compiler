#include "BasicLLVM.h"
#include "ASTNodes.h"
#include "BasicType.h"
using namespace llvm;

static LLVMContext context;
static IRBuilder<> builder;
static std::shared_ptr<Module> module;


void build_basic_type()
{
    ShortIntType = Type::getInt8Ty(context);
    IntType = Type::getInt16Ty(context);
    LongIntType = Type::getIn32Ty(context);
    Int64Type = Type::getIn64Ty(context);

    ByteType = Type::getInt8Ty(context);
    WordType = Type::getInt16Ty(context);
    DwordType = Type::getIn32Ty(context);
    QwordType = Type::getIn64Ty(context);

    RealType = Type::getFloatTy(context);
    DoubleType = Type::getDoubleTy(context);
    ExtendType = Type::getExtendedType(context);

    CharType = Type::getInt8Ty(context);
    BoolType = Type::getInt1Ty(context);
}

void syscal_declare()
{
    std::vector<Type*> function_args;
    function_args.push_back(Type::getInt8PtrTy(the_context));
    FunctionType* printf_type = FunctionType::get(Type::getInt32Ty(the_context), function_args, true);
    Function* printf_fun = Function::Create(printf_type, Function::ExternalLinkage, "printf", the_module.get());
    FunctionType* scanf_type = FunctionType::get(Type::getInt32Ty(the_context), function_args, true);
    Function* scanf_fun = Function::Create(scanf_type, Function::ExternalLinkage, "scanf", the_module.get());
}

void Generator(ASTNodes::BasicNode* ASTRoot, std::string aim)
{
    module = std::make_shared<Module>("main", context);
    build_basic_type();
    syscal_declare();
    if (aim == "x86_64"){
        module->setDataLayout("e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128");
        module->setTargetTriple("x86_64-pc-linux-gnu");
    }
    ASTRoot->code_gen();
    module -> print(outs(), nullptr);

}