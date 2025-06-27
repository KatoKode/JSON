# makefile for libutil.so
libutil.so: memmove64.o list.o lifo.o string.o util.o
	gcc -z noexecstack -shared memmove64.o list.o lifo.o string.o util.o \
		-o libutil.so
util.o: util.c
	gcc -fPIC -c util.c -o util.o
string.o: string.asm
	nasm -f elf64 string.asm
lifo.o: lifo.asm
	nasm -f elf64 lifo.asm
list.o: list.asm
	nasm -f elf64 list.asm
memmove64.o: memmove64.asm
	nasm -f elf64 memmove64.asm
.PHONY: clean
clean:
	rm -f libutil.so util.o
	rm -f list.o memmove64.o
	rm -f lifo.o string.o
