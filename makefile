CC          =	gcc
# Flags that are sent to the compiler
# Do not change these
CFLAGS      =	-Wall -ansi -pedantic -g -std=gnu99

#Directories where the compiler can find things
INCLUDES    =   -Iinclude

all: bin/n1 bin/n2 bin/n3 bin/n4 bin/n5 bin/n6 bin/n7

bin/n1: src/n1.c src/linkedList.c
	$(CC) $(CFLAGS) src/n1.c src/linkedList.c -o bin/n1 -Iinclude -g
bin/n2:	src/n2.c src/linkedList.c
	$(CC) $(CFLAGS) src/n2.c src/linkedList.c -o bin/n2 -Iinclude -g
bin/n3:	src/n3.c src/linkedList.c 
	$(CC) $(CFLAGS) src/n3.c src/linkedList.c -o bin/n3 -Iinclude -g
bin/n4: src/n4.c src/linkedList.c
	$(CC) $(CFLAGS) src/n4.c src/linkedList.c -o bin/n4 -Iinclude -g
bin/n5:	src/n5.c src/linkedList.c
	$(CC) $(CFLAGS) src/n5.c src/linkedList.c -o bin/n5 -Iinclude -g
bin/n6:	src/n6.c src/linkedList.c
	$(CC) $(CFLAGS) src/n6.c src/linkedList.c -o bin/n6 -Iinclude -g
bin/n7:	src/n7.c src/linkedList.c
	$(CC) $(CFLAGS) src/n7.c src/linkedList.c -o bin/n7 -Iinclude -g


run: bin/n1 bin/n2 bin/n3 bin/n4 bin/n5 bin/n6 bin/n7
	@ rm -f /tmp/link*
	 ./bin/n7 & ./bin/n6 & ./bin/n5 & ./bin/n4 & ./bin/n3 & ./bin/n2 & ./bin/n1

clean:
	@ rm -rf bin/*
