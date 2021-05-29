; ModuleID = 'test'
source_filename = "test"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@a = global i16 0
@b = global i16 0
@c = global i16 0
@0 = private unnamed_addr constant [7 x i8] c"%hd%hd\00", align 1
@1 = private unnamed_addr constant [5 x i8] c"%hd\0A\00", align 1

declare i32 @printf(i8*, ...)

declare i32 @scanf(i8*, ...)

define i64 @main() {
  %1 = load i16, i16* @a
  %2 = load i16, i16* @b
  %3 = call i32 (i8*, ...) @scanf(i8* getelementptr inbounds ([7 x i8], [7 x i8]* @0, i64 0, i64 0), i16* @a, i16* @b)
  %4 = load i16, i16* @a
  %5 = load i16, i16* @b
  %6 = add i16 %4, %5
  %7 = load i16, i16* @c
  store i16 %6, i16* @c
  %8 = load i16, i16* @c
  %9 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @1, i64 0, i64 0), i16 %8)
  ret i64 0
}
