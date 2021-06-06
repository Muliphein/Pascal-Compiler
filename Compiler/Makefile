default:
	@echo "Please Input the Parameters"
.PHONY : test
test: GeneratorTest.cpp BasicVariable.cpp Generator.cpp BasicConstant.cpp Function.cpp Statement.cpp SystemCall.cpp RecordType.cpp
	clang++ GeneratorTest.cpp BasicVariable.cpp Generator.cpp BasicConstant.cpp Function.cpp Statement.cpp SystemCall.cpp RecordType.cpp `llvm-config --cflags --ldflags --libs` -o ./test_generator
	./test_generator > test.ll
	clang++ test.ll -o test
	llvm-as test.ll
	llc test.bc
	./test

.PHONY : debug
debug: GeneratorTest.cpp BasicVariable.cpp Generator.cpp BasicConstant.cpp Function.cpp Statement.cpp SystemCall.cpp RecordType.cpp
	clang++ GeneratorTest.cpp BasicVariable.cpp Generator.cpp BasicConstant.cpp Function.cpp Statement.cpp SystemCall.cpp RecordType.cpp `llvm-config --cflags --ldflags --libs` -o ./test_generator
	./test_generator

.PHONY: testclean
testclean:
	-rm test
	-rm test_generator
	-rm test.bc
	-rm test.s
	-rm test.ll

.PHONY: syntax
syntax:
	bison -d test.y
	flex test.lex
	clang++ test.tab.c lex.yy.c splast.cpp GraphGenerator.cpp -o main -std=c++11
	-rm test.tab.c
	-rm lex.yy.c
	-rm test.tab.h

.PHONY: windows
windows:
	clang test.ll -o test.exe --target=x86_64-w64-windows-gnu