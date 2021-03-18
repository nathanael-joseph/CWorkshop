#-------------------------------------------------------------------------------
# Author: Nathanael J Y
# Last Modified: 17/03/2021
# Written for: The Open University Of Israel
# Course: 20465 - C Programming Workshop
# Assignment: Maman 11 Question 1
#-------------------------------------------------------------------------------

letters: letters.c letters.h
	@echo "compiling"
	gcc -g -ansi -Wall -pedantic letters.c -o letters
	@echo "compiled successfully"

run: letters
	./letters

test: letters
	@echo "running test..."
	@./letters < test.txt > results.txt
	@echo "Done. \nType 'cat results.txt' to see the output"
