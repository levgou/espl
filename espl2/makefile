# flags
C_COMPILE_FLAGS = -g -Wall -m32 -ansi -c
LINK_FLAGS = -m32 -g -Wall


all: menu

# task1:
addresses: addresses.c
	gcc  $(LINK_FLAGS) -o bin/addresses addresses.c

# tasks 2-3:
menu: utills.o task2a.o task2b.o task2c.o task3.o
	gcc  $(LINK_FLAGS) -o bin/menu bin/utills.o bin/task2a.o bin/task2b.o bin/task2c.o bin/task3.o

utills.o: utills.c
	gcc $(C_COMPILE_FLAGS) -o bin/utills.o utills.c

task2a.o: utills.o task2a.c 
	gcc $(C_COMPILE_FLAGS) -o bin/task2a.o task2a.c

task2b.o: task2b.c
	gcc $(C_COMPILE_FLAGS) -o bin/task2b.o task2b.c

task2c.o: task2a.o task2c.c
	gcc $(C_COMPILE_FLAGS) -o bin/task2c.o task2c.c

task3.o: task2a.o task2b.o task2c.o task3.c
	gcc $(C_COMPILE_FLAGS) -o bin/task3.o task3.c

#tell make that "clean" is not a file name!
.PHONY: clean

#Clean the build directory
clean:
	rm -f bin/*