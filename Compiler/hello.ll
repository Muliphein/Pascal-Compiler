; ModuleID = 'hello'
source_filename = "hello"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@ans = global [9 x i16] zeroinitializer
@i = global i16 0
@0 = private unnamed_addr constant [5 x i8] c"%hd\0A\00", align 1

declare i32 @printf(i8*, ...)

declare i32 @scanf(i8*, ...)

define i16 @main() {
  %main = alloca i16
  store i16 1, i16* getelementptr inbounds ([9 x i16], [9 x i16]* @ans, i64 0, i16 0)
  store i16 1, i16* getelementptr inbounds ([9 x i16], [9 x i16]* @ans, i64 0, i16 1)
  %i = alloca i16
  %1 = getelementptr i16, i16* %i, i64 0
  store i16 2, i16* %1
  br label %con_block

con_block:                                        ; preds = %loop_block, %0
  %2 = getelementptr i16, i16* %i, i64 0
  %3 = load i16, i16* %2
  %4 = icmp ne i16 %3, 9
  br i1 %4, label %loop_block, label %end_block

loop_block:                                       ; preds = %con_block
  %5 = getelementptr i16, i16* %i, i64 0
  %6 = load i16, i16* %5
  %7 = sub i16 %6, 1
  %8 = sub i16 %7, 0
  %9 = getelementptr [9 x i16], [9 x i16]* @ans, i64 0, i16 %8
  %10 = getelementptr i16, i16* %i, i64 0
  %11 = load i16, i16* %10
  %12 = sub i16 %11, 2
  %13 = sub i16 %12, 0
  %14 = getelementptr [9 x i16], [9 x i16]* @ans, i64 0, i16 %13
  %15 = load i16, i16* %9
  %16 = load i16, i16* %14
  %17 = add i16 %15, %16
  %18 = getelementptr i16, i16* %i, i64 0
  %19 = load i16, i16* %18
  %20 = sub i16 %19, 0
  %21 = getelementptr [9 x i16], [9 x i16]* @ans, i64 0, i16 %20
  store i16 %17, i16* %21
  %22 = getelementptr i16, i16* %i, i64 0
  %23 = load i16, i16* %22
  %24 = add i16 %23, 1
  %25 = getelementptr i16, i16* %i, i64 0
  store i16 %24, i16* %25
  br label %con_block

end_block:                                        ; preds = %con_block
  %26 = load i16, i16* getelementptr inbounds ([9 x i16], [9 x i16]* @ans, i64 0, i16 8)
  %27 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @0, i64 0, i64 0), i16 %26)
  ret i16 0
}
