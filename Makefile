CC = gcc
CFLAGS = -std=c99 -Wall

all: main.o parser.o lexer.o linkedlist.o tree.o utils.o
	$(CC) $(CFLAGS) -Wall -o main utils.o linkedlist.o tree.o lexer.o parser.o main.o
main: main.c main.h
	$(CC) -Wall -c main.c
parser:
	$(CC) parser.c parser.h
lexer: lexer.c lexer.h
	$(CC) -Wall -c lexer.c
linkedlist: linkedlist.c linkedlist.h
	$(CC) -Wall -c linkedlist.c
tree: tree.c tree.h
	$(CC) -Wall -c tree.c
utils: utils.c utils.h
	$(CC) -Wall -c utils.c

