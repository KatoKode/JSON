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
