CC := gcc
CFLAGS := -Wall -g -O0
SRC := ${wildcard *.c}
OBJS := ${patsubst %.c,%,$(SRC)}

.PHONY:all clean
all:$(OBJS)

%:%.c
	$(CC) $(CFLAGS) -o $@ $^



clean:
	$(RM) *.o .*.sw? $(OBJS) 
#	echo $(SRC)
#	echo $(OBJS)
