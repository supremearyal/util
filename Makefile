CC = gcc
CFLAGS = -Wall -Werror -Wextra -ansi -pedantic

all: flash_cards

lib: string.o llist.o skip_list.o pair.o map.o vector.o queue.o
	ar rcs libclib.a string.o llist.o skip_list.o pair.o map.o vector.o queue.o

string.o: string.c string.h
	$(CC) $(CFLAGS) -c string.c

llist.o: llist.c llist.h
	$(CC) $(CFLAGS) -c llist.c

skip_list.o: skip_list.c skip_list.h
	$(CC) $(CFLAGS) -c skip_list.c

pair.o: pair.c pair.h
	$(CC) $(CFLAGS) -c pair.c

map.o: map.c map.h skip_list.c skip_list.h pair.c pair.h vector.c vector.h
	$(CC) $(CFLAGS) -c map.c

vector.o: vector.c vector.h
	$(CC) $(CFLAGS) -c vector.c

queue.o: queue.c queue.h llist.c llist.h
	$(CC) $(CFLAGS) -c queue.c

string_test: string_test.c string.o
	$(CC) $(CFLAGS) -o string_test string_test.c string.o

string_cmp_test: string_cmp_test.c string.o
	$(CC) $(CFLAGS) -o string_cmp_test string_cmp_test.c string.o

llist_test: llist_test.c llist.o string.o
	$(CC) $(CFLAGS) -o llist_test llist_test.c llist.o string.o

skip_list_test: skip_list_test.c skip_list.o string.o
	$(CC) $(CFLAGS) -o skip_list_test skip_list_test.c skip_list.o string.o

map_test: map_test.c map.o pair.o skip_list.o string.o vector.o
	$(CC) $(CFLAGS) -o map_test map_test.c map.o pair.o skip_list.o string.o vector.o

vector_test: vector_test.c vector.o string.o
	$(CC) $(CFLAGS) -o vector_test vector_test.c vector.o string.o

queue_test: queue_test.c queue.o llist.o
	$(CC) $(CFLAGS) -o queue_test queue_test.c queue.o llist.o

flash_cards: flash_cards.c map.o vector.o pair.o skip_list.o string.o
	$(CC) $(CFLAGS) -o flash_cards flash_cards.c map.o pair.o skip_list.o string.o vector.o

clean:
	rm -rf *.o string_cmp_test string_test llist_test skip_list_test map_test vector_test queue_test flash_cards
