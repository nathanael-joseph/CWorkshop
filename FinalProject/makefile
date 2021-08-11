
debugFlags = -g -ansi -Wall -pedantic 

includePaths = 	-I ./ 

obj = system_utils/memory_management.o \
	  system_utils/error_logging.o \
  	  system_utils/file_management.o \
	  datastructures/singlelinkedlist.o \
	  datastructures/dictionary.o \
	  datastructures/linkedlist_buffer.o \
	  type_utils/char_utils.o \
	  type_utils/string_utils.o \
	  assembler.o \
	  instruction.o \
	  label.o \
	  directive.o \
	  assembler_state.o

assembler: $(obj) 
	gcc $(debugFlags) $(obj) -o assembler
	@echo "\n"

%.o: %.c %.h
	gcc -c $(debugFlags) $(includePaths) $< -o $@
	@echo "\n"

test: build
	./assembler test_error.as test_pass.as Readme.md 

test_long: build
	valgrind -v --leak-check=full --show-leak-kinds=all \
	./assembler test_pass_long.as  test_error_long.as

.PHONY:

build: .PHONY
	$(MAKE) clean
	$(MAKE) assembler

clean: .PHONY
	find . -name '*.o' -type f -delete
	rm -f assembler
	rm -f *.ent *.ext *.ob
