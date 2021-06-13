default:
	@echo "Please Input the Parameters"

.PHONY: all
all :
	bison -d SPL.y
	flex SPL.lex
	clang++ SPL.tab.c lex.yy.c splast.cpp GraphGenerator.cpp ASTTransfer.cpp BasicVariable.cpp Generator.cpp BasicConstant.cpp Function.cpp Statement.cpp SystemCall.cpp RecordType.cpp `llvm-config --cflags --ldflags --libs` -o ./main
	-rm SPL.tab.c
	-rm lex.yy.c
	-rm SPL.tab.h

.PHONY: sample
sample:
	@./main test.spl
	@clang++ hello.ll -o hello
	@./hello