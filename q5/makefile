all: hello

hello: hello.o
	gcc -g -o hello hello.o

hello.o: hello.c
	gcc -g -c hello.c

valgrind: hello
	valgrind --vgdb-error=0 --tool=memcheck -v --leak-check=full --show-leak-kinds=all  --error-exitcode=99 --track-origins=yes ./hello

clean:
	rm -f hello hello.o