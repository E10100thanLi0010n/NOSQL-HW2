CC	=	gcc
CFLAGS	=	-Wall	-g


TARGET	=	my_program
SRC	=	main.c	table.c	benchmark.c
HEADERS	=	table.h	benchmark.h

all:	$(TARGET)

$(TARGET):	$(SRC)	$(HEADERS)
	$(CC)	$(CFLAGS)	-o	$(TARGET)	$(SRC)	-lhiredis

clean:
	rm	-f	$(TARGET)

.PHONY:	all	clean




