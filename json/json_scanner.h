#ifndef json_scannerNER_H
#define json_scannerNER_H  1

#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "../util/util.h"
#include "json_token.h"

typedef struct json_scanner json_scanner_t;

struct json_scanner {
  size_t          start;
  size_t          current;
  size_t          length;
  char const *    source;
  list_t          list;
};

#define json_scanner_alloc() (calloc(1, sizeof(json_scanner_t)))
#define json_scanner_free(P) (free(P), P = NULL)

int json_scanner_do (json_scanner_t *);
int json_scanner_init (json_scanner_t *, char const *);
void json_scanner_term (json_scanner_t *);

#endif
