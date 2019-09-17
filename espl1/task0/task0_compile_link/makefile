# flags
C_COMPILE_FLAGS = -g -Wall -m32 -ansi -c
ASM_COMPILE_FLAGS = -g -f elf -w+all
LINK_FLAGS = -m32 -g -Wall

# All Targets
all: task0

# Tool invocations
task0: main.o numbers.o add.o
	gcc  $(LINK_FLAGS) -o bin/task0 bin/main.o bin/numbers.o bin/add.o

main.o: main.c
	gcc $(C_COMPILE_FLAGS) -o bin/main.o main.c

numbers.o: numbers.c
	gcc $(C_COMPILE_FLAGS) -o bin/numbers.o numbers.c

add.o: add.s
	nasm $(ASM_COMPILE_FLAGS) -o bin/add.o add.s


#tell make that "clean" is not a file name!
.PHONY: clean

#Clean the build directory
clean:
	rm -f bin/*