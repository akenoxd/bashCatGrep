CC=gcc
CFLAGS= -Wall -Wextra -Werror
DEBUGFLAGS= -g

s21_cat: s21_cat.o s21_cat_file_processing.o
	$(CC) $(CFLAGS) $^ -o $@

s21_cat.o: s21_cat.c
	$(CC) $(CFLAGS) -c $< -o $@

s21_cat_file_processing.o: s21_cat_file_processing.c
	$(CC) $(CFLAGS) -c $< -o $@

test: s21_cat
	bash test.sh

clean:
	rm -f s21_cat *.o

rebuild: clean s21_cat

all: rebuild

debug: CFLAGS += $(DEBUGFLAGS)
debug: rebuild

.PHONY: all clean rebuild debug