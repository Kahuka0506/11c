CC = cc
CFLAFS = -std=c11 -g -static
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

11c: $(OBJS)
	$(CC) -o 11c $(OBJS) $(LDFLAGS)

$(OBJS): 11c.h

test: 11c
	./test.sh

clean:
	rm -f 11c *.o *~ tmp*

.PHONY: test clean
