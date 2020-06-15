all:
	clang -Wall -Wpedantic -Wextra -Werror -c  tower.c stack.c
	clang -Wall -Wpedantic -Wextra -Werror -o  tower tower.c stack.c

clean: 
	rm -rf stack.o
	rm -rf tower
	rm -rf tower.o
	rm -rf infer-out
infer:
	infer-capture -- make; infer-analyze -- make
