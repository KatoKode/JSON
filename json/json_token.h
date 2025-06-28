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
#ifndef JSON_TOKEN_H
#define JSON_TOKEN_H

#include <unistd.h>
#include <stdint.h>

#define JSON_LEXEME_SIZE    255L
#define JSON_LITERAL_SIZE   1023L

typedef enum json_class json_class_t;

enum json_class {
  // single-character tokens
  JSON_CLASS_BOOLEAN,
  JSON_CLASS_DOUBLE_QUOTE,
  JSON_CLASS_COMMA,
  JSON_CLASS_COLON,
  JSON_CLASS_LEFT_BRACKET,
  JSON_CLASS_RIGHT_BRACKET,
  JSON_CLASS_LEFT_BRACE,
  JSON_CLASS_RIGHT_BRACE,

  // literals
  JSON_CLASS_IDENTIFIER,
  JSON_CLASS_DOUBLE,
  JSON_CLASS_LONG,
  JSON_CLASS_STRING,

  // end of tokens
  JSON_CLASS_EOT
};

typedef struct json_token json_token_t;

struct json_token {
  size_t        type;
  size_t        offset;
  size_t        length;
  union {
    long          i;
    double        d;
  } numeric;
  char          lexeme [ JSON_LEXEME_SIZE + 1 ];
  char          literal [ JSON_LITERAL_SIZE + 1 ];
};

#define json_token_alloc() (calloc(1, sizeof(json_token_t)))
#define json_token_free(P) (free(P), P = NULL)

#define as_json_token(P) ((json_token_t *)P)

#endif

