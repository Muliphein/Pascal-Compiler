#ifndef __BASICTYPE_H__
#define __BASICTYPE_H__

#include "BasicLLVM.h"
using namespace llvm;

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
Type* ExtendType;   // 10 byte ...

Type* CharType; // 1 byte *
Type* BoolType; // 1 bit *

#endif