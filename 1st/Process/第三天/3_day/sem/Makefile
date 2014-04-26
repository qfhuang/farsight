CC = gcc
CFLAGS = -Wall -g

SRC = $(wildcard *.c)
OBJS = $(SRC:.c=.o)
TARGET = sem_fork

all : $(TARGET)

%.o : %.c
	$(CC) $(CFLAGS) -c  $^ -o $@
$(TARGET) : $(OBJS)
	$(CC) $(CFLAGS)  $^ -o $@

clean : 
	rm -rf *.o $(TARGET) *.tgz *.swp

