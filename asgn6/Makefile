all:
	clang -Wall -Wpedantic -Wextra -Werror -g -c  sorting.c sortA.c sortB.c sortC.c sortD.c
	clang -Wall -Wpedantic -Wextra -Werror -g -o  sorting sorting.c sortA.c sortB.c sortC.c sortD.c
clean:
	rm -rf sorting
	rm -rf sorting.o
	rm -rf infer-out
	rm -rf sortA.o
	rm -rf sortB.o
	rm -rf sortC.o
	rm -rf sortD.o
sort:
	clang -Wall -Wpedantic -Wextra -Werror -c sortD.c
	clang -Wall -Wpedantic -Wextra -Werror -o sortD.c

infer:
	infer-capture -- make; infer-analyze -- make

