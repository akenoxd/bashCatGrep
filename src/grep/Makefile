CC=gcc
CFLAGS= -Wall -Wextra -Werror
DEBUGFLAGS= -g

s21_grep: s21_grep.o s21_grep_file_processing.o
	$(CC) $(CFLAGS) $^ -o $@

s21_grep.o: s21_grep.c
	$(CC) $(CFLAGS) -c $< -o $@

s21_grep_file_processing.o: s21_grep_file_processing.c
	$(CC) $(CFLAGS) -c $< -o $@

test: s21_grep
	bash test.sh

clean:
	rm -f s21_grep *.o

rebuild: clean s21_grep
	
all: rebuild

debug: CFLAGS += $(DEBUGFLAGS)
debug: rebuild

.PHONY: all clean rebuild debug
