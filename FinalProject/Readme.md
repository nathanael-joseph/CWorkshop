
Assignment14 - Final Project
===

***Authored By: Nathanael J Y***

***A C programming assignment for the Open University of Isreal.***

Git Repo: https://github.com/nathanael-joseph/CWorkshop/tree/main/FinalProject

---

Assignment 14 is a single file assembly compiler for a simplified assembly language, detailed in the project brief.

An overview of the brief containing the information necissary for compiling can be found in the file:
	brief_notes.txt

The Instructions are loaded from the CSV file:
	assembler_instructions.csv
This file is crucial to the compiler's functionality - ***DO NOT MOVE, EDIT, OR DELETE***

Compiler directives are currently hard coded - see directive.c for implementation

To compile:
	$ make build 
And then run using:
	$ ./assembler file1.as file2.as ... fileN.as

Two standard tests have already been created:

	$ make test

this rebuilds the project and executes ./assembler test_error.as test_pass.as 				 Readme.md 
	

	$ make test_long

this rebuilds the project and then executes ./assembler test_pass_long.as  test_error_long.as in valgrind. Note that valgrind must be installed in your system for this command to work.


Additional commands 

	$ make clean 

 removes .o files, .ent files, .ext files, .ob files, and the assembler executable.


 	$ make
 	
 simply recompiles and relinks any changed files.


