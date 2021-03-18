#-------------------------------------------------------------------------------
# Author: Nathanael J Y
# Last Modified: 18/03/2021
# Written for: The Open University Of Israel
# Course: 20465 - C Programming Workshop
# Assignment: Maman 11 Question 2
#-------------------------------------------------------------------------------

my_sin: my_sin.c my_sin.h
	gcc -g -ansi -Wall -pedantic my_sin.c -o my_sin -lm 

run: my_sin
	./my_sin

test: my_sin
	@echo "running tests..."
	@echo "0" | ./my_sin > results.txt
	@echo "25" | ./my_sin >> results.txt
	@echo "-25" | ./my_sin >> results.txt
	@echo "360" | ./my_sin >> results.txt
	@echo "-360" | ./my_sin >> results.txt
	@echo "12" | ./my_sin >> results.txt
	@echo "49.75" | ./my_sin >> results.txt
	@echo "-566.89997" | ./my_sin >> results.txt
	@echo "992576" | ./my_sin >> results.txt
	@echo "90" | ./my_sin >> results.txt
	@echo "Done. \nType 'cat results.txt' to see the output"
