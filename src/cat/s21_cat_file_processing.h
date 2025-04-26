#ifndef S21_CAT_FILE_PROCESSING_H
#define S21_CAT_FILE_PROCESSING_H
#include <ctype.h>
#include <stdio.h>

void process_file(const char *filename, int b, int e, int n, int s, int t,
                  int v);
void print_with_flags(FILE *file, int b, int e, int n, int s, int t, int v);
void print_line_number(int *line_number);
void process_char(char c, int e, int t, int v);

#endif