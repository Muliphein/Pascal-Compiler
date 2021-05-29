; ModuleID = 'test'
source_filename = "test"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

%MyStruct = type { i32, i32, double }

@fuck.1 = global i32 0
@fuck_string = global [16 x i8] c"%d hello world\0A\00"
@0 = private unnamed_addr constant [7 x i8] c"hello!\00", align 1

declare i32 @fuck(%MyStruct*)

declare i32 @printf(i8*, ...)

define i32 @max(i32 %a, i32 %b) {
max_entry:
  %0 = icmp sgt i32 %a, %b
  %t = alloca i32
  %1 = getelementptr i32, i32* %t, i32 0
  store i32 5, i32* %1
  %2 = load i32, i32* %1
  %3 = lshr i32 %2, 2
  store i32 %3, i32* %1
  br i1 %0, label %if_then, label %if_else

if_then:                                          ; preds = %max_entry
  ret i32 %a

if_else:                                          ; preds = %max_entry
  %4 = load i32, i32* %t
  ret i32 %2
}

define i32 @main() {
main_entry:
  %0 = call i32 @max(i32 -10, i32 20)
  %1 = load i32, i32* @fuck.1
  %2 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([16 x i8], [16 x i8]* @fuck_string, i32 0, i32 0), i32 %1)
  ret i32 0
}
