#   Compiler, Compiler Flags
CC = gcc
CFLAGS = -Wall -std=c99 -O3

#   Sources
SOURCES = roapfun.c 

#   Objects  ('Make' automatically compiles .c to .o)

OBJECTS_ROAP = roapfun.o roap.o 

roap: $(OBJECTS_ROAP)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS_ROAP)



roap.o: roap.c

roapfun.o: head.h roapfun.c

clean::
	rm -f *.o core a.out *~
