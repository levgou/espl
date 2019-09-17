# flags
C_COMPILE_FLAGS = -g -Wall -m32 -ansi -c
ASM_COMPILE_FLAGS = -g -f elf -w+all
LINK_FLAGS = -m32 -g -Wall

# All Target
all: mk_bin prog

mk_bin:
	mkdir -p bin

prog: fd.o open_close.o
	gcc  $(LINK_FLAGS) -o bin/prog bin/fd.o bin/open_close.o

fd.o:
	gcc $(C_COMPILE_FLAGS) -o bin/fd.o fd.c

open_close.o: open_close.asm
	nasm $(ASM_COMPILE_FLAGS) -o bin/open_close.o open_close.asm


#tell make that "clean" is not a file name!
.PHONY: clean

#Clean the build directory
clean:
	rm -f bin/*