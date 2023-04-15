CC = gcc
CFLAGS = -std=c99 -Wall

clean:
	rm -f *.o main
all: main.o parser.o lexer.o grammar.o hashmap.o linkedlist.o tree.o datablock.o utils.o
	$(CC) $(CFLAGS) -Wall -o main utils.o datablock.o tree.o linkedlist.o hashmap.o grammar.o lexer.o parser.o main.o
main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o
parser.o: parser.c parser.h
	$(CC) $(CFLAGS) -c parser.c -o parser.o
lexer.o: lexer.c lexer.h
	$(CC) $(CFLAGS) -c lexer.c -o lexer.o
grammar.o: grammar.c grammar.h
	$(CC) $(CFLAGS) -c grammar.c -o grammar.o
hashmap.o: hashmap.c hashmap.h
	$(CC) $(CFLAGS) -c hashmap.c -o hashmap.o
linkedlist.o: linkedlist.c linkedlist.h
	$(CC) $(CFLAGS) -c linkedlist.c -o linkedlist.o
tree.o: tree.c tree.h
	$(CC) $(CFLAGS) -c tree.c -o tree.o
datablock.o: datablock.c datablock.h
	$(CC) $(CFLAGS) -c datablock.c -o datablock.o
utils.o: utils.c utils.h
	$(CC) $(CFLAGS) -c utils.c -o utils.o
