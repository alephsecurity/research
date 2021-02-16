.PHONY: all clean

CC=gcc
CFLAGS=

NASM=nasm
NASM_FLAGS=-f elf64

LD=ld


all: exploit crash decoy

exploit: exploit.c
	$(CC) -o $@ $< $(CFLAGS)
	chmod +x $@

crash: crash.o
	$(LD) $^ -o $@

decoy: decoy.o
	$(LD) $^ -o $@

crash.o: crash.asm
	$(NASM) $(NASM_FLAGS) $^ 

decoy.o: decoy.asm
	$(NASM) $(NASM_FLAGS) $^ 


clean:
	rm exploit decoy crash *.o