CC	=	gcc
CFLAGS	=	-Wall	-g


TARGET	=	my_program
SRC	=	main.c	table.c	DoubleLinkedList.c	benchmark.c	SortedSet.c
HEADERS	=	table.h	DoubleLinkedList.h	benchmark.h	SortedSet.h

all:	$(TARGET)

$(TARGET):	$(SRC)	$(HEADERS)
	$(CC)	$(CFLAGS)	-o	$(TARGET)	$(SRC)	-lhiredis

clean:
	rm	-f	$(TARGET)

.PHONY:	all	clean




