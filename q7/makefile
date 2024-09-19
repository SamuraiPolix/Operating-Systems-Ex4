all: race race2

race: race.o
	gcc -g -o race race.o

race2: race2.o
	gcc -g -o race2 race2.o

race.o: race.c
	gcc -g -c race.c

race2.o: race2.c
	gcc -g -c race2.c

valgrind: race
	# valgrind --vgdb-error=0 --tool=memcheck -v --leak-check=full --show-leak-kinds=all  --error-exitcode=99 --track-origins=yes ./race
	valgrind --tool=helgrind ./race

clean:
	rm -f race race.o race2 race2.o