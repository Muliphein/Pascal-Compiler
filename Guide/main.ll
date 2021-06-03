; ModuleID = 'test'
source_filename = "test"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

%MyNewStruct = type { [2 x %MyStruct] }
%MyStruct = type { i32, i32, [2 x double] }

@fuck.1 = global i32 5
@fuck_string = global [16 x i8] c"%d hello world\0A\00"
@0 = private unnamed_addr constant [7 x i8] c"hello!\00", align 1

declare i32 @fuck(%MyNewStruct*)

declare i32 @printf(i8*, ...)

define i32 @max(i32* %a, i32 %b) {
max_entry:
  store i32 0, i32* %a
  ret i32 0
}

define i32 @main() {
main_entry:
  %0 = call i32 @max(i32* @fuck.1, i32 20)
  %1 = load i32, i32* @fuck.1
  %2 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([7 x i8], [7 x i8]* @0, i32 0, i32 0))
  ret i32 0
}
