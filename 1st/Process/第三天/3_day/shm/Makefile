CC = gcc
CFLAGS = -Wall -g

SRC = $(wildcard *.c)
TARGET = $(SRC:.c=)

all : $(TARGET)

% : %.o
	$(CC) $(CFLAGS)  $^ -o $@

clean : 
	rm -rf *.o $(TARGET) *.tgz *.swp

