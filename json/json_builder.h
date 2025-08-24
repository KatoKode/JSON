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
#ifndef JSON_BUILDER_H
#define JSON_BUILDER_H  1

#include <unistd.h>
#include <stdlib.h>
#include "../util/util.h"
#include "json_struc.h"

int json_add_array (json_t *, char *, json_array_t *);
int json_add_member (json_t *, char *, json_member_t *);
int json_add_object (json_t *, char *, json_object_t *);
int json_add_value (json_t *, char  *, json_value_t *);
int json_delete_member (json_t *, char const *);
int json_init (json_t *);
json_member_t * json_search (json_t *, char *);
void json_term (json_t *);

int json_array_add_array (json_array_t *, json_array_t *);
int json_array_add_member (json_array_t *, json_member_t *);
int json_array_add_object (json_array_t *, json_object_t *);
int json_array_add_value (json_array_t *, json_value_t *);
json_member_t * json_array_begin(json_array_t *);
int json_array_delete_member (json_array_t *, size_t);
json_member_t * json_array_get_member (json_array_t *, size_t);
int json_array_init (json_array_t *);
json_member_t * json_array_next(json_array_t *);
void json_array_term (json_array_t *);

int json_member_type (json_member_t *);

int json_object_add_array (json_object_t *, char *, json_array_t *);
int json_object_add_member (json_object_t *, char *, json_member_t *);
int json_object_add_object (json_object_t *, char *, json_object_t *);
int json_object_add_value (json_object_t *, char *, json_value_t *);
int json_object_delete_member (json_object_t *, char const *);
int json_object_init (json_object_t *);
json_member_t * json_object_search (json_object_t *, char *);
void json_object_term (json_object_t *);

void json_pair_init (json_pair_t *, char *, json_member_t *);
void json_pair_term (json_pair_t *);

char const * json_value_get_boolean (json_value_t *);
double json_value_get_double (json_value_t *);
long json_value_get_long (json_value_t *);
char * json_value_get_string (json_value_t *);
void json_value_set_boolean (json_value_t *, char const *);
void json_value_set_double (json_value_t *, double);
void json_value_set_long (json_value_t *, long);
void json_value_set_string (json_value_t *, char *);
void json_value_term (json_value_t *);

int json_walk (json_t *, void *,
    int (*enter_cb) (char const *, json_member_t *, void *),
    int (*exit_cb) (char const *, json_member_t *, void *));

int json_add_boolean_value (json_t *, char *, char const *);
int json_add_double_value (json_t *, char *, double);
int json_add_long_value (json_t *, char *, long);
int json_add_string_value (json_t *, char *, char *);
int json_array_add_boolean_value (json_array_t *, char const *);
int json_array_add_double_value (json_array_t *, double);
int json_array_add_long_value (json_array_t *, long);
int json_array_add_string_value (json_array_t *, char *);
int json_object_add_boolean_value (json_object_t *, char *, char const *);
int json_object_add_double_value (json_object_t *, char *, double);
int json_object_add_long_value (json_object_t *, char *, long);
int json_object_add_string_value (json_object_t *, char *, char *);
#endif
