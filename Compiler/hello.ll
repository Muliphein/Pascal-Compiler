; ModuleID = 'hello'
source_filename = "hello"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@i = global i16 0
@0 = private unnamed_addr constant [5 x i8] c"%hd\0A\00", align 1

declare i32 @printf(i8*, ...)

declare i32 @scanf(i8*, ...)

define i16 @go(i16 %a) {
  %a1 = alloca i16
  %1 = getelementptr i16, i16* %a1, i64 0
  store i16 %a, i16* %1
  %go = alloca i16
  %2 = getelementptr i16, i16* %a1, i64 0
  %3 = load i16, i16* %2
  %4 = icmp eq i16 %3, 1
  br i1 %4, label %then_block, label %else_block

then_block:                                       ; preds = %0
  %5 = getelementptr i16, i16* %go, i64 0
  store i16 1, i16* %5
  br label %end_block

else_block:                                       ; preds = %0
  %6 = getelementptr i16, i16* %a1, i64 0
  %7 = load i16, i16* %6
  %8 = icmp eq i16 %7, 2
  br i1 %8, label %then_block2, label %else_block3

end_block:                                        ; preds = %end_block4, %then_block
  %9 = getelementptr i16, i16* %go, i64 0
  %10 = load i16, i16* %9
  ret i16 %10

then_block2:                                      ; preds = %else_block
  %11 = getelementptr i16, i16* %go, i64 0
  store i16 1, i16* %11
  br label %end_block4

else_block3:                                      ; preds = %else_block
  %12 = getelementptr i16, i16* %a1, i64 0
  %13 = load i16, i16* %12
  %14 = sub i16 %13, 1
  %15 = call i16 @go(i16 %14)
  %16 = getelementptr i16, i16* %a1, i64 0
  %17 = load i16, i16* %16
  %18 = sub i16 %17, 2
  %19 = call i16 @go(i16 %18)
  %20 = add i16 %15, %19
  %21 = getelementptr i16, i16* %go, i64 0
  store i16 %20, i16* %21
  br label %end_block4

end_block4:                                       ; preds = %else_block3, %then_block2
  br label %end_block
}

define i16 @main() {
  %main = alloca i16
  %1 = call i16 @go(i16 10)
  store i16 %1, i16* @i
  %2 = load i16, i16* @i
  %3 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @0, i64 0, i64 0), i16 %2)
  ret i16 0
}
