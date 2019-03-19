main: ask2.o main.o hash_table.o
	gcc ask2.o main.o hash_table.o -o main

main.o: main.c
	gcc -c main.c

hash_table.o: hash_table.c
	gcc -c hash_table.c

ask2.o: ask2.c
	gcc -c ask2.c
	
clean:
	rm -f main ask2.o main.o hash_table.o

run1:
	main k 10 frames 60 q 100 max 10000

run2:
	main k 20 frames 60 q 100 max 10000

run3:
	main k 30 frames 60 q 100 max 10000
