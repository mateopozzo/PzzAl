S=src
O=obj
I=include
T=test
SRCS=$(wildcard $(S)/*.c)
OBJS=$(patsubst $(S)/%.c, $(O)/%.o, $(SRCS))

CC = gcc
CFLAGS = -g -Wall -Werror

testexe: $(T)/test.o $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $< -o $@ 

$(T)/test.o: $(T)/test.c	
	$(CC) -c $(CFLAGS) $< -o $@
	
$(O)/%.o: $(S)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -r $(OBJS)

