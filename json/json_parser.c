#include "json_parser.h"
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// DECLARATIONS
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int json_parser_at_end (json_parser_t *);
json_token_t * json_parser_peek (json_parser_t *);
int json_parser_double (json_parser_t *, char *);
json_token_t * json_parser_identifier (json_parser_t *);
int json_parser_object (json_parser_t *, char *);
int json_parser_string (json_parser_t *, char *);
int json_parser_long (json_parser_t *, char *);
int json_parser_parent_type(json_parser_t *);
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_PARSER_ADVANCE
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
json_token_t * json_parser_advance (json_parser_t *json_parser)
{
  if (json_parser_at_end(json_parser)) return NULL;
  json_token_t *token = list_curr(&json_parser->json_scanner->list);
  (void) list_next(&json_parser->json_scanner->list);
  return token;
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_PARSER_AT_END
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int json_parser_at_end (json_parser_t *json_parser)
{
  return (json_parser_peek(json_parser)->type == JSON_CLASS_EOT);
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_PARSER_CHECK
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int json_parser_check (json_parser_t *json_parser, json_class_t type)
{
  return (json_parser_peek(json_parser)->type == type);
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_PARSER_CONSUME
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
json_token_t * json_parser_consume (json_parser_t *json_parser,
    json_class_t expected)
{
  if (json_parser_check(json_parser, expected)) {
    return json_parser_advance(json_parser);
  }
  return NULL;
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_PARSER_ERROR
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int json_parser_error (json_parser_t *json_parser)
{
  json_token_t *token;
  if ((token = list_curr(&json_parser->json_scanner->list)) == NULL)
    return -1;

  if (token->type == JSON_CLASS_EOT)
  {
    puts("ERROR: unexpected end of input.\n");
  }
  else
  {
    printf("ERROR: near offset: %lu lexeme: %s literal: %s\n",
        token->offset, token->lexeme, token->literal);
  }

  return -1;
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_PARSER_MATCH
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int json_parser_match (json_parser_t *json_parser, json_class_t type)
{
  if (json_parser_check(json_parser, type))
  {
    (void) json_parser_advance(json_parser);

    return 1;
  }
  return 0;
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_PARSER_PEEK
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
json_token_t * json_parser_peek (json_parser_t *json_parser)
{
  return (json_token_t *)list_curr(&json_parser->json_scanner->list);
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_PARSER_PEEK_NEXT
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
json_token_t * json_parser_peek_next (json_parser_t *json_parser)
{
  return (json_token_t *)list_succ(&json_parser->json_scanner->list);
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_PARSER_ARRAY_BEGIN
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int json_parser_array_begin (json_parser_t *json_parser, char *name)
{
  json_array_t *json_array = json_array_alloc();
  if (json_array_init(json_array) < 0) return -1;

  if (lifo_empty(&json_parser->lifo))
  {
    if (json_add_array(json_parser->json, name, json_array) < 0) return -1;
  }
  else
  {
    json_list_t *json_list = lifo_top(&json_parser->lifo);
    if (json_list->type == JSON_ARRAY)
    {
      if (json_array_add_array(json_list, json_array) < 0) return -1;
    }
    else if (json_list->type == JSON_OBJECT)
    {
      if (json_object_add_array(json_list, name, json_array) < 0) return -1;
    }
    else return -1;
  }

  if (lifo_push(&json_parser->lifo, json_array) == NULL) return -1;

  return 0;
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_PARSER_ARRAY_END
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void json_parser_array_end(json_parser_t *json_parser)
{
  (void) lifo_pop(&json_parser->lifo);
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_PARSER_OBJECT_BEGIN
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int json_parser_object_begin (json_parser_t *json_parser, char *name)
{
  json_object_t *json_object = json_object_alloc();
  if (json_object_init(json_object) < 0) return -1;

  if (lifo_empty(&json_parser->lifo))
  {
    if (json_add_object(json_parser->json, name, json_object) < 0) return -1;
  }
  else
  {
    json_list_t *json_list = lifo_top(&json_parser->lifo);
    if (json_list->type == JSON_ARRAY)
    {
      if (json_array_add_object(json_list, json_object) < 0) return -1;
    }
    else if (json_list->type == JSON_OBJECT)
    {
      if (json_object_add_object(json_list, name, json_object) < 0) return -1;
    }
    else return -1;
  }

  if (lifo_push(&json_parser->lifo, json_object) == NULL) return -1;

  return 0;
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_PARSER_object_END
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void json_parser_object_end(json_parser_t *json_parser)
{
  json_parser_array_end(json_parser);
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_PARSER_ARRAY
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int json_parser_array (json_parser_t *json_parser, char *name)
{
  if (json_parser_string(json_parser, name) == 0) return 0;

  if (! json_parser_match(json_parser, JSON_CLASS_LEFT_BRACKET)) return -1;

  if (json_parser_array_begin(json_parser, name) < 0) return -1;

  while (! json_parser_at_end(json_parser) &&
      ! json_parser_check(json_parser, JSON_CLASS_RIGHT_BRACKET))
  {
    if (json_parser_object(json_parser, NULL) < 0) return -1;

    if (! json_parser_match(json_parser, JSON_CLASS_COMMA)) break;
  }

  if (! json_parser_match(json_parser, JSON_CLASS_RIGHT_BRACKET)) return -1;

  json_parser_array_end(json_parser);

  return 0;
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_PARSER_BOOLEAN
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int json_parser_boolean (json_parser_t *json_parser, char *name)
{
  json_token_t *token = NULL;
  if ((token = json_parser_consume(json_parser, JSON_CLASS_BOOLEAN)) == NULL)
    return -1;

  switch (json_parser_parent_type(json_parser))
  {
    case JSON_NULL:
      return json_add_boolean_value(json_parser->json, name, token->literal);
    case JSON_ARRAY:
    {
      json_array_t *json_array = lifo_top(&json_parser->lifo);
      return json_array_add_boolean_value(json_array, token->literal);
    }
    case JSON_OBJECT:
    {
      json_object_t *json_object = lifo_top(&json_parser->lifo);
      return json_object_add_boolean_value(json_object, name, token->literal);
    }
    default: return -1;
  }
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_PARSER_DO
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int json_parser_do (json_parser_t *json_parser)
{
  if (! json_parser_match(json_parser, JSON_CLASS_LEFT_BRACE))
    return json_parser_error(json_parser);

  while (! json_parser_at_end(json_parser) &&
      json_parser_check(json_parser, JSON_CLASS_IDENTIFIER))
  {
    json_token_t *ident = NULL;
    if ((ident = json_parser_identifier(json_parser)) == NULL)
      return json_parser_error(json_parser);

    if (json_parser_object(json_parser, ident->lexeme) < 0)
      return json_parser_error(json_parser);

    if (! json_parser_match(json_parser, JSON_CLASS_COMMA)) break;
  }

  if (! json_parser_match(json_parser, JSON_CLASS_RIGHT_BRACE))
    return json_parser_error(json_parser);

  return 0;
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_PARSER_DOUBLE
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int json_parser_double (json_parser_t *json_parser, char *name)
{
  if (json_parser_long(json_parser, name) == 0) return 0;

  json_token_t *value = NULL;
  if ((value = json_parser_consume(json_parser, JSON_CLASS_DOUBLE)) == NULL)
    return -1;

  switch (json_parser_parent_type(json_parser))
  {
    case JSON_NULL:
      return json_add_double_value(json_parser->json, name, value->numeric.d);
    case JSON_ARRAY:
    {
      json_array_t *json_array = lifo_top(&json_parser->lifo);
      return json_array_add_double_value(json_array, value->numeric.d);
    }
    case JSON_OBJECT:
    {
      json_object_t *json_object = lifo_top(&json_parser->lifo);
      return json_object_add_double_value(json_object, name, value->numeric.d);
    }
    default: return -1;
  }
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_PARSER_IDENTIFIER
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
json_token_t * json_parser_identifier (json_parser_t *json_parser)
{
  json_token_t *ident = NULL;

  if ((ident = json_parser_consume(json_parser, JSON_CLASS_IDENTIFIER)) == NULL)
    return NULL;

  if (! json_parser_match(json_parser, JSON_CLASS_COLON)) return NULL;

  return ident;
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_PARSER_INIT
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int json_parser_init (json_parser_t *json_parser, json_scanner_t *json_scan)
{
  json_parser->json = json_alloc();
  if (json_init(json_parser->json) < 0) return -1;
  json_parser->json_scanner = json_scan;
  (void) list_begin(&json_parser->json_scanner->list);
  if (lifo_init(&json_parser->lifo, 64) < 0) return -1;
  return 0;
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_PARSER_LONG
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int json_parser_long (json_parser_t *json_parser, char *name)
{
  if (json_parser_boolean(json_parser, name) == 0) return 0;

  json_token_t *value;
  if ((value = json_parser_consume(json_parser, JSON_CLASS_LONG)) == NULL)
    return -1;

  switch (json_parser_parent_type(json_parser))
  {
    case JSON_NULL:
      return json_add_long_value(json_parser->json, name, value->numeric.i);
    case JSON_ARRAY:
    {
      json_array_t *json_array = lifo_top(&json_parser->lifo);
      return json_array_add_long_value(json_array, value->numeric.i);
    }
    case JSON_OBJECT:
    {
      json_object_t *json_object = lifo_top(&json_parser->lifo);
      return json_object_add_long_value(json_object, name, value->numeric.i);
    }
    default: return -1;
  }
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_PARSER_OBJECT
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int json_parser_object (json_parser_t *json_parser, char *name)
{
  if (json_parser_array(json_parser, name) == 0) return 0;

  if (! json_parser_match(json_parser, JSON_CLASS_LEFT_BRACE)) return -1;

  json_parser_object_begin(json_parser, name);

  while (! json_parser_at_end(json_parser) &&
      ! json_parser_check(json_parser, JSON_CLASS_RIGHT_BRACE))
  {
    json_token_t *ident;
    if ((ident = json_parser_identifier(json_parser)) == NULL) return -1;

    if (json_parser_object(json_parser, ident->lexeme) < 0) return -1;

    if (! json_parser_match(json_parser, JSON_CLASS_COMMA)) break;
  }

  if (! json_parser_match(json_parser, JSON_CLASS_RIGHT_BRACE)) return -1;

  json_parser_object_end(json_parser);

  return 0;
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_PARSER_PARENT_TYPE
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int json_parser_parent_type(json_parser_t *json_parser)
{
  if (lifo_empty(&json_parser->lifo)) return JSON_NULL;

  return ((json_list_t *)lifo_top(&json_parser->lifo))->type;
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_PARSER_STRING
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int json_parser_string (json_parser_t *json_parser, char *name)
{
  if (json_parser_double(json_parser, name) == 0) return 0;

  json_token_t *value;
  if ((value = json_parser_consume(json_parser, JSON_CLASS_STRING)) == NULL)
    return -1;

  switch (json_parser_parent_type(json_parser))
  {
    case JSON_NULL:
      return json_add_string_value(json_parser->json, name, value->literal);
    case JSON_ARRAY:
    {
      json_array_t *json_array = lifo_top(&json_parser->lifo);
      return json_array_add_string_value(json_array, value->literal);
    }
    case JSON_OBJECT:
    {
      json_object_t *json_object = lifo_top(&json_parser->lifo);
      return json_object_add_string_value(json_object, name, value->literal);
    }
    default: return -1;
  }
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_PARSER_TERM
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void json_parser_term (json_parser_t *json_parser)
{
  lifo_term(&json_parser->lifo);
}

