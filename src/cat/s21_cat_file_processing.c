#include "s21_cat_file_processing.h"
void process_file(const char *filename, int b, int e, int n, int s, int t,
                  int v) {
  FILE *file = fopen(filename, "r");
  if (!file) {
    perror(filename);
  } else {
    print_with_flags(file, b, e, n, s, t, v);
    fclose(file);
  }
}

void print_line_number(int *line_number) { printf("%6d\t", (*line_number)++); }

void process_char(char c, int e, int t, int v) {
  if (c == '\n' && e) printf("$");

  if (c == '\t' && t) {
    printf("^I");
  } else if (v && !isprint(c) && c >= 0 && c <= 31 && c != '\n' && c != '\t') {
    printf("^%c", c + 64);
  } else {
    printf("%c", c);
  }
}

void print_with_flags(FILE *file, int b, int e, int n, int s, int t, int v) {
  static int line_number = 1;
  static char prev_char = '\n';
  static int skipped = 0;
  char c;

  while ((c = fgetc(file)) != EOF) {
    if (c != '\n') skipped = 0;

    if (c == '\n' && prev_char == '\n' && s) {
      if (!skipped) {
        skipped = 1;
        if (n && !b) print_line_number(&line_number);
        process_char(c, e, t, v);
        prev_char = c;
      }
    } else {
      if (prev_char == '\n' && c != '\n' && (b || n))
        print_line_number(&line_number);
      else if (prev_char == '\n' && c == '\n' && n && !b)
        print_line_number(&line_number);
      process_char(c, e, t, v);
      prev_char = c;
    }
  }
}
