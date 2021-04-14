#-------------------------------------------------------------------------------
# Author: Nathanael J Y
# Last Modified: 13/04/2021
# Written for: The Open University Of Israel
# Course: 20465 - C Programming Workshop
# Assignment: Maman 12 Question 1
#-------------------------------------------------------------------------------


objects = myText.o linkedList.o buffer.o dynamicBuffer.o dsFactory.o
debugFlags = -g -ansi -Wall -pedantic


myText: $(objects)
	gcc $(debugFlags) $(objects) -o myText
	rm -f $(objects)

myText.o: myText.c myText.h dsFactory.o
	gcc -c $(debugFlags) myText.c 

dsFactory.o: dsFactory.c dsFactory.h linkedList.o dynamicBuffer.o
	gcc -c $(debugFlags) dsFactory.c 

linkedList.o: linkedList.c linkedList.h buffer.o
	gcc -c $(debugFlags) linkedList.c 

dynamicBuffer.o: dynamicBuffer.c dynamicBuffer.h buffer.o
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
	./myText < test3_dynamic_buffer_big_file.txt > results3.txt
	./myText < test4_linked_list_big_file.txt > results4.txt