#include <getopt.h>
#include <stdio.h>

#include "s21_cat_file_processing.h"

void handle_flags(int argc, char **argv, int *b, int *e, int *n, int *s, int *t,
                  int *v, int *ret);
void print_help();

int main(int argc, char **argv) {
  int ret = 0;
  int b = 0, e = 0, n = 0, s = 0, t = 0, v = 0;

  handle_flags(argc, argv, &b, &e, &n, &s, &t, &v, &ret);

  if (!ret) {
    for (int i = optind; i < argc; i++) process_file(argv[i], b, e, n, s, t, v);
  } else {
    print_help();
  }
  return 0;
}

void handle_flags(int argc, char **argv, int *b, int *e, int *n, int *s, int *t,
                  int *v, int *ret) {
  int opt;
  struct option longopts[] = {{"number-nonblank", 0, NULL, 'b'},
                              {"number", 0, NULL, 'n'},
                              {"squeeze-blank", 0, NULL, 's'},
                              {0, 0, 0, 0}};

  while ((opt = getopt_long(argc, argv, "beEnstTv", longopts, NULL)) != -1) {
    switch (opt) {
      case 'b':
        *b = 1;
        break;
      case 'e':
        *e = 1;
        *v = 1;
        break;
      case 'E':
        *e = 1;
        break;
      case 'n':
        *n = 1;
        break;
      case 's':
        *s = 1;
        break;
      case 't':
        *t = 1;
        *v = 1;
        break;
      case 'T':
        *t = 1;
        break;
      case 'v':
        *v = 1;
        break;
      default:
        *ret = 1;
        break;
    }
  }
  if (optind == argc) *ret = 1;
}

void print_help() {
  printf("Usage: s21_cat [OPTIONS] FILE...\n");
  printf("Options:\n");
  printf("  -b    Number non-blank output lines\n");
  printf("  -e    Display non-printing characters\n");
  printf("  -n    Number all output lines\n");
  printf("  -s    Squeeze multiple adjacent empty lines\n");
  printf("  -t    Display tab characters as `^I`\n");
  printf("  -v    Display non-printing characters\n");
}
