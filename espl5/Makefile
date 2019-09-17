%.o: %.asm
	nasm -g -O1 -f elf -o $@ $<

%.o: %.c
	gcc -m32 -g -nostdlib -fno-stack-protector -c -o $@ $<

all: clean lwca lwca_s lwca_s_final

lwca: lwc.o task1a.o task1b.o
	ld  -melf_i386 -o $@ $^

lwca_s: task2a.o
	ld  -melf_i386 -o $@ $^

lwca_s_final: task2b.o
	ld  -melf_i386 -o $@ $^

clean:
	rm -f *.o lwca lwca_s lwca_s_final
