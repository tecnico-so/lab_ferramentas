CFLAGS = -g -Wall -std=c17

test: test.o bst.o
	gcc $(CFLAGS) test.o bst.o -o test

test.o: test.c bst.h
	gcc $(CFLAGS) -c test.c -o test.o

bst.o: bst.c bst.h
	gcc $(CFLAGS) -c bst.c -o bst.o

clean:
	rm -f *.o test

clean2:
	rm -f *.o

run:
	./test

run1:
	./test < tree1.txt

run2:
	./test < tree2.txt

