#include <getopt.h>
#include <stdio.h>
#include <string.h>

#include "s21_grep_file_processing.h"

void add_template(char *template, char *new_template);
void add_templates_from_file(char *template, char *filename);

int parse_flags(int argc, char *argv[], char *template, int *e, int *i, int *v,
                int *c, int *l, int *n, int *h, int *s, int *f, int *o);
void print_help();

int main(int argc, char **argv) {
  int e = 0, i = 0, v = 0, c = 0, l = 0, n = 0, h = 0, s = 0, f = 0, o = 0;
  char template[2048];

  if (parse_flags(argc, argv, template, &e, &i, &v, &c, &l, &n, &h, &s, &f,
                  &o) != 0) {
    return 1;
  }

  if (optind < argc) {
    if (!e && !f) {
      add_template(template, argv[optind]);
      optind++;
    }

    if (optind == argc - 1) h = 1;

    for (int j = optind; j < argc; j++) {
      FILE *file = fopen(argv[j], "r");
      if (!file) {
        if (!s) perror(argv[j]);
      } else {
        process(file, argv[j], template, i, v, c, l, n, h, o);
        fclose(file);
      }
    }
  } else {
    print_help();
  }
  return 0;
}

void add_template(char *template, char *new_template) {
  static int count = 0;
  if (count == 0) {
    strcpy(template, new_template);
    count++;
  } else {
    strcat(template, "\\|");
    strcat(template, new_template);
    count++;
  }
}

void add_templates_from_file(char *template, char *filename) {
  FILE *file = fopen(filename, "r");
  if (!file) {
    perror(filename);
  } else {
    char *line = NULL;
    size_t len;
    int str_len;
    while ((str_len = getline(&line, &len, file)) != -1) {
      if (line[str_len - 1] == '\n') line[str_len - 1] = '\0';
      if (strlen(line) > 0) add_template(template, line);
    }
    free(line);
    fclose(file);
  }
}

int parse_flags(int argc, char *argv[], char *template, int *e, int *i, int *v,
                int *c, int *l, int *n, int *h, int *s, int *f, int *o) {
  int opt;
  while ((opt = getopt(argc, argv, "e:ivoclnhsf:o")) != -1) {
    switch (opt) {
      case 'e':
        *e = 1;
        add_template(template, optarg);
        break;
      case 'i':
        *i = 1;
        break;
      case 'v':
        *v = 1;
        break;
      case 'c':
        *c = 1;
        break;
      case 'l':
        *l = 1;
        break;
      case 'n':
        *n = 1;
        break;
      case 'h':
        *h = 1;
        break;
      case 's':
        *s = 1;
        break;
      case 'f':
        add_templates_from_file(template, optarg);
        *f = 1;
        break;
      case 'o':
        *o = 1;
        break;
      default:
        print_help();
        return 1;
    }
  }
  return 0;
}

void print_help() { printf("Usage: s21_grep [OPTIONS] PATTERN FILE...\n"); }