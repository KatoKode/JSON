/*------------------------------------------------------------------------------
    JSON Library Implementation in C with Assembly Language Support Libraries
    Copyright (C) 2025  J. McIntosh

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
------------------------------------------------------------------------------*/
#ifndef JSON_SCANNER_H
#define JSON_SCANNER_H  1

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
