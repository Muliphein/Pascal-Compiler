; ModuleID = 'hello'
source_filename = "hello"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

%fib = type { i16, i16 }

@ans = global [11 x i16] zeroinitializer
@i = global i16 0
@temp = global %fib zeroinitializer
@0 = private unnamed_addr constant [5 x i8] c"%hd\0A\00", align 1

declare i32 @printf(i8*, ...)

declare i32 @scanf(i8*, ...)

define i16 @main() {
  %main = alloca i16
  store i16 11, i16* getelementptr inbounds (%fib, %fib* @temp, i64 0, i32 0)
  store i16 1, i16* getelementptr inbounds (%fib, %fib* @temp, i64 0, i32 1)
  %1 = load i16, i16* getelementptr inbounds (%fib, %fib* @temp, i64 0, i32 1)
  %2 = sub i16 %1, 1
  %3 = getelementptr [11 x i16], [11 x i16]* @ans, i64 0, i16 %2
  store i16 1, i16* %3
  %4 = load i16, i16* getelementptr inbounds (%fib, %fib* @temp, i64 0, i32 1)
  %5 = add i16 %4, 1
  store i16 %5, i16* getelementptr inbounds (%fib, %fib* @temp, i64 0, i32 1)
  %6 = load i16, i16* getelementptr inbounds (%fib, %fib* @temp, i64 0, i32 1)
  %7 = sub i16 %6, 1
  %8 = getelementptr [11 x i16], [11 x i16]* @ans, i64 0, i16 %7
  store i16 1, i16* %8
  store i16 2, i16* @i
  br label %rep_ent

rep_ent:                                          ; preds = %0
  br label %rep_body

rep_body:                                         ; preds = %rep_body, %rep_ent
  %9 = load i16, i16* @i
  %10 = sub i16 %9, 1
  %11 = sub i16 %10, 1
  %12 = getelementptr [11 x i16], [11 x i16]* @ans, i64 0, i16 %11
  %13 = load i16, i16* @i
  %14 = sub i16 %13, 2
  %15 = sub i16 %14, 1
  %16 = getelementptr [11 x i16], [11 x i16]* @ans, i64 0, i16 %15
  %17 = load i16, i16* %12
  %18 = load i16, i16* %16
  %19 = add i16 %17, %18
  %20 = load i16, i16* @i
  %21 = sub i16 %20, 1
  %22 = getelementptr [11 x i16], [11 x i16]* @ans, i64 0, i16 %21
  store i16 %19, i16* %22
  %23 = load i16, i16* @i
  %24 = add i16 %23, 1
  store i16 %24, i16* @i
  %25 = load i16, i16* @i
  %26 = load i16, i16* getelementptr inbounds (%fib, %fib* @temp, i64 0, i32 0)
  %27 = icmp sgt i16 %25, %26
  br i1 %27, label %rep_body_end, label %rep_body

rep_body_end:                                     ; preds = %rep_body
  br label %rep_over

rep_over:                                         ; preds = %rep_body_end
  %28 = load i16, i16* getelementptr inbounds ([11 x i16], [11 x i16]* @ans, i64 0, i16 10)
  %29 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @0, i64 0, i64 0), i16 %28)
  ret i16 0
}
