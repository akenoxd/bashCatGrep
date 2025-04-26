#ifndef S21_GREP_FILE_PROCESSING_H
#define S21_GREP_FILE_PROCESSING_H
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
int process(FILE *file, char *filename, char *template, int i, int v, int c,
            int l, int n, int h, int o);
void process_matched_line(const char *filename, const char *line,
                          int line_number, regex_t *regex, int h, int n, int o,
                          size_t str_len);
#endif