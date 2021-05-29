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
#include <iostream>

using namespace llvm;

static LLVMContext the_context;
static IRBuilder<> builder(the_context);
static std::shared_ptr<Module> the_module;
static std::map<std::string, Value*> named_values;
// static Module the_module2;
// conText Module BasicBlock Stmt
int main() {

    { // Module Make
        the_module = std::make_shared<Module>("test", the_context);
        the_module->setDataLayout("e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128");
        the_module->setTargetTriple("x86_64-pc-linux-gnu");
    }

    { // Struct Decleration
        StructType* struct_type = StructType::create(the_context, "MyStruct");
        std::vector <Type*> elements;
        elements.push_back(Type::getInt32Ty(the_context));
        elements.push_back(Type::getInt32Ty(the_context));
        elements.push_back(Type::getDoubleTy(the_context));
        struct_type->setBody(elements);


        // to see the influence
        std::vector<Type*> function_args;
        PointerType *p_struct = PointerType::get(struct_type, 0);
        function_args.push_back(p_struct);
        FunctionType* fuck_type = FunctionType::get(Type::getInt32Ty(the_context), function_args, false);
        Function* fuck_fun = Function::Create(fuck_type, Function::ExternalLinkage, "fuck", the_module.get());

    }

    { // printf Declaration
        std::vector<Type*> function_args;
        function_args.push_back(Type::getInt8PtrTy(the_context));
        FunctionType* printf_type = FunctionType::get(Type::getInt32Ty(the_context), function_args, true);
        Function* printf_fun = Function::Create(printf_type, Function::ExternalLinkage, "printf", the_module.get());
    }

    { // Function Declaration
        std::vector<Type*> function_args;
        function_args.push_back(Type::getInt32Ty(the_context));
        function_args.push_back(Type::getInt32Ty(the_context));

        FunctionType* max_type = FunctionType::get(Type::getInt32Ty(the_context), function_args, false);
        Function* max_fun = Function::Create(max_type, Function::ExternalLinkage, "max", the_module.get());

        unsigned Idx = 0;
        auto arg_it = max_fun->arg_begin();
        auto arg_a = arg_it++;
        arg_a->setName("a");
        auto arg_b = arg_it++;
        arg_b->setName("b");
    }


    { // Function Constructor
        Function* TheFunction = the_module->getFunction("max");

        BasicBlock* BB = BasicBlock::Create(the_context, "max_entry", TheFunction);
        builder.SetInsertPoint(BB);
        auto arg_it = TheFunction->arg_begin();
        auto arg_a = arg_it++;
        auto arg_b = arg_it++;
        Value* cmp_value = builder.CreateICmpSGT(arg_a, arg_b);

        // Temper Value
        AllocaInst* var = builder.CreateAlloca(Type::getInt32Ty(the_context), nullptr, "t");
        auto var_pos = builder.CreateGEP(var, builder.getInt32(0));
        builder.CreateStore(ConstantInt::get(Type::getInt32Ty(the_context), 5), var_pos);
        auto temp = builder.CreateLoad(Type::getInt32Ty(the_context), var_pos);
        auto temp1 = builder.CreateLShr(temp, 2);
        builder.CreateStore(temp1, var_pos);

        BasicBlock* if_then = BasicBlock::Create(the_context, "if_then", TheFunction);
        BasicBlock* if_else = BasicBlock::Create(the_context, "if_else", TheFunction);
        builder.CreateCondBr(cmp_value, if_then, if_else);
        builder.SetInsertPoint(if_then);
        builder.CreateRet(arg_a);
        builder.SetInsertPoint(if_else);
        auto res = builder.CreateLoad(Type::getInt32Ty(the_context), var);
        builder.CreateRet(temp);
    }


    { // Main Constructor

        {
            FunctionType* main_type = FunctionType::get(Type::getInt32Ty(the_context), false);
            Function* main_fun = Function::Create(main_type, Function::ExternalLinkage, "main", the_module.get());
        }

        {
            Function* main_fun = the_module->getFunction("main");
            BasicBlock* main_entry = BasicBlock::Create(the_context, "main_entry", main_fun);
            builder.SetInsertPoint(main_entry);
        }

        {
            auto a_value = ConstantInt::get(Type::getInt32Ty(the_context), -10);
            auto b_value = ConstantInt::get(Type::getInt32Ty(the_context), 20);

            std::vector <Value*> put_args;
            put_args.push_back(a_value);
            put_args.push_back(b_value);

            ArrayRef <Value*> args_Ref(put_args);
            Function* TheFunction = the_module->getFunction("max");
            Value *ret = builder.CreateCall(TheFunction, args_Ref);
        }
        
        {
            
            GlobalVariable *globalVar = new GlobalVariable(*(the_module.get()), Type::getInt32Ty(the_context),  false,
              GlobalValue::ExternalLinkage, ConstantInt::get(Type::getInt32Ty(the_context), 0), "fuck");

            char s[13]="hello world\n";
            std::vector<llvm::Constant*> values;
            Constant* c = ConstantInt::get(Type::getInt8Ty(the_context), 0);
            for (int i=0; i<13; ++i) values.push_back(ConstantInt::get(Type::getInt8Ty(the_context), s[i]));
            Constant* init =ConstantArray::get(ArrayType::get(Type::getInt8Ty(the_context), 13), values);
        
            GlobalVariable *globalStr = new GlobalVariable(*(the_module.get()), ArrayType::get(Type::getInt8Ty(the_context), 13),  false,
              GlobalValue::ExternalLinkage, init, "fuck_string");

            Function* TheFunction =the_module->getFunction("printf");
            
            //Important
            // global variable is a pointer
            // 0 -> point to the array's pointer
            // 1 -> point to the array[index] 's position
            // always the position , need use load and store
            auto res = builder.CreateGEP(globalStr, {builder.getInt32(0), builder.getInt32(0)});
            auto modify = builder.CreateGEP(globalStr, {builder.getInt32(0), builder.getInt32(1)});
            builder.CreateStore(ConstantInt::get(Type::getInt8Ty(the_context), 48), modify);

            std::vector <Value*> put_argss;
            put_argss.push_back(res);
            ArrayRef  <Value*> printf_Ref(put_argss);
            builder.CreateCall(TheFunction, printf_Ref);
        }

        {
            auto ret = ConstantInt::get(Type::getInt32Ty(the_context), 0);
            builder.CreateRet(ret);
        }
    }




    the_module -> print(outs(), nullptr);
}