main : main.cpp
	clang++ main.cpp `llvm-config --cflags --ldflags --libs` -o ./main

.PHONY: run
run : main.cpp
	clang++ main.cpp `llvm-config --cflags --ldflags --libs` -o ./main
	./main > main.ll
	clang++ main.ll -o main.out
	./main.out


.PHONY: run3
run3 : main.cpp
	clang++ main.cpp `llvm-config --cflags --ldflags --libs` -o ./main -O3
	./main > main.ll
	clang++ main.ll -o main.out
	./main.out

.PHONY: clean
clean:
	-rm main
	-rm main.out