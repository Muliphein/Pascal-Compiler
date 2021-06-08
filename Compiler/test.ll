; ModuleID = 'test'
source_filename = "test"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@0 = private unnamed_addr constant [13 x i8] c"%hd%hd%*[^\0A]\00", align 1
@1 = private unnamed_addr constant [5 x i8] c"%hd\0A\00", align 1

declare i32 @printf(i8*, ...)

declare i32 @scanf(i8*, ...)

define i16 @main() {
  %main = alloca i16
  %a = alloca [3 x i16]
  %1 = getelementptr [3 x i16], [3 x i16]* %a, i64 0, i16 0
  %2 = getelementptr [3 x i16], [3 x i16]* %a, i64 0, i16 1
  %3 = call i32 (i8*, ...) @scanf(i8* getelementptr inbounds ([13 x i8], [13 x i8]* @0, i64 0, i64 0), i16* %1, i16* %2)
  %4 = getelementptr [3 x i16], [3 x i16]* %a, i64 0, i16 0
  %5 = getelementptr [3 x i16], [3 x i16]* %a, i64 0, i16 1
  %6 = load i16, i16* %4
  %7 = load i16, i16* %5
  %8 = add i16 %6, %7
  %9 = getelementptr [3 x i16], [3 x i16]* %a, i64 0, i16 2
  store i16 %8, i16* %9
  %10 = getelementptr [3 x i16], [3 x i16]* %a, i64 0, i16 2
  %11 = load i16, i16* %10
  %12 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @1, i64 0, i64 0), i16 %11)
  ret i16 0
}
