#include "s21_grep_file_processing.h"

int process(FILE *file, char *filename, char *template, int i, int v, int c,
            int l, int n, int h, int o) {
  regex_t regex;
  int cflags = REG_EXTENDED;
  cflags = 0;
  if (i) cflags |= REG_ICASE;

  int reti = regcomp(&regex, template, cflags);
  if (reti) {
    fprintf(stderr, "Could not compile regex\n");
    return 1;
  }

  int line_number = 0;
  int match_count = 0;
  char *line = NULL;
  size_t len;
  int str_len;
  while ((str_len = getline(&line, &len, file)) != -1) {
    line_number++;

    int reti = regexec(&regex, line, 0, NULL, 0);
    int is_match = (reti == 0);

    if ((is_match && !v) || (!is_match && v)) {
      match_count++;
      if (l) {
        printf("%s\n", filename);
        break;
      }
      if (!c && !l)
        process_matched_line(filename, line, line_number, &regex, h, n, o,
                             str_len);
    }
  }
  if (c && !l) {
    if (!h && !o) printf("%s:", filename);
    printf("%d\n", match_count);
  }
  regfree(&regex);
  free(line);

  return 0;
}

void process_matched_line(const char *filename, const char *line,
                          int line_number, regex_t *regex, int h, int n, int o,
                          size_t str_len) {
  if (!h && !o) printf("%s:", filename);
  if (n && !o) printf("%d:", line_number);
  if (o) {
    regmatch_t match;
    char *line_ptr = (char *)line;
    while (regexec(regex, line_ptr, 1, &match, 0) == 0) {
      if (!h) printf("%s:", filename);
      if (n) printf("%d:", line_number);

      for (int i = match.rm_so; i < match.rm_eo; i++) {
        printf("%c", line_ptr[i]);
      }
      printf("\n");
      line_ptr += match.rm_eo;
    }
  }
  if (!o) {
    printf("%s", line);
    if (line[str_len - 1] != '\n') printf("\n");
  }
}