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
#include "json_writer.h"
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// DECLARATIONS
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int json_writer_enter_cb (char const *, json_member_t *, void *);
int json_writer_exit_cb (char const *, json_member_t *, void *);
int json_writer_get_previous_char (json_writer_t *);
int json_writer_write_array(json_writer_t *, char const *, json_array_t *);
int json_writer_write_char (json_writer_t *, char const *);
int json_writer_write_name (json_writer_t *, char const *);
int json_writer_write_object(json_writer_t *, char const *, json_object_t *);
int json_writer_write_value(json_writer_t *, char const *, json_value_t *);
int json_writer_write_varchar (json_writer_t *, char const *);
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_WRITER_DO
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int json_writer_do (json_writer_t *json_writer)
{
  if (json_writer_write_char(json_writer, &o_cr_brace) < 0) return -1;

  if (json_walk(json_writer->json, json_writer,
      json_writer_enter_cb, json_writer_exit_cb) < 0) return -1;

  if (json_writer_write_char(json_writer, &c_cr_brace) < 0) return -1;

  return 0;
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_WRITER_ENTER_CB
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int json_writer_enter_cb (char const *name,
    json_member_t *member, void *cb_data)
{
  json_writer_t *json_writer = cb_data;

  if (json_writer_get_previous_char(json_writer) != o_sq_bracket
      && json_writer_get_previous_char(json_writer) != o_cr_brace)
  {
     if (json_writer_write_char(json_writer, &comma) < 0) return -1;
  }

  switch (json_member_type(member))
  {
		case JSON_BOOLEAN:
		case JSON_DOUBLE:
		case JSON_LONG:
		case JSON_STRING:
    {
      return json_writer_write_value(json_writer, name, member);
    }
    case JSON_ARRAY:
    {
      return json_writer_write_array(json_writer, name, member);
    }
    case JSON_OBJECT:
    {
      return json_writer_write_object(json_writer, name, member);
    }
    default: return -1;
  }
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_WRITER_EXIT_CB
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int json_writer_exit_cb (char const *name, json_member_t *member, void *cb_data)
{
  if (member == NULL) return 0;

  json_writer_t *json_writer = cb_data;

  if (json_member_type(member) == JSON_ARRAY)
  {
    return json_writer_write_char(json_writer, &c_sq_bracket);
  }
  else if (json_member_type(member) == JSON_OBJECT)
  {
    return json_writer_write_char(json_writer, &c_cr_brace);
  }
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_WRITER_GET_PREVIOUS_CHAR
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int json_writer_get_previous_char (json_writer_t *json_writer)
{
  if (fseek(json_writer->file, -1, SEEK_CUR) < 0) return -1;

  char ch;
  return (((ch = fgetc(json_writer->file)) == EOF) ? -1 : ch);
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_WRITER_INIT
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int json_writer_init (json_writer_t *json_writer, json_t *json,
    char const *path)
{
  int flags = (O_CREAT | O_TRUNC | O_RDWR);
  mode_t mode = (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
  int fd;
  if ((fd = open(path, flags, mode)) < 0) return -1;

  char *fmode = "w+";
  if ((json_writer->file = fdopen(fd, fmode)) == NULL) return -1;

  json_writer->json = json;

  return 0;
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_WRITER_TERM
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void json_writer_term (json_writer_t *json_writer) {
  (void) fflush(json_writer->file);
  (void) fclose(json_writer->file);
  (void) memset(json_writer, 0, sizeof(json_writer_t));
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_WRITER_WRITE_ARRAY
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int json_writer_write_array(json_writer_t *json_writer, char const *name,
    json_array_t *array)
{
  if (json_writer_write_name(json_writer, name) < 0) return -1;
  if (json_writer_write_char(json_writer, &o_sq_bracket) < 0) return -1;
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_WRITER_WRITE_BOOLEAN
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int json_writer_write_boolean (json_writer_t *json_writer, char const *name,
    char const *value)
{
  if (json_writer_write_name(json_writer, name) < 0) return -1;
  if (json_writer_write_varchar(json_writer, value) < 0) return -1;
  return 0;
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_WRITER_WRITE_CHAR
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int json_writer_write_char (json_writer_t *json_writer, char const *ch)
{
  return ((fputc(*ch, json_writer->file) == EOF) ? -1 : 0);
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_WRITER_WRITE_DOUBLE
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int json_writer_write_double (json_writer_t *json_writer, char const *name,
    double value)
{
  if (json_writer_write_name(json_writer, name) < 0) return -1;

  char value_as_text [JSON_VALUE_LEN + 1];
  (void) snprintf(value_as_text, JSON_VALUE_LEN, "%g", value);

  if (json_writer_write_varchar(json_writer, value_as_text) < 0) return -1;

  return 0;
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_WRITER_WRITE_LONG
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int json_writer_write_long (json_writer_t *json_writer, char const * name,
    long value)
{
  if (json_writer_write_name(json_writer, name) < 0) return -1;

  char value_as_text [JSON_VALUE_LEN + 1];
  (void) snprintf(value_as_text, JSON_VALUE_LEN, "%ld", value);

  if (json_writer_write_varchar(json_writer, value_as_text) < 0) return -1;

  return 0;
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_WRITER_WRITE_NAME
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int json_writer_write_name (json_writer_t *json_writer, char const *name)
{
  if (name == NULL) return 0;

  if (json_writer_write_char(json_writer, &d_quote) < 0) return -1;
  if (json_writer_write_varchar(json_writer, name) < 0) return -1;
  if (json_writer_write_char(json_writer, &d_quote) < 0) return -1;
  if (json_writer_write_char(json_writer, &colon) < 0) return -1;

  return 0;
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_WRITER_WRITE_OBJECT
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int json_writer_write_object(json_writer_t *json_writer, char const *name,
    json_object_t *object)
{
  if (json_writer_write_name(json_writer, name) < 0) return -1;
  if (json_writer_write_char(json_writer, &o_cr_brace) < 0) return -1;
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_WRITER_WRITE_STRING
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int json_writer_write_string(json_writer_t *json_writer, char const *name,
    char const *value)
{
  if (json_writer_write_name(json_writer, name) < 0) return -1;
  if (json_writer_write_char(json_writer, &d_quote) < 0) return -1;
  if (json_writer_write_varchar(json_writer, value) < 0) return -1;
  if (json_writer_write_char(json_writer, &d_quote) < 0) return -1;

  return 0;
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_WRITER_WRITE_VALUE
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int json_writer_write_value(json_writer_t *json_writer, char const *name,
    json_value_t *value)
{
  switch (value->type)
  {
		case JSON_BOOLEAN:
    {
      return json_writer_write_boolean(json_writer, name, value->value.str);
    }
		case JSON_DOUBLE:
    {
      return json_writer_write_double(json_writer, name, value->value.dbl);
    }
    case JSON_LONG:
    {
      return json_writer_write_long(json_writer, name, value->value.lng);
    }
		case JSON_STRING:
    {
      return json_writer_write_string(json_writer, name, value->value.str);
    }
    default: return -1;
  }
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_WRITER_WRITE_VARCHAR
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int json_writer_write_varchar (json_writer_t *json_writer, char const *vc)
{
  return ((fputs(vc, json_writer->file) == EOF) ? -1 : 0);
}

