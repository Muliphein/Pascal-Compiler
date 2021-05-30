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
