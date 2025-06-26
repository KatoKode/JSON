json_test: main.o ../util/libutil.so ../json/libjson.so
	gcc -g main.o ../util/libutil.so ../json/libjson.so -o json_test
main.o: main.c
	gcc -g -c main.c -o main.o
clean:
	rm -f json_test main.o
