/*------------------------------------------------------------------------------
    JSON (JSON) Library Implementation in C with Assembly Language Support
    Libraries

    Copyright (C) 2025  J. McIntosh

    JSON is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    JSON is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with JSON; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
------------------------------------------------------------------------------*/
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
