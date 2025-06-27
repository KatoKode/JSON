#ifndef JSON_PARSER_H
#define JSON_PARSER_H 1

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "../util/util.h"
#include "json_token.h"
#include "json_struc.h"
#include "json_scanner.h"
#include "json_builder.h"

typedef struct json_parser json_parser_t;

struct json_parser {
  json_t *          json;
  json_scanner_t *  json_scanner;
  lifo_t            lifo;
};

#define json_parser_alloc() (calloc(1, sizeof(json_parser_t)))
#define json_parser_free(P) (free(P), P = NULL)

int json_parser_do (json_parser_t *);
int json_parser_init (json_parser_t *, json_scanner_t *);
void json_parser_term (json_parser_t *);

#endif
