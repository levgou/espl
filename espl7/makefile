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
task2: task2b.o task2a.o LineParser.o cmd_history.o prompt_flow_utils.o
	gcc  $(LINK_FLAGS) -o bin/task2 bin/LineParser.o bin/prompt_flow_utils.o bin/cmd_history.o bin/task2b.o bin/task2a.o

task1: task1.o LineParser.o cmd_history.o prompt_flow_utils.o
	gcc  $(LINK_FLAGS) -o bin/task1 bin/LineParser.o bin/prompt_flow_utils.o bin/cmd_history.o bin/task1.o

# ----------------------------------------------------------------------------------------------------------------------
# --- Compile - Tasks ---
# ----------------------------------------------------------------------------------------------------------------------
task1.o: task1.c
	gcc  $(C_COMPILE_FLAGS) -o bin/task1.o task1.c

task2a.o: task2a.c
	gcc  $(C_COMPILE_FLAGS) -o bin/task2a.o task2a.c

task2b.o: task2b.c
	gcc  $(C_COMPILE_FLAGS) -o bin/task2b.o task2b.c

# ----------------------------------------------------------------------------------------------------------------------
# --- Compile - Helpers ---
# ----------------------------------------------------------------------------------------------------------------------
LineParser.o : LineParser.c
	gcc  $(C_COMPILE_FLAGS) -o bin/LineParser.o LineParser.c

cmd_history.o: cmd_history.c
	gcc  $(C_COMPILE_FLAGS) -o bin/cmd_history.o cmd_history.c

prompt_flow_utils.o: prompt_flow_utils.c
	gcc  $(C_COMPILE_FLAGS) -o bin/prompt_flow_utils.o prompt_flow_utils.c

#tell make that "clean" is not a file name!
.PHONY: clean

#Clean the build directory
clean:
	rm -f bin/*
