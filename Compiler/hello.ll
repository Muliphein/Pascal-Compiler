; ModuleID = 'hello'
source_filename = "hello"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@ans = global i16 0
@0 = private unnamed_addr constant [5 x i8] c"%hd\0A\00", align 1

declare i32 @printf(i8*, ...)

declare i32 @scanf(i8*, ...)

define i16 @gcd(i16 %a, i16 %b) {
  %a1 = alloca i16
  %1 = getelementptr i16, i16* %a1, i64 0
  store i16 %a, i16* %1
  %b2 = alloca i16
  %2 = getelementptr i16, i16* %b2, i64 0
  store i16 %b, i16* %2
  %gcd = alloca i16
  %3 = getelementptr i16, i16* %b2, i64 0
  %4 = load i16, i16* %3
  %5 = icmp eq i16 %4, 0
  br i1 %5, label %then_block, label %else_block

then_block:                                       ; preds = %0
  %6 = getelementptr i16, i16* %a1, i64 0
  %7 = getelementptr i16, i16* %gcd, i64 0
  %8 = load i16, i16* %6
  store i16 %8, i16* %7
  br label %end_block

else_block:                                       ; preds = %0
  %9 = getelementptr i16, i16* %b2, i64 0
  %10 = load i16, i16* %9
  %11 = getelementptr i16, i16* %a1, i64 0
  %12 = getelementptr i16, i16* %b2, i64 0
  %13 = load i16, i16* %11
  %14 = load i16, i16* %12
  %15 = srem i16 %13, %14
  %16 = call i16 @gcd(i16 %10, i16 %15)
  %17 = getelementptr i16, i16* %gcd, i64 0
  store i16 %16, i16* %17
  br label %end_block

end_block:                                        ; preds = %else_block, %then_block
  %18 = getelementptr i16, i16* %gcd, i64 0
  %19 = load i16, i16* %18
  ret i16 %19
}

define i16 @main() {
  %main = alloca i16
  %1 = call i16 @gcd(i16 9, i16 36)
  %2 = call i16 @gcd(i16 3, i16 6)
  %3 = mul i16 %1, %2
  store i16 %3, i16* @ans
  %4 = load i16, i16* @ans
  %5 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @0, i64 0, i64 0), i16 %4)
  ret i16 0
}
