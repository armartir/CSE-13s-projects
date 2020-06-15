

all:
	clang -Wall -Wpedantic -Wextra -Werror lrc.c -o lrc
clean:
	rm -rf lrc
	rm -rf infer-out
infer:
	 infer-capture -- make; infer-analyze -- make
