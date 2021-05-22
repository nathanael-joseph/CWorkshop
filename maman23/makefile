all:
	gcc -g -ansi -Wall -pedantic not_a_quine.c -o not_a_quine
	gcc -g -ansi -Wall -pedantic quine.c -o quine

test: all
	@echo "\n\nrunning test 1"
	./not_a_quine > test1.c
	gcc -g -ansi -Wall -pedantic test1.c -o test1
	./test1
	@echo "\n\nrunning test 2"
	./quine > test2.c
	gcc -g -ansi -Wall -pedantic test2.c -o test2
	./test2

clean:
	rm test*