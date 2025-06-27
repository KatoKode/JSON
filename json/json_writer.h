#ifndef JSON_WRITER_H
#define JSON_WRITER_H  1

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include "../util/util.h"
#include "json_struc.h"
#include "json_builder.h"

typedef struct json_writer json_writer_t;

struct json_writer {
  FILE *          file;
  json_t *        json;
};

#define json_writer_alloc() (calloc(1, sizeof(json_t)))
#define json_writer_free(P) (free(P), P = NULL)
#define as_json_writer(P) ((json_writer_t *)P)

int json_writer_init (json_writer_t *, json_t *, char const *);
int json_writer_do (json_writer_t *);
void json_writer_term (json_writer_t *);

#endif
