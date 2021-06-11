; ModuleID = 'hello'
source_filename = "hello"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@ans = global [11 x i16] zeroinitializer
@i = global i16 0
@0 = private unnamed_addr constant [5 x i8] c"%hd\0A\00", align 1

declare i32 @printf(i8*, ...)

declare i32 @scanf(i8*, ...)

define i16 @main() {
  %main = alloca i16
  store i16 1, i16* getelementptr inbounds ([11 x i16], [11 x i16]* @ans, i64 0, i16 0)
  store i16 1, i16* getelementptr inbounds ([11 x i16], [11 x i16]* @ans, i64 0, i16 1)
  store i16 2, i16* @i
  br label %rep_ent

rep_ent:                                          ; preds = %0
  br label %rep_body

rep_body:                                         ; preds = %rep_body, %rep_ent
  %1 = load i16, i16* @i
  %2 = sub i16 %1, 1
  %3 = sub i16 %2, 1
  %4 = getelementptr [11 x i16], [11 x i16]* @ans, i64 0, i16 %3
  %5 = load i16, i16* @i
  %6 = sub i16 %5, 2
  %7 = sub i16 %6, 1
  %8 = getelementptr [11 x i16], [11 x i16]* @ans, i64 0, i16 %7
  %9 = load i16, i16* %4
  %10 = load i16, i16* %8
  %11 = add i16 %9, %10
  %12 = load i16, i16* @i
  %13 = sub i16 %12, 1
  %14 = getelementptr [11 x i16], [11 x i16]* @ans, i64 0, i16 %13
  store i16 %11, i16* %14
  %15 = load i16, i16* @i
  %16 = add i16 %15, 1
  store i16 %16, i16* @i
  %17 = load i16, i16* @i
  %18 = icmp sgt i16 %17, 11
  br i1 %18, label %rep_body_end, label %rep_body

rep_body_end:                                     ; preds = %rep_body
  br label %rep_over

rep_over:                                         ; preds = %rep_body_end
  %19 = load i16, i16* getelementptr inbounds ([11 x i16], [11 x i16]* @ans, i64 0, i16 10)
  %20 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @0, i64 0, i64 0), i16 %19)
  ret i16 0
}
