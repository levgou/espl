# flags
C_COMPILE_FLAGS = -g -Wall -m32 -ansi -c
ASM_COMPILE_FLAGS = -g -f elf -w+all
LINK_FLAGS = -m32 -g -Wall

all: task1 task2 task3

# ---------------------------------- link targets ----------------------------------
task1: task1.o task1.o funcA.o
	gcc  $(LINK_FLAGS) -o bin/task1 bin/task1.o  bin/funcA.o

task2: scmp.o cmpstr.o cmpstr_asm.o
	gcc  $(LINK_FLAGS) -o bin/task2 bin/scmp.o bin/cmpstr_asm.o

task3: rev_str.o
	ld -melf_i386 -o bin/task3 bin/rev_str.o -lc -I/lib/ld-linux.so.2

# -------------------------------- compile targets ---------------------------------

# task 1
task1.o: task1.c
	gcc $(C_COMPILE_FLAGS) -o bin/task1.o task1.c

funcA.o: funcA.asm
	nasm $(ASM_COMPILE_FLAGS) -o bin/funcA.o funcA.asm

# task 2
scmp.o: scmp.c
	gcc $(C_COMPILE_FLAGS) -o bin/scmp.o scmp.c

cmpstr.o: cmpstr.c
	gcc $(C_COMPILE_FLAGS) -o bin/cmpstr.o cmpstr.c

cmpstr_asm.o: cmpstr.s
	nasm $(ASM_COMPILE_FLAGS) -o bin/cmpstr_asm.o cmpstr.s

# task 3
rev_str.o: task3.s
	nasm $(ASM_COMPILE_FLAGS) -o bin/rev_str.o task3.s

# ----------------------------------------------------------------------------------

#tell make that "clean" is not a file name!
.PHONY: clean

#Clean the build directory
clean:
	rm -f bin/*