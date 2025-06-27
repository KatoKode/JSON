#include "json_scanner.h"
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// DECLARATIONS
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int json_scanner_error (json_scanner_t *);
int json_scanner_load (json_scanner_t *, char const *);
char json_scanner_peek (json_scanner_t *);
char json_scanner_peek_next (json_scanner_t *);
void json_scanner_print (json_scanner_t *);
int json_scanner_token (json_scanner_t *);
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_SCANNER_ADD_BOOLEAN
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int json_scanner_add_boolean (json_scanner_t *json_scanner) {
  json_token_t tok;

  memset(&tok, 0, sizeof(json_token_t));
  tok.type    = JSON_CLASS_BOOLEAN;
  tok.offset  = json_scanner->start + 1;
  tok.length  = (json_scanner->current) - (json_scanner->start);

  (void) strncpy(tok.literal, &json_scanner->source [ json_scanner->start ],
      (tok.length < JSON_LITERAL_SIZE) ? tok.length : JSON_LITERAL_SIZE);

  return list_add(&json_scanner->list, &tok);
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_SCANNER_ADD_DOUBLE
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int json_scanner_add_double (json_scanner_t *json_scanner)
{
  json_token_t tok;

  memset(&tok, 0, sizeof(json_token_t));
  tok.type    = JSON_CLASS_DOUBLE;
  tok.offset  = json_scanner->start + 1;
  tok.length  = json_scanner->current - json_scanner->start;

  {
    char *str = substring(json_scanner->source,
        json_scanner->start, json_scanner->current);

    tok.numeric.d = strtod(str, NULL);

    (void) strncpy(tok.literal, str, JSON_LITERAL_SIZE);

    free(str);
  }

  return list_add(&json_scanner->list, &tok);
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_SCANNER_ADD_IDENTIFIER
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int json_scanner_add_identifier (json_scanner_t *json_scanner)
{
  json_token_t tok;

  memset(&tok, 0, sizeof(json_token_t));
  tok.type    = JSON_CLASS_IDENTIFIER;
  tok.offset  = json_scanner->start + 1;
  // length of string minus quotation marks
  tok.length  = (json_scanner->current - 1) - (json_scanner->start + 1);

  (void) strncpy(tok.lexeme, &json_scanner->source [ json_scanner->start + 1 ],
      (tok.length < JSON_LITERAL_SIZE) ? tok.length : JSON_LITERAL_SIZE);

  return list_add(&json_scanner->list, &tok);
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_SCANNER_ADD_STRING
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int json_scanner_add_string (json_scanner_t *json_scanner)
{
  json_token_t tok;

  memset(&tok, 0, sizeof(json_token_t));
  tok.type    = JSON_CLASS_STRING;
  tok.offset  = json_scanner->start + 1;
  // length of string minus quotation marks
  tok.length  = (json_scanner->current - 1) - (json_scanner->start + 1);

  (void) strncpy(tok.literal, &json_scanner->source [ json_scanner->start + 1 ],
      (tok.length < JSON_LITERAL_SIZE) ? tok.length : JSON_LITERAL_SIZE);

  return list_add(&json_scanner->list, &tok);
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_SCANNER_ADD_TYPE
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int json_scanner_add_type (json_scanner_t *json_scanner, size_t type)
{
  json_token_t tok;

  memset(&tok, 0, sizeof(json_token_t));
  tok.type    = type;
  tok.offset  = json_scanner->start;
  tok.length  = json_scanner->current - json_scanner->start;

  return list_add(&json_scanner->list, &tok);
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_SCANNER_ADD_LONG
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int json_scanner_add_long (json_scanner_t *json_scanner)
{
  json_token_t tok;

  memset(&tok, 0, sizeof(json_token_t));
  tok.type    = JSON_CLASS_LONG;
  tok.offset  = json_scanner->start + 1;
  tok.length  = json_scanner->current - json_scanner->start;

  {
    char *str = substring(json_scanner->source,
        json_scanner->start, json_scanner->current);

    tok.numeric.i = strtol(str, NULL, 10);

    (void) strncpy(tok.literal, str, JSON_LITERAL_SIZE);

    free(str);
  }

  return list_add(&json_scanner->list, &tok);
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_SCANNER_ADVANCE 
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
char json_scanner_advance (json_scanner_t *json_scanner)
{
  return json_scanner->source[json_scanner->current++];
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_SCANNER_AT_END
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int json_scanner_at_end (json_scanner_t *json_scanner)
{
  return json_scanner->current >= json_scanner->length;
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_SCANNER_BOOLEAN
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int json_scanner_boolean (json_scanner_t *json_scanner)
{
  while (! json_scanner_at_end(json_scanner)
      && json_scanner_peek(json_scanner) != ','
      && json_scanner_peek(json_scanner) != '}'
      && json_scanner_peek(json_scanner) != ']')
  {
    (void) json_scanner_advance(json_scanner);
  }

  if (json_scanner_at_end(json_scanner)) return -1;

  return json_scanner_add_boolean(json_scanner);
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_SCANNER_DO
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int json_scanner_do (json_scanner_t *json_scanner)
{
  while (! json_scanner_at_end(json_scanner))
  {
    json_scanner->start = json_scanner->current;

    if (json_scanner_token(json_scanner) < 0)
    {
      return json_scanner_error(json_scanner);
    }
  }

  json_token_t tok;
  memset(&tok, 0, sizeof(json_token_t));
  tok.type = JSON_CLASS_EOT;

  return list_add(&json_scanner->list, &tok);
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_SCANNER_ERROR
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int json_scanner_error (json_scanner_t *json_scanner)
{
  json_scanner_print(json_scanner);
  return -1;
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_SCANNER_INIT
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int json_scanner_init (json_scanner_t *json_scanner, char const *path)
{
  memset(json_scanner, 0, sizeof(json_scanner_t));
  json_scanner->start = 0;
  json_scanner->current = 0;
  if (json_scanner_load(json_scanner, path) < 0) return -1;
  return list_init(&json_scanner->list, sizeof(json_token_t));
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_SCANNER_LOAD
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int json_scanner_load (json_scanner_t *json_scanner, char const *path)
{
  int flags = (O_RDONLY | O_RSYNC);
  int fd = -1;
  if ((fd = open(path, flags)) < 0) return -1;

  struct stat fs;
  if (fstat(fd, &fs) < 0) goto failure;

  if ((json_scanner->source = calloc(1, (fs.st_size + 1L))) == NULL)
    goto failure;

  if (pread(fd, (char *)json_scanner->source, fs.st_size, 0L) < 0)
    goto failure;

  json_scanner->length = fs.st_size;

  (void) close(fd);

  return 0;

failure:

  (void) close(fd);

  return -1;
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_SCANNER_NUMBER
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int json_scanner_number (json_scanner_t *json_scanner)
{
  while (isdigit(json_scanner_peek(json_scanner)))
    (void) json_scanner_advance(json_scanner);

  if (json_scanner_peek(json_scanner) == '.')
  {
    (void) json_scanner_advance(json_scanner);

    while (isdigit(json_scanner_peek(json_scanner)))
      (void) json_scanner_advance(json_scanner);

    if (json_scanner_peek(json_scanner) == 'e'
        && json_scanner_peek_next(json_scanner) == '+')
    {
      (void) json_scanner_advance(json_scanner);
      (void) json_scanner_advance(json_scanner);

      while (isdigit(json_scanner_peek(json_scanner)))
        (void) json_scanner_advance(json_scanner);
    }

    return json_scanner_add_double(json_scanner);
  }
  else
  {
    return json_scanner_add_long(json_scanner);
  }
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_SCANNER_PEEK
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
char json_scanner_peek (json_scanner_t *json_scanner)
{
  if (json_scanner_at_end(json_scanner)) return '\0';
  return json_scanner->source [ json_scanner->current ];
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_SCANNER_PEEK_NEXT
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
char json_scanner_peek_next (json_scanner_t *json_scanner)
{
  if (json_scanner->current + 1 >= json_scanner->length) return '\0';
  return json_scanner->source [ json_scanner->current + 1 ];
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_SCANNER_PRINT
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void json_scanner_print (json_scanner_t *json_scanner)
{
  printf("ERROR: start: %lu current: %lu length: %lu near: \'%c\'\n",
      json_scanner->start, json_scanner->current,
      (json_scanner->current - json_scanner->start),
      json_scanner->source [ json_scanner->current - 1L ]);
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_SCANNER_STRING
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int json_scanner_string (json_scanner_t *json_scanner)
{
  while (! json_scanner_at_end(json_scanner)
      && json_scanner_peek(json_scanner) != '\"')
    (void) json_scanner_advance(json_scanner);

  if (json_scanner_at_end(json_scanner)) return -1;

  // skip the closing double quote (")
  json_scanner_advance(json_scanner);

  if (json_scanner_peek(json_scanner) == ':')
    return json_scanner_add_identifier(json_scanner);

  return json_scanner_add_string(json_scanner);
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_SCANNER_TOKEN
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int json_scanner_token (json_scanner_t *json_scanner)
{
  char c = json_scanner_advance(json_scanner);

  switch (c)
  {
    case '\"':
      return json_scanner_string(json_scanner);
    case ',':
      return json_scanner_add_type(json_scanner, JSON_CLASS_COMMA);
    case '-':
      return json_scanner_number(json_scanner);
    case ':':
      return json_scanner_add_type(json_scanner, JSON_CLASS_COLON);
    case '[':
      return json_scanner_add_type(json_scanner, JSON_CLASS_LEFT_BRACKET);
    case ']':
      return json_scanner_add_type(json_scanner, JSON_CLASS_RIGHT_BRACKET);
    case '{':
      return json_scanner_add_type(json_scanner, JSON_CLASS_LEFT_BRACE);
    case '}':
      return json_scanner_add_type(json_scanner, JSON_CLASS_RIGHT_BRACE);
    case '\t': case '\n': case '\r': case ' ':
       return 0;  // ignore whitespace
    default:
    {
      if (isdigit(c))
        return json_scanner_number(json_scanner);
      else if (isalpha(c))
        return json_scanner_boolean(json_scanner);
    }
  }
  return -1;  // ERROR
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_SCANNER_TERM
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void json_scanner_term (json_scanner_t *json_scanner) {
    list_term(&json_scanner->list);
    free((void *)json_scanner->source);
    memset(json_scanner, 0, sizeof(json_scanner_t));
}

