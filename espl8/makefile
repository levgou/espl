     # flags
C_COMPILE_FLAGS = -g -Wall -m32 -ansi -c
LINK_FLAGS = -m32 -g -Wall

all: clear_screen mkbin clean task1 task2

mkbin:
	mkdir -p bin

clear_screen:
	clear

# ----------------------------------------------------------------------------------------------------------------------
# --- Link ---
# ----------------------------------------------------------------------------------------------------------------------
task1: task1.o examine.o
	gcc  $(LINK_FLAGS) -o bin/task1 bin/task1.o bin/examine.o

task2: task2.o examine.o
	gcc  $(LINK_FLAGS) -o bin/task2 bin/task2.o bin/examine.o


# ----------------------------------------------------------------------------------------------------------------------
# --- Compile - Tasks ---
# ----------------------------------------------------------------------------------------------------------------------
task1.o: task1.c
	gcc  $(C_COMPILE_FLAGS) -o bin/task1.o task1.c

task2.o: task2.c
	gcc  $(C_COMPILE_FLAGS) -o bin/task2.o task2.c

# ----------------------------------------------------------------------------------------------------------------------
# --- Compile - Helpers ---
# ----------------------------------------------------------------------------------------------------------------------
examine.o: task0/examine.c
	gcc  $(C_COMPILE_FLAGS) -o bin/examine.o task0/examine.c


#tell make that "clean" is not a file name!
.PHONY: clean

#Clean the build directory
clean:
	rm -f bin/*
