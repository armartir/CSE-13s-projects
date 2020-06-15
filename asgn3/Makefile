
all:
	clang -Wall -Wpedantic -Wextra -Werror -O3 -c math.c
	clang -Wall -O3 -lm -o math math.o

clean:
	rm -rf math
	rm -rf math.o
	rm -rf infer-out
infer :
	infer-capture -- make; infer-analyze -- make 
