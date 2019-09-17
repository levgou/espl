# flags
C_COMPILE_FLAGS = -g -Wall -m32 -ansi -c
ASM_COMPILE_FLAGS = -g -f elf -w+all
LINK_FLAGS = -m32 -g -Wall

# All Targets
all: task0

# Tool invocations
task0: task0.o my_cmp.o
	gcc  $(LINK_FLAGS) -o bin/task0 bin/task0.o  bin/my_cmp.o

task0.o: task0.c
	gcc $(C_COMPILE_FLAGS) -o bin/task0.o task0.c

my_cmp.o: my_cmp.asm
	nasm $(ASM_COMPILE_FLAGS) -o bin/my_cmp.o my_cmp.asm


#tell make that "clean" is not a file name!
.PHONY: clean

#Clean the build directory
clean:
	rm -f bin/*