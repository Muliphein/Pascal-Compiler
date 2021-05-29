default:
	echo "Please Add the Parameters"
.PHONY : test
test: GeneratorTest.cpp BasicVariable.cpp Generator.cpp BasicConstant.cpp Function.cpp Statement.cpp SystemCall.cpp
	clang++ GeneratorTest.cpp BasicVariable.cpp Generator.cpp BasicConstant.cpp Function.cpp Statement.cpp SystemCall.cpp `llvm-config --cflags --ldflags --libs` -o ./test