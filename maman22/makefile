#-------------------------------------------------------------------------------
# Author: Nathanael J Y
# Last Modified: 20/04/2021
# Written for: The Open University Of Israel
# Course: 20465 - C Programming Workshop
# Assignment: Maman 22 Question 1
#-------------------------------------------------------------------------------

objects = memorymanagement.o \
		  errormanagement.o \
		  set.o \
		  bitmap_128.o \
		  stringutils.o \
		  charutils.o \
		  myset.o \



debugFlags = -g -ansi -Wall -pedantic

All: $(objects)
	gcc $(debugFlags) $(objects) -o myset
	rm $(objects)

myset.o: myset.c myset.h
	gcc $(debugFlags) -c myset.c

charutils.o: charutils.c charutils.h
	gcc $(debugFlags) -c charutils.c
	
stringutils.o: stringutils.c stringutils.h
	gcc $(debugFlags) -c stringutils.c

set.o: set.c set.h
	gcc $(debugFlags) -c set.c

bitmap_128.o: bitmap_128.c bitmap_128.h
	gcc $(debugFlags) -c bitmap_128.c

memorymanagement.o: memorymanagement.c memorymanagement.h
	gcc $(debugFlags) -c memorymanagement.c

errormanagement.o: errormanagement.c errormanagement.h
	gcc $(debugFlags) -c errormanagement.c

clean:
	rm $(objects)

run: All
	./myset
