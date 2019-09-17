# flags
C_COMPILE_FLAGS = -g -Wall -m32 -ansi -c
ASM_COMPILE_FLAGS = -g -f elf -w+all
LINK_FLAGS = -m32 -g -Wall

# All Targets
all: char2ascii

# Tool invocations
char2ascii: main.o task1a.o task1b.o task1b.o task1c.o utills.o
	gcc  $(LINK_FLAGS) -o bin/char2ascii bin/main.o bin/task1a.o bin/task1b.o bin/task1c.o bin/utills.o 

main.o: main.c
	gcc $(C_COMPILE_FLAGS) -o bin/main.o main.c

task1a.o: utills.o task1a.c
	gcc $(C_COMPILE_FLAGS) -o bin/task1a.o task1a.c

task1b.o: utills.o task1b.c
	gcc $(C_COMPILE_FLAGS) -o bin/task1b.o task1b.c

task1c.o: utills.o task1c.c
	gcc $(C_COMPILE_FLAGS) -o bin/task1c.o task1c.c

utills.o: utills.c
	gcc $(C_COMPILE_FLAGS) -o bin/utills.o utills.c


#tell make that "clean" is not a file name!
.PHONY: clean

#Clean the build directory
clean:
	rm -f bin/*