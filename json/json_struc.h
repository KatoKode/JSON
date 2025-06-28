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
#ifndef JSON_STRUC_H
#define JSON_STRUC_H  1

#include <unistd.h>
#include "../util/util.h"

#define JSON_NULL         0x00
#define JSON_BOOLEAN      0x71
#define JSON_DOUBLE       0x72
#define JSON_LONG         0x73
#define JSON_STRING       0x74
#define JSON_ARRAY        0x75
#define JSON_OBJECT       0x76
#define JSON_VALUE        0x77

#define JSON_BUFFER_SIZE  64

#define JSON_NAME_LEN     255
#define JSON_VALUE_LEN    1023

static char const o_sq_bracket  =   '[';
static char const c_sq_bracket  =   ']';
static char const o_cr_brace    =   '{';
static char const c_cr_brace    =   '}';
static char const colon         =   ':';
static char const comma         =   ',';
static char const d_quote       =   '\"';

static char const *json_true   = "true";
static char const *json_false  = "false";

typedef int json_type_t;

typedef void json_member_t;

typedef struct json_value json_value_t;

struct json_value {
  json_type_t   type;
  union {
    long        lng;
    double      dbl;
    char *      str;
  } value;
};

#define json_value_alloc() (calloc(1, sizeof(json_value_t)))
#define json_value_free(P) (free(P), P = NULL)
#define as_json_value(P) ((json_value_t *)P)

typedef struct json_list json_list_t;

struct json_list {
  json_type_t   type;
  list_t        list;
};

#define as_json_list(P) ((json_list_t *)P)

typedef struct json_list json_array_t;

#define json_array_alloc() (calloc(1, sizeof(json_array_t)))
#define json_array_free(P) (free(P), P = NULL)
#define as_json_array(P) ((json_array_t *)P)

typedef struct json_list json_object_t;

#define json_object_alloc() (calloc(1, sizeof(json_object_t)))
#define json_object_free(P) (free(P), P = NULL)
#define as_json_object(P) ((json_object_t *)P)

typedef struct json_node json_node_t;

struct json_node {
  void *        member;
};

#define json_node_alloc() (calloc(1, sizeof(json_node_t)))
#define json_node_free(P) (free(P), P = NULL)
#define as_json_node(P) ((json_node_t *)P)

typedef struct json_pair json_pair_t;

struct json_pair {
  char *        name;
  void *        member;
};

#define json_pair_alloc() (calloc(1, sizeof(json_pair_t)))
#define json_pair_free(P) (free(P), P = NULL)
#define as_json_pair(P) ((json_pair_t *)P)

typedef struct json json_t;

struct json {
  list_t        list;
};

#define json_alloc() (calloc(1, sizeof(json_t)))
#define json_free(P) (free(P), P = NULL)
#define as_json(P) ((json_t *)P)

#endif
