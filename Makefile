CC = gcc
CFLAGS = --std=c99


bst : bst.c
	$(CC) $(CFLAGS) bst.c -o bst
