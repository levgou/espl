# flags
C_COMPILE_FLAGS = -g -Wall -m32 -ansi -c
LINK_FLAGS = -m32 -g -Wall

all: clean my_shell2

my_shell2: LineParser.o cmd_history.o task2.o
	gcc  $(LINK_FLAGS) -o bin/my_shell bin/LineParser.o bin/task2.o bin/cmd_history.o

my_shell1: LineParser.o prompt.o
	gcc  $(LINK_FLAGS) -o bin/my_shell bin/LineParser.o bin/prompt.o

LineParser.o : LineParser.c
	gcc  $(C_COMPILE_FLAGS) -o bin/LineParser.o LineParser.c

cmd_history.o: cmd_history.c
	gcc  $(C_COMPILE_FLAGS) -o bin/cmd_history.o cmd_history.c

prompt.o : prompt.c
	gcc  $(C_COMPILE_FLAGS) -o bin/prompt.o prompt.c

task2.o : task2.c
	gcc  $(C_COMPILE_FLAGS) -o bin/task2.o task2.c

#tell make that "clean" is not a file name!
.PHONY: clean

#Clean the build directory
clean:
	rm -f bin/*
