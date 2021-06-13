; ModuleID = 'hello'
source_filename = "hello"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@ans = global [1001 x i16] zeroinitializer
@i = global i16 0
@a = global i16 0
@b = global i16 0
@0 = private unnamed_addr constant [5 x i8] c"%hd\0A\00", align 1

declare i32 @printf(i8*, ...)

declare i32 @scanf(i8*, ...)

define i16 @main() {
  %main = alloca i16
  store i16 1, i16* getelementptr inbounds ([1001 x i16], [1001 x i16]* @ans, i64 0, i16 0)
  store i16 1, i16* getelementptr inbounds ([1001 x i16], [1001 x i16]* @ans, i64 0, i16 1)
  store i16 2, i16* @a
  store i16 8, i16* @b
  %i = alloca i16
  %1 = getelementptr i16, i16* %i, i64 0
  %2 = load i16, i16* @a
  store i16 %2, i16* %1
  br label %con_block

con_block:                                        ; preds = %loop_block, %0
  %3 = getelementptr i16, i16* %i, i64 0
  %4 = load i16, i16* @b
  %5 = add i16 %4, 1
  %6 = load i16, i16* %3
  %7 = icmp ne i16 %6, %5
  br i1 %7, label %loop_block, label %end_block

loop_block:                                       ; preds = %con_block
  %8 = getelementptr i16, i16* %i, i64 0
  %9 = load i16, i16* %8
  %10 = sub i16 %9, 1
  %11 = sub i16 %10, 0
  %12 = getelementptr [1001 x i16], [1001 x i16]* @ans, i64 0, i16 %11
  %13 = getelementptr i16, i16* %i, i64 0
  %14 = load i16, i16* %13
  %15 = sub i16 %14, 2
  %16 = sub i16 %15, 0
  %17 = getelementptr [1001 x i16], [1001 x i16]* @ans, i64 0, i16 %16
  %18 = load i16, i16* %12
  %19 = load i16, i16* %17
  %20 = add i16 %18, %19
  %21 = getelementptr i16, i16* %i, i64 0
  %22 = load i16, i16* %21
  %23 = sub i16 %22, 0
  %24 = getelementptr [1001 x i16], [1001 x i16]* @ans, i64 0, i16 %23
  store i16 %20, i16* %24
  %25 = load i16, i16* @b
  %26 = add i16 %25, 1
  store i16 %26, i16* @b
  %27 = getelementptr i16, i16* %i, i64 0
  %28 = load i16, i16* %27
  %29 = add i16 %28, 1
  %30 = getelementptr i16, i16* %i, i64 0
  store i16 %29, i16* %30
  br label %con_block

end_block:                                        ; preds = %con_block
  %31 = load i16, i16* @b
  %32 = sub i16 %31, 0
  %33 = getelementptr [1001 x i16], [1001 x i16]* @ans, i64 0, i16 %32
  %34 = load i16, i16* %33
  %35 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @0, i64 0, i64 0), i16 %34)
  ret i16 0
}
