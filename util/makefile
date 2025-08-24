#-------------------------------------------------------------------------------
#   JSON (JSON) Library Implementation in C with Assembly Language Support
#   Libraries
#
#   Copyright (C) 2025  J. McIntosh
#
#   JSON is free software; you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation; either version 2 of the License, or
#   (at your option) any later version.
#
#   JSON is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU General Public License for more details.
#
#   You should have received a copy of the GNU General Public License along
#   with JSON; if not, write to the Free Software Foundation, Inc.,
#   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
#-------------------------------------------------------------------------------
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
