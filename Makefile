CC = cc
CFLAFS = -std=c11 -g -static

11c: 11c.c

test: 11c
	./test.sh

clean:
	rm -f 11c *.o *~ tmp*

.PHONY: test clean
