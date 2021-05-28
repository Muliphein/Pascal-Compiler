; ModuleID = 'test'
source_filename = "test"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

%MyStruct = type { i32, i32, double }

@fuck.1 = global i32 0
@fuck_string = global [13 x i8] c"hello world\0A\00"

declare i32 @fuck(%MyStruct*)

declare i32 @printf(i8*, ...)

define i32 @max(i32 %a, i32 %b) {
max_entry:
  %0 = icmp sgt i32 %a, %b
  %t = alloca i32
  store i32 5, i32* %t
  %1 = load i32, i32* %t
  %2 = lshr i32 %1, 2
  store i32 %2, i32* %t
  br i1 %0, label %if_then, label %if_else

if_then:                                          ; preds = %max_entry
  ret i32 %a

if_else:                                          ; preds = %max_entry
  %3 = load i32, i32* %t
  ret i32 %1
}

define i32 @main() {
main_entry:
  %0 = call i32 @max(i32 -10, i32 20)
  store i8 48, i8* getelementptr inbounds ([13 x i8], [13 x i8]* @fuck_string, i32 0, i32 1)
  %1 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([13 x i8], [13 x i8]* @fuck_string, i32 0, i32 0))
  ret i32 0
}
