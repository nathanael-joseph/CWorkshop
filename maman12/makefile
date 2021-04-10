#-------------------------------------------------------------------------------
# Author: Nathanael J Y
# Last Modified: 10/04/2021
# Written for: The Open University Of Israel
# Course: 20465 - C Programming Workshop
# Assignment: Maman 12 Question 1
#-------------------------------------------------------------------------------


objects = myText.o linkedList.o buffer.o dynamicBuffer.o
debugFlags = -g -ansi -Wall -pedantic


myText: $(objects)
	gcc $(debugFlags) $(objects) -o myText

myText.o: myText.c myText.h 
	gcc -c $(debugFlags) myText.c 

linkedList.o: linkedList.c linkedList.h
	gcc -c $(debugFlags) linkedList.c 

dynamicBuffer.o: dynamicBuffer.c dynamicBuffer.h
	gcc -c $(debugFlags) dynamicBuffer.c

buffer.o: buffer.c buffer.h
	gcc -c $(debugFlags) buffer.c 

clean:
	rm -f $(objects)

run: myText
	./myText

test: myText
	./myText < test1_dynamic_buffer.txt > results1.txt
	./myText < test2_linked_list.txt > results2.txt

