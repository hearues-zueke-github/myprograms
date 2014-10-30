BINARY=crypt

CC = gcc
CFLAGS = -Wall -o

all: encraption.c utils.c main.c
	$(CC) $(CFLAGS) $(BINARY) $^  
test:
	./$(BINARY) $(BINARY) $(BINARY) e $(BINARY).crypt
