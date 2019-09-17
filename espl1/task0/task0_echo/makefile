# flags
C_COMPILE_FLAGS = -g -Wall -m32 -ansi -c
ASM_COMPILE_FLAGS = -g -f elf -w+all
LINK_FLAGS = -m32 -g -Wall

# All Target
all: my_echo

my_echo: my_echo.c
	gcc  $(LINK_FLAGS) -o bin/my_echo my_echo.c



#tell make that "clean" is not a file name!
.PHONY: clean

#Clean the build directory
clean:
	rm -f bin/*