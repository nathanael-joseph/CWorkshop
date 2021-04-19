#-------------------------------------------------------------------------------
# Author: Nathanael J Y
# Last Modified: 19/04/2021
# Written for: The Open University Of Israel
# Course: 20465 - C Programming Workshop
# Assignment: Maman 22 Question 1
#-------------------------------------------------------------------------------

objects = set.o myset.o bitmap_128.o
debugFlags = -g -ansi -Wall -pedantic

bitmap_128: bitmap_128.c bitmap_128.h
	gcc $(debugFlags) -c bitmap_128.c

clean:
	rm $(objects)
	