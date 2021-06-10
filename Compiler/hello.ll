; ModuleID = 'hello'
source_filename = "hello"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@f = global i16 0
@k = global i16 0
@0 = private unnamed_addr constant [5 x i8] c"%hd\0A\00", align 1
@1 = private unnamed_addr constant [5 x i8] c"%hd\0A\00", align 1

declare i32 @printf(i8*, ...)

declare i32 @scanf(i8*, ...)

define i16 @go(i16* %b, i16 %a) {
  %a1 = alloca i16
  %1 = getelementptr i16, i16* %a1, i64 0
  store i16 %a, i16* %1
  %go = alloca i16
  %fk = alloca i16
  %t = alloca float
  %2 = getelementptr i16, i16* %a1, i64 0
  %3 = load i16, i16* %2
  %4 = icmp sgt i16 %3, 0
  br i1 %4, label %then_block, label %else_block

then_block:                                       ; preds = %0
  %5 = getelementptr i16, i16* %a1, i64 0
  %6 = getelementptr i16, i16* %b, i64 0
  %7 = getelementptr i16, i16* %a1, i64 0
  %8 = load i16, i16* %7
  %9 = sub i16 %8, 1
  %10 = call i16 @go(i16* %6, i16 %9)
  %11 = load i16, i16* %5
  %12 = mul i16 %11, %10
  %13 = getelementptr i16, i16* %go, i64 0
  store i16 %12, i16* %13
  br label %end_block

else_block:                                       ; preds = %0
  %14 = getelementptr i16, i16* %go, i64 0
  store i16 1, i16* %14
  br label %end_block

end_block:                                        ; preds = %else_block, %then_block
  %15 = getelementptr i16, i16* %b, i64 0
  %16 = getelementptr i16, i16* %go, i64 0
  %17 = load i16, i16* %15
  %18 = load i16, i16* %16
  %19 = add i16 %17, %18
  %20 = getelementptr i16, i16* %b, i64 0
  store i16 %19, i16* %20
  %21 = getelementptr i16, i16* %go, i64 0
  %22 = load i16, i16* @k
  %23 = load i16, i16* %21
  %24 = add i16 %22, %23
  store i16 %24, i16* @k
  %25 = getelementptr i16, i16* %go, i64 0
  %26 = load i16, i16* %25
  ret i16 %26
}

define i16 @main() {
  %main = alloca i16
  store i16 0, i16* @k
  %1 = call i16 @go(i16* @k, i16 5)
  store i16 %1, i16* @f
  %2 = load i16, i16* @f
  %3 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @0, i64 0, i64 0), i16 %2)
  %4 = load i16, i16* @k
  %5 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @1, i64 0, i64 0), i16 %4)
  ret i16 0
}
