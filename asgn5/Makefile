all:
	clang -Wall -Wpedantic -Wextra -Werror -g -c  factor.c bv.c sieve.c
	clang -Wall -Wpedantic -Wextra -Werror -g -lm -o  factor factor.c bv.c sieve.c
clean:
	rm -rf factor
	rm -rf factor.o
	rm -rf bv.o
	rm -rf sieve.o
	rm -rf infer-out
bv:
	clang -Wall -Wpedantic -Wextra -Werror -c bv.c
	clang -Wall -Wpedantic -Wextra -Werror -o bv.c
	
infer:
	infer-capture -- make; infer-analyze -- make

