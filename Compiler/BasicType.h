#ifndef __BASICTYPE_H__
#define __BASICTYPE_H__

#include "BasicLLVM.h"
using namespace llvm;

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

#endif