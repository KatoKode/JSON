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
#include "json.h"
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// DECLARATION
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void json_delete_cb (void const *);

void json_member_free (json_member_t *);
void json_member_term (json_member_t *);

void json_node_init (json_node_t *, json_member_t *);
void json_node_term (json_node_t *);

int json_traverse_array (json_member_t *, void *,
    int (*enter_cb) (char const *, json_member_t *, void *),
    int (*exit_cb) (char const *, json_member_t *, void *));

int json_traverse_object (json_member_t *, void *,
    int (*enter_cb) (char const *, json_member_t *, void *),
    int (*exit_cb) (char const *, json_member_t *, void *));
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_ADD_ARRAY
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int json_add_array (json_t *json, char *name, json_array_t *array)
{
  array->type = JSON_ARRAY;
  return json_add_member(json, name, array);
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_ADD_MEMBER
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int json_add_member (json_t *json, char *name, json_member_t *member)
{
  json_pair_t *curr;
  for (curr = list_begin(&json->list);
      curr != NULL;
      curr = list_next(&json->list))
  {
    if (strncmp(name, curr->name, JSON_NAME_LEN) == 0) break;
  }

  if (curr == NULL)
  {
    json_pair_t pair;
    json_pair_init(&pair, name, member);
    return list_add(&json->list, &pair);
  }

  json_pair_term(curr);
  json_pair_init(curr, NULL, member);

  return 0;
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_ADD_OBJECT
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int json_add_object (json_t *json, char *name, json_object_t *object)
{
  object->type = JSON_OBJECT;
  return json_add_member(json, name, object);
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_SEARCH
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void * json_search (json_t *json, char *name)
{
  for (json_pair_t *pair = list_begin(&json->list);
      pair != NULL;
      pair = list_next(&json->list))
  {
    if (strncmp(pair->name, name, JSON_NAME_LEN) == 0) return pair->member;
  }

  return NULL;
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_ADD_VALUE
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int json_add_value (json_t *json, char *name, json_value_t *value)
{
  return json_add_member(json, name, value);
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_ARRAY_ADD_ARRAY
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int json_array_add_array (json_array_t *array, json_array_t *member)
{
  return json_array_add_member(array, member);
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_ARRAY_ADD_MEMBER
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int json_array_add_member (json_array_t *array, json_member_t *member)
{
  json_node_t node;
  json_node_init(&node, member);

  return list_add(&array->list, &node);
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_ARRAY_ADD_OBJECT
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int json_array_add_object (json_array_t *array, json_object_t *object)
{
  return json_array_add_member(array, object);
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_ARRAY_ADD_VALUE
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int json_array_add_value (json_array_t *array, json_value_t *value)
{
  return json_array_add_member(array, value);
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_ARRAY_BEGIN
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
json_member_t * json_array_begin(json_array_t *json_array)
{
  json_node_t *json_node;
  if ((json_node = list_begin(&json_array->list)) == NULL) return NULL;
  return json_node->member;
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_ARRAY_GET_MEMBER
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
json_member_t * json_array_get_member (json_array_t *json_array, size_t index)
{
  json_node_t *json_node;
  if ((json_node = list_at(&json_array->list, index)) == NULL) return NULL;
  return json_node->member;
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_ARRAY_INIT
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int json_array_init (json_array_t *array)
{
  array->type = JSON_ARRAY;
  return list_init(&array->list, sizeof(json_node_t));
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_ARRAY_NEXT
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
json_member_t * json_array_next(json_array_t *json_array)
{
  json_node_t *json_node;
  if ((json_node = list_next(&json_array->list)) == NULL) return NULL;
  return json_node->member;
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_ARRAY_TERM
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void json_array_term (json_array_t *array) {
  for (json_node_t *node = list_begin(&array->list);
      node != NULL;
      node = list_next(&array->list))
  {
    json_node_term(node);
  }

  list_term(&array->list);
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_DELETE_CB
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void json_delete_cb (void const *p)
{
  json_node_t *node = (json_node_t *)p;
  json_node_term(node);
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_INIT
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int json_init (json_t *json)
{
  return list_init(&json->list, sizeof(json_pair_t));
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_MEMBER_FREE
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void json_member_free (json_member_t *member)
{
  switch (json_member_type(member))
  {
    case JSON_ARRAY:
      json_array_free(member);
      break;
    case JSON_OBJECT:
      json_object_free(member);
      break;
    case JSON_BOOLEAN: case JSON_DOUBLE: case JSON_LONG: case JSON_STRING:
      json_value_free(member);
      break;
    default:;
  }
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_MEMBER_TERM
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void json_member_term (json_member_t *member)
{
  switch (json_member_type(member))
  {
    case JSON_ARRAY:
      json_array_term(member);
      break;
    case JSON_OBJECT:
      json_object_term(member);
      break;
    case JSON_BOOLEAN: case JSON_DOUBLE: case JSON_LONG: case JSON_STRING:
      json_value_term(member);
      break;
    default:;
  }
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_MEMBER_TYPE
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int json_member_type (json_member_t *member)
{
  return *((json_type_t *)member);
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_NODE_INIT
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void json_node_init (json_node_t *node, json_member_t *member)
{
  node->member = member;
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_NODE_TERM
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void json_node_term (json_node_t *node)
{
  json_member_term(node->member);
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_NODE_TYPE
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int json_node_type (json_node_t *node) {
  return json_member_type(node->member);
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_OJECT_ADD_ARRAY
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int json_object_add_array (json_object_t *object,
    char *name, json_array_t *array)
{
  return json_object_add_member(object, name, array);
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_OJECT_ADD_MEMBER
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int json_object_add_member (json_object_t *object,
    char *name, json_member_t *member)
{
  json_pair_t *curr;
  for (curr = list_begin(&object->list);
      curr != NULL;
      curr = list_next(&object->list))
  {
    if (strncmp(name, curr->name, JSON_NAME_LEN) == 0) break;
  }

  if (curr == NULL)
  {
    json_pair_t pair;
    json_pair_init(&pair, name, member);
    return list_add(&object->list, &pair);
  }

  json_pair_term(curr);
  json_pair_init(curr, NULL, member);

  return 0;
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_OJECT_ADD_OBJECT
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int json_object_add_object (json_object_t *object,
    char *name, json_object_t *new_object)
{
  return json_object_add_member(object, name, new_object);
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_OJECT_ADD_VALUE
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int json_object_add_value (json_object_t *object,
    char *name, json_value_t *value)
{
  return json_object_add_member(object, name, value);
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_OBJECT_INIT
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int json_object_init (json_object_t *object)
{
  object->type = JSON_OBJECT;
  return list_init(&object->list, sizeof(json_pair_t));
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_OBJECT_SEARCH
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
json_member_t * json_object_search (json_object_t *object, char *name)
{
  for (json_pair_t *pair = list_begin(&object->list);
      pair != NULL;
      pair = list_next(&object->list))
  {
    if (strncmp(pair->name, name, JSON_NAME_LEN) == 0) return pair->member;
  }

  return NULL;
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_OBJECT_TERM
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void json_object_term (json_object_t *object)
{
  for (json_pair_t *pair = list_begin(&object->list);
      pair != NULL;
      pair = list_next(&object->list))
  {
    json_pair_term(pair);
  }

  list_term(&object->list);
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_PAIR_INIT
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void json_pair_init (json_pair_t *pair, char *name, json_member_t *member)
{
  pair->name = NULL;

  if (name)
  {
    pair->name = strndup(name, JSON_NAME_LEN);
  }

  pair->member = member;
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_PAIR_TERM
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void json_pair_term (json_pair_t *pair)
{
  if (pair->name) free(pair->name);
  json_member_term(pair->member);
  json_member_free(pair->member);
}
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
   JSON_TERM
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
void json_term (json_t *json)
{
  for (json_pair_t *pair = list_begin(&json->list);
      pair != NULL;
      pair = list_next(&json->list))
  {
    json_pair_term(pair);
  }

  list_term(&json->list);
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_TRAVERSE
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int json_traverse (json_member_t *member, char *name, void *cb_data,
    int (*enter_cb) (char const *, json_member_t *, void *),
    int (*exit_cb) (char const *, json_member_t *, void *))
{
  if (enter_cb(name, member, cb_data) < 0) return -1;

  if (json_member_type(member) == JSON_ARRAY)
  {
    if (json_traverse_array(member, cb_data, enter_cb, exit_cb) < 0)
      return -1;
  }
  else if (json_member_type(member) == JSON_OBJECT)
  {
    if (json_traverse_object(member, cb_data, enter_cb, exit_cb) < 0)
      return -1;
  }

  if (exit_cb)
  {
    if (exit_cb(name, member, cb_data) < 0) return -1;
  }

  return 0;
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_TRAVERSE_ARRAY
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int json_traverse_array (json_member_t *member, void *cb_data,
    int (*enter_cb) (char const *, json_member_t *, void *),
    int (*exit_cb) (char const *, json_member_t *, void *))
{
  if (json_member_type(member) == JSON_ARRAY)
  {
    json_list_t *json_list = as_json_list(member);

    for (json_node_t *node = list_begin(&json_list->list);
        node != NULL;
        node = list_next(&json_list->list))
    {
      if (json_traverse(node->member, NULL, cb_data, enter_cb, exit_cb) < 0)
        return -1;
    }
  }
  return 0;
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_TRAVERSE_OBJECT
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int json_traverse_object (json_member_t *member, void *cb_data,
    int (*enter_cb) (char const *, json_member_t *, void *),
    int (*exit_cb) (char const *, json_member_t *, void *))
{
  if (json_member_type(member) == JSON_OBJECT)
  {
    json_list_t *json_list = as_json_list(member);

    for (json_pair_t *m_pair = list_begin(&json_list->list);
        m_pair != NULL;
        m_pair = list_next(&json_list->list))
    {
      if (json_traverse(m_pair->member, m_pair->name,
            cb_data, enter_cb, exit_cb) < 0) return -1;
    }
  }
  return 0;
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_VALUE_GET_BOOLEAN
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
char const * json_value_get_boolean (json_value_t *json_value)
{
  if (json_value->type != JSON_BOOLEAN) return NULL;
  return json_value->value.str;
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_VALUE_GET_DOUBLE
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
double json_value_get_double (json_value_t *json_value)
{
  if (json_value->type != JSON_DOUBLE) return 0.0F;
  return json_value->value.dbl;
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_VALUE_SET_LONG
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
long json_value_get_long (json_value_t *json_value)
{
  if (json_value->type != JSON_LONG) return 0L;
  return json_value->value.lng;
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_VALUE_SET_STRING
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
char * json_value_get_string (json_value_t *json_value)
{
  if (json_value->type != JSON_STRING) return NULL;
  return json_value->value.str;
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_VALUE_SET_BOOLEAN
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
void json_value_set_boolean (json_value_t *json_value, char const *value)
{
  json_value->type = JSON_BOOLEAN;
  json_value->value.str = (char *)json_false;
  if (strncmp(value, json_true, JSON_VALUE_LEN) == 0)
    json_value->value.str = (char *)json_true;
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_VALUE_SET_DOUBLE
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void json_value_set_double (json_value_t *json_value, double value)
{
  json_value->type = JSON_DOUBLE;
  json_value->value.dbl = value;
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_VALUE_SET_LONG
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void json_value_set_long (json_value_t *json_value, long value)
{
  json_value->type = JSON_LONG;
  json_value->value.lng = value;
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_VALUE_SET_STRING
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void json_value_set_string (json_value_t *json_value, char *value)
{
  json_value->type = JSON_STRING;
  json_value->value.str = strndup(value, JSON_VALUE_LEN);
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_VALUE_TERM
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void json_value_term (json_value_t *json_value)
{
  if (json_value->type == JSON_STRING && json_value->value.str != NULL)
  {
    free(json_value->value.str);
  }
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_WALK
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int json_walk (json_t *json, void *cb_data,
    int (*enter_cb) (char const *, json_member_t *, void *),
    int (*exit_cb) (char const *, json_member_t *, void *))
{
  for (json_pair_t *json_pair = list_begin(&json->list);
      json_pair != NULL;
      json_pair = list_next(&json->list))
  {
    if (json_traverse(json_pair->member, json_pair->name,
          cb_data, enter_cb, exit_cb) < 0) return -1;
  }

  if (exit_cb) if (exit_cb(NULL, NULL, cb_data) < 0) return -1;

  return 0;
}
//------------------------------------------------------------------------------
// CONVENIENCE ROUTINES
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_ADD_BOOLEAN_VALUE
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int json_add_boolean_value (json_t *json, char *name, char const *value)
{
  json_value_t *json_value = json_value_alloc();
  json_value_set_boolean(json_value, value);

  return json_add_value(json, name, json_value);
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_ADD_DOUBLE_VALUE
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int json_add_double_value (json_t *json, char *name, double value)
{
  json_value_t *json_value = json_value_alloc();
  json_value_set_double(json_value, value);

  return json_add_value(json, name, json_value);
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_ADD_LONG_VALUE
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int json_add_long_value (json_t *json, char *name, long value)
{
  json_value_t *json_value = json_value_alloc();
  json_value_set_long(json_value, value);

  return json_add_value(json, name, json_value);
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_ADD_STRING_VALUE
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int json_add_string_value (json_t *json, char *name, char *value)
{
  json_value_t *json_value = json_value_alloc();
  json_value_set_string(json_value, value);

  return json_add_value(json, name, json_value);
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_ARRAY_ADD_BOOLEAN_VALUE
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int json_array_add_boolean_value (json_array_t *json_array, char const *value)
{
  json_value_t *json_value = json_value_alloc();
  json_value_set_boolean(json_value, value);

  return json_array_add_value(json_array, json_value);
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_ARRAY_ADD_DOUBLE_VALUE
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int json_array_add_double_value (json_array_t *json_array, double value)
{
  json_value_t *json_value = json_value_alloc();
  json_value_set_double(json_value, value);

  return json_array_add_value(json_array, json_value);
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_ARRAY_ADD_LONG_VALUE
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int json_array_add_long_value (json_array_t *json_array, long value)
{
  json_value_t *json_value = json_value_alloc();
  json_value_set_long(json_value, value);

  return json_array_add_value(json_array, json_value);
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_ARRAY_ADD_STRING_VALUE
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int json_array_add_string_value (json_array_t *json_array, char *value)
{
  json_value_t *json_value = json_value_alloc();
  json_value_set_string(json_value, value);

  return json_array_add_value(json_array, json_value);
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_OBJECT_ADD_BOOLEAN_VALUE
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int json_object_add_boolean_value (json_object_t *json_object,
    char *name, char const *value)
{
  json_value_t *json_value = json_value_alloc();
  json_value_set_boolean(json_value, value);

  return json_object_add_value(json_object, name, json_value);
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_OBJECT_ADD_DOUBLE_VALUE
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int json_object_add_double_value (json_object_t *json_object,
    char *name, double value)
{
  json_value_t *json_value = json_value_alloc();
  json_value_set_double(json_value, value);

  return json_object_add_value(json_object, name, json_value);
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_OBJECT_ADD_LONG_VALUE
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int json_object_add_long_value (json_object_t *json_object,
    char *name, long value)
{
  json_value_t *json_value = json_value_alloc();
  json_value_set_long(json_value, value);

  return json_object_add_value(json_object, name, json_value);
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_OBJECT_ADD_STRING_VALUE
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int json_object_add_string_value (json_object_t *json_object,
    char *name, char *value)
{
  json_value_t *json_value = json_value_alloc();
  json_value_set_string(json_value, value);

  return json_object_add_value(json_object, name, json_value);
}

