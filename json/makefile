#-------------------------------------------------------------------------------
#   JSON Library Implementation in C with Assembly Language Support Libraries
#   Copyright (C) 2025  J. McIntosh
#
#   This program is free software; you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation; either version 2 of the License, or
#   (at your option) any later version.
#
#   This program is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU General Public License for more details.
#
#   You should have received a copy of the GNU General Public License along
#   with this program; if not, write to the Free Software Foundation, Inc.,
#   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
#-------------------------------------------------------------------------------
# makefile for libjson.o
libjson.so: json_builder.o json_writer.o json_scanner.o json_parser.o json.o
	gcc -march=x86-64 -m64 -z noexecstack -shared json_builder.o json_writer.o json_scanner.o \
		json_parser.o json.o -o libjson.so
json.o: json.c
	gcc -march=x86-64 -m64 -z noexecstack -fPIC -c json.c -o json.o
json_builder.o: json_builder.c
	gcc -march=x86-64 -m64 -z noexecstack -fPIC -c json_builder.c -o json_builder.o
json_writer.o: json_writer.c
	gcc -march=x86-64 -m64 -z noexecstack -fPIC -c json_writer.c -o json_writer.o
json_parser.o: json_parser.c
	gcc -march=x86-64 -m64 -z noexecstack -fPIC -c json_parser.c -o json_parser.o
json_scanner.o: json_scanner.c
	gcc -march=x86-64 -m64 -z noexecstack -fPIC -c json_scanner.c -o json_scanner.o
.PHONY: clean
clean:
	rm -f libjson.so json.o
	rm -f json_builder.o
	rm -f json_writer.o
	rm -f json_parser.o
	rm -f json_scanner.o
