#include "SystemCall.h"
#include "BasicType.h"

extern LLVMContext context;
extern IRBuilder<> builder;
extern std::shared_ptr<Module> module;

ASTNodes::CodeGenResult* ASTNodes::SysReadNode::code_gen(){
    std::string _string="";
    std::vector<CodeGenResult*> code_gen_args;
    std::vector<Value*> scanf_args;
    scanf_args.push_back(nullptr);
    code_gen_args.push_back(nullptr);
    for (auto arg: this->args){
        ASTNodes::CodeGenResult* temp=arg->code_gen();
        code_gen_args.push_back(temp);
        if (temp->type == IntType){
            _string += "%hd";
            scanf_args.push_back(temp->mem);
        } else if (temp->type == CharType){
            _string += "%c";
            scanf_args.push_back(temp->mem);
        } else if (temp->type == RealType){
            _string += "%f";
            scanf_args.push_back(temp->mem);
        } else if (temp->type == BoolType){ // Special for Bool Type
            _string += "%d";
            AllocaInst* _int_space = builder.CreateAlloca(Int64Type, nullptr, "temp");
            auto _var_int = builder.CreateGEP(_int_space, builder.getInt64(0));
            scanf_args.push_back(_var_int);
        } else {
            throw "Wrong Type In Read(ln)\n";
        }
    }
    if (this->has_newline){
        _string += "%*[^\n]";
    }
    GlobalVariable* format_string = builder.CreateGlobalString(_string);
    Value* format= builder.CreateGEP(format_string, {builder.getInt64(0), builder.getInt64(0)});
    Function* scanf_function=module->getFunction("scanf");
    scanf_args[0] = format;
    ArrayRef <Value*> scanf_ref(scanf_args);
    auto scanf_res = builder.CreateCall(scanf_function, scanf_ref);

    for (int i=1; i<code_gen_args.size(); ++i){ // Get the Result to Bool Type
        if (code_gen_args[i]->type == BoolType){
            Value* read_int = builder.CreateLoad(Int64Type, scanf_args[i]);
            Value* cmp_res = builder.CreateICmpNE(read_int, ConstantInt::get(Int64Type, 0));
            builder.CreateStore(cmp_res, code_gen_args[i]->mem);
        }
    }

    CodeGenResult* ret = new CodeGenResult(nullptr, nullptr, scanf_res);

    return ret;
}

ASTNodes::CodeGenResult* ASTNodes::SysWriteNode::code_gen(){
    std::string _string="";
    std::vector<Value*> printf_args;
    printf_args.push_back(nullptr);

    for (auto arg: this->args){
        ASTNodes::CodeGenResult* temp=arg->code_gen();
        if (temp->type == IntType){
            _string += "%hd";
            printf_args.push_back(temp->get_value());
        } else if (temp->type == CharType){
            _string += "%c";
            printf_args.push_back(temp->get_value());
        } else if (temp->type == RealType){
            _string += "%f";
            printf_args.push_back(temp->get_value());
        } else if (temp->type == BoolType){ // Special Zero Extented for BoolType
            _string += "%d";
            Value * res = builder.CreateZExt(temp->get_value(), Int64Type);
            printf_args.push_back(res);
        } else {
            throw "Wrong Type In Read(ln)";
        }
    }

    if (this->has_newline){
        _string += "\n";
    }

    GlobalVariable* format_string = builder.CreateGlobalString(_string);
    Value* format= builder.CreateGEP(format_string, {builder.getInt64(0), builder.getInt64(0)});
    Function* printf_function=module->getFunction("printf");
    printf_args[0] = format;
    ArrayRef <Value*> printf_ref(printf_args);
    auto printf_res = builder.CreateCall(printf_function, printf_ref);
    CodeGenResult* ret = new CodeGenResult(nullptr, nullptr, printf_res);
    return ret;
}

