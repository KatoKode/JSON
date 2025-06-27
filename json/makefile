# makefile for libjson.o
libjson.so: json_builder.o json_writer.o json_scanner.o json_parser.o json.o
	gcc -z noexecstack -shared json_builder.o json_writer.o json_scanner.o \
		json_parser.o json.o -o libjson.so
json.o: json.c
	gcc -fPIC -c json.c -o json.o
json_builder.o: json_builder.c
	gcc -fPIC -c json_builder.c -o json_builder.o
json_writer.o: json_writer.c
	gcc -fPIC -c json_writer.c -o json_writer.o
json_parser.o: json_parser.c
	gcc -fPIC -c json_parser.c -o json_parser.o
json_scanner.o: json_scanner.c
	gcc -fPIC -c json_scanner.c -o json_scanner.o
.PHONY: clean
clean:
	rm -f libjson.so json.o
	rm -f json_builder.o
	rm -f json_writer.o
	rm -f json_parser.o
	rm -f json_scanner.o
