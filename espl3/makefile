# flags
C_COMPILE_FLAGS = -g -Wall -m32 -ansi -c
LINK_FLAGS = -m32 -g -Wall

all: bcmp

bcmp: task1a.o task1b.o task1c.o task2.o
	gcc  $(LINK_FLAGS) -o bin/bcmp bin/task1a.o bin/task1b.o bin/task1c.o bin/task2.o

task1a.o : task1a.c
	gcc  $(C_COMPILE_FLAGS) -o bin/task1a.o task1a.c

task1b.o : task1b.c
	gcc  $(C_COMPILE_FLAGS) -o bin/task1b.o task1b.c

task1c.o : task1c.c
	gcc  $(C_COMPILE_FLAGS) -o bin/task1c.o task1c.c

task2.o : task2.c
	gcc  $(C_COMPILE_FLAGS) -o bin/task2.o task2.c

#tell make that "clean" is not a file name!
.PHONY: clean

#Clean the build directory
clean:
	rm -f bin/*
