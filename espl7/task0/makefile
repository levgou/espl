# flags
C_COMPILE_FLAGS = -g -Wall -m32 -ansi -c
LINK_FLAGS = -m32 -g -Wall

mypipe: mypipe.c
	gcc  $(LINK_FLAGS) -o mypipe mypipe.c 


#tell make that "clean" is not a file name!
.PHONY: clean

#Clean the build directory
clean:
	rm -f bin/*
