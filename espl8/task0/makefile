     # flags
C_COMPILE_FLAGS = -g -Wall -m32 -ansi -c
LINK_FLAGS = -m32 -g -Wall

all: clear_screen mkbin clean task0

mkbin:
	mkdir -p bin

clear_screen:
	clear

# ----------------------------------------------------------------------------------------------------------------------
# --- Link ---
# ----------------------------------------------------------------------------------------------------------------------
task0: examine.o
	gcc  $(LINK_FLAGS) -o bin/tasko bin/examine.o


# ----------------------------------------------------------------------------------------------------------------------
# --- Compile - Tasks ---
# ----------------------------------------------------------------------------------------------------------------------
examine.o: examine.c
	gcc  $(C_COMPILE_FLAGS) -o bin/examine.o examine.c

# ----------------------------------------------------------------------------------------------------------------------
# --- Compile - Helpers ---
# ----------------------------------------------------------------------------------------------------------------------

#tell make that "clean" is not a file name!
.PHONY: clean

#Clean the build directory
clean:
	rm -f bin/*
