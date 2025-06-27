


Just Another Armchair Programmer

JSON Library Written in C with Assembly Language Support Libraries

by Jerry McIntosh

---

## JSON Structure
A JSON structure is the main structure and represents the top of the JSON Tree.  A JSON structure can hold Objects, Arrays, and Values.

---

```c
int json_add_array (json_t *json, char *name, json_array_t *array);
```

`json_add_array` adds a named Array to the top level of a JSON Tree.  Returns 0 for success or -1 for failure.

---

```c
int json_add_object (json_t *json, char *name, json_object_t *object);
```

`json_add_object()` adds a named JSON Object to the top level of a JSON Tree.  Returns 0 for success or -1 for failure.

---

```c
int json_add_value (json_t *json, char  *name, json_value_t *value);
```

`json_add_value()` adds a named Value to the top level of a JSON Tree.  Returns 0 for success or -1 for failure.

---

```c
void * json_alloc();
```

`json_alloc()` allocates a JSON structure on the Heap.  If successful, returns a pointer to a JSON Structure on the Heap or `NULL` upon failure.

---

```c
void json_free(json_t *json);
```

`json_free()` free memory allocated for a JSON structure on the Heap.

---

```c
int json_init (json_t *json);
```

`json_init()` initializes a JSON structure.  Returns 0 for success or -1 for failure.

---

```c
json_member_t * json_search (json_t *json, char *name);
```

`json_search()` searches the top of the JSON Tree for a member with a name matching `name`.  If a match is found a pointer to the corresponding member is returned, otherwise, `NULL` is returned.

---

```c
void json_term (json_t *json);
```

`json_term()` terminates a JSON structure.  Call `json_term()` prior to calling `json_free()`.

---

## JSON Array Structure
A JSON Array can hold unnamed JSON Objects, JSON Arrays, and JSON Values.  Each member of a JSON Array is stored in a JSON Node.  A JSON Node can hold one of the following: a JSON Object, a JSON Array, or a JSON Value.

---

```c
int json_array_add_array (json_array_t *array, json_array_t *new_array);
```

`json_array_add_array()` adds a JSON Array to a JSON Array.  Returns 0 for success or -1 for failure.

---

```c
int json_array_add_object (json_array_t *array, json_object_t *object);
```

`json_array_add_object()` adds a JSON Object to a JSON Array.  Returns 0 for success or -1 for failure.

---

```c
int json_array_add_value (json_array_t *array, json_value_t *value);
```

`json_array_add_value()` adds a Value to a JSON Array.  Returns 0 for success or -1 for failure.

---

```c
void * json_array_alloc();
```

`json_array_alloc()` allocates a JSON Array on the Heap.  If successful, returns a pointer to a JSON Array Structure on the Heap or `NULL` upon failure.

---

```c
json_member_t * json_array_begin (json_array_t *array);
```

`json_array_begin()` returns the first member of a JSON Array or `NULL` should the JSON Array be empty.  `json_array_begin()` must be called once prior to the first call to `json_array_next()` to initiate the iteration through a JSON Array.

---

```c
void json_array_free (json_array_t *array);
```

`json_array_free()` free memory allocated for a JSON Array on the Heap.

---

```c
json_member_t * json_array_get_member (json_array_t *array, size_t index);
```

`json_array_get_member()` returns a pointer to the member at `index` of a JSON Array or `NULL` should `index` be out-of-bounds.

---

```c
int json_array_init (json_array_t *);
```

`json_array_init()` initializes a JSON Array.  A JSON Array must be initialized before use.

---

```c
json_member_t * json_array_next (json_array_t *array);
```

`json_array_next()` returns a pointer to the next member of a JSON Array or `NULL` when the end of a JSON Array has been reached.  **NOTE**: `json_array_begin()` must be called once prior to the first call to `json_array_next()` to initiate the iteration through a JSON Array.

---

```c
void json_array_term (json_array_t *array);
```

`json_array_term()` terminates a JSON Array.  Call `json_array_term()` prior to calling `json_array_free()`.

---

## Object Structure
A JSON Object can hold named JSON Objects, named JSON Arrays, and named JSON Values.  Each item in a JSON Object is a member of a key-value JSON Pair.  A key-value JSON Pair can hold one of the following: a JSON Object, a JSON Array, or a JSON Value.

---

```c
int json_object_add_array (json_object_t *object, char *name, json_array_t *array);
```

`json_object_add_array()` adds a named JSON Array to a JSON Object.  Returns 0 for success or -1 for failure.

---

```c
int json_object_add_object (json_object_t *object, char *name, json_object_t *new_object);
```

`json_object_add_object()` adds a named JSON Object to a JSON Object.  Returns 0 for success or -1 for failure.

---

```c
int json_object_add_value (json_object_t *object, char *name, json_value_t *value);
```

`json_object_add_value()` adds a named JSON Value to a JSON Object.  Returns 0 for success or -1 for failure.

---

```c
void * json_object_alloc();
```

`json_object_alloc()` allocate memory on the Heap for a JSON Object.

---

```c
void json_object_free(json_object_t *object);
```

`json_object_free()` free memory allocated for a JSON Object on the Heap.

---

```c
int json_object_init (json_object_t *object);
```

`json_object_init()` initializes a JSON Object.  A JSON Object must be initialized before use.  Returns 0 for success or -1 for failure.

---

```c
json_member_t * json_object_search (json_object_t *object, char *name);
```

`json_object_search()` searches a JSON Object for a member with a name matching `name`.  If a match is found a pointer to the corresponding member is returned, otherwise, `NULL` is returned.

---

```c
void json_object_term (json_object_t *object);
```

`json_object_term()` terminates a Node.  Call `json_object_term()` prior to calling `json_object_free()`.

---

## JSON Value Structure
A Value structure can hold one of the following primary values: a Boolean, a Double, a Long, or a String.

---

```c
void * json_value_alloc();
```

`json_value_alloc()` allocate memory on the Heap for a Value.

---

```c
void json_value_free(json_value_t *value);
```

`json_value_free()` free memory allocated for a Value on the Heap.

---

```c
char const * json_value_get_boolean (json_value_t *value);
```

`json_value_get_boolean()` returns the Boolean value stored in a Value.  If Value is empty or contains something other than a Boolean the behavior is undefined.

---

```c
double json_value_get_double (json_value_t *value);
```

`json_value_get_double()` retrieves the Double value stored in a Value.  If Value is empty or contains something other than a Double the behavior is undefined.

---

```c
long json_value_get_long (json_value_t *value);
```

`json_value_get_long()` retrieves the Long value stored in a Value.  If Value is empty or contains something other than a Long the behavior is undefined.

---

```c
char * json_value_get_string (json_value_t *value);
```

`json_value_get_string()` retrieves the String value stored in a Value.  If Value is empty or contains something other than a String the behavior is undefined.

---

```c
void json_value_set_boolean (json_value_t *value, char const *new_value);
```

`json_value_set_boolean()` sets the type and value of a Value to a Boolean value.

---

```c
void json_value_set_double (json_value_t *value, double new_value);
```

`json_value_set_double()` sets the type and value of a Value to a Double value.

---

```c
void json_value_set_long (json_value_t *value, long new_value);
```

`json_value_set_long()` sets the type and value of a Value to a Long value.

---

```c
void json_value_set_string (json_value_t *value, char *new_value);
```

`json_value_set_string()` sets the type and value of a Value to a String value.

---

```c
void json_value_term (json_value_t *value);
```

`json_value_term()` terminates a Value.  Call `json_value_term()` prior to calling `json_value_free()`

---

## JSON Tree Walk Function

---

```c
int json_walk (json_t *json, void *cb_data,
    int (*enter_cb) (char const *, json_member_t *, void *),
    int (*exit_cb) (char const *, json_member_t *, void *));
```
**NOTE**: `NULL` can be passed for `exit_cb`.

`json_walk()` walks the JSON Tree calling `enter_cb` and `exit_cb` at each member.  Parameter `cb_data` is passed to both callback functions as the last parameter.

`cb_data` is for user-defined data.  `cb_data` is passed to both `enter_cb` and `exit_cb` as the last paramenter.

`enter_cb()` is a user-defined callback function that is called at each member.  The parameters are as follows:

+ pointer to a name (key) associated with the Node.  Could be `NULL`.
+ pointer to the current member.
+ pointer to user-defined `cb_data` parameter.

`exit_cb()` is a user-defined callback function that is called just prior to leaving the current member.  `NULL` can be passed in place of `exit_cb`.  The parameters are as follows:

+ pointer to a name (key) associated with the member.  Could be `NULL`.
+ pointer to the current member.
+ pointer to user-defined `cb_data` parameter.

Returns 0 for success or -1 upon failure.

---

## Convenience Functions
**NOTE**: All the Convenience Functions return 0 for success or -1 for failure.

---

```c
int json_add_boolean_value (json_t *json, char *name, char const *value);
```

`json_add_boolean_value()` adds a Boolean value to the upper-most level of a JSON Tree.

---

```c
int json_add_double_value (json_t *json, char *name, double value);
```

`json_add_double_value()` adds a Double value to the upper-most level of a JSON Tree.

---

```c
int json_add_long_value (json_t *json, char *name, long value);
```

`json_add_long_value()` adds a Long value to the upper-most level of a JSON Tree.

---

```c
int json_add_string_value (json_t *json, char *name, char *value);
```

`json_add_string_value()` adds a String value to the upper-most level of a JSON Tree.

---

```c
int json_array_add_boolean_value (json_array_t *array, char const *value);
```

`json_array_add_boolean_value()` adds a Boolean value to a JSON Array.

---

```c
int json_array_add_double_value (json_array_t *array, double value);
```

`json_array_add_double_value()` adds a Double value to a JSON Array.

---

```c
int json_array_add_long_value (json_array_t *array, long value);
```

`json_array_add_long_value()` adds a Long value to a JSON Array.

---

```c
int json_array_add_string_value (json_array_t *array, char *value);
```

`json_array_add_string_value()` adds a String value to a JSON Array.

---

```c
int json_object_add_boolean_value (json_object_t *object, char *name, char const *value);
```

`json_object_add_boolean_value()` adds a Boolean value to a JSON Object.

---

```c
int json_object_add_double_value (json_object_t *object, char *name, double value);
```

`json_object_add_double_value()` adds a Double value to a JSON Object.

---

```c
int json_object_add_long_value (json_object_t *object, char *name, long value);
```

`json_object_add_long_value()` adds a Long value to a JSON Object.

---

```c
int json_object_add_string_value (json_object_t *object, char *name, char *value);
```

`json_object_add_string_value()` adds a String value to a JSON Object.
## JSON Scanner
The JSON Scanner scans a JSON File and produces a list of JSON Tokens.

---

```c
void * json_scanner_alloc();
```

`json_scanner_alloc()` allocates a JSON Scanner structure on the Heap.

---

```c
int json_scanner_do (json_scanner_t *scanner);
```

`json_scanner_do()` scans a JSON File and produces a list of JSON Tokens.  Returns 0 upon success or -1 for failure.

---

```c
void json_scanner_free(json_scanner_t *scanner);
```

`json_scanner_free()` frees memory allocated for a JSON Scanner on the Heap.

---

```c
int json_scanner_init (json_scanner_t *scanner, char const *path);
```

`json_scanner_init()` initializes the JSON Scanner structure and buffers the JSON file pointed to by `path`.  Returns 0 upon success or -1 for failure.

---

```c
void json_scanner_term(json_scanner_t *scanner);
```

`json_scanner_term()` terminates a JSON Scanner.  Call `json_scanner_term()` prior to calling `json_scanner_free()`.
## JSON Parser
The JSON Parser parses a list of JSON Tokens returned by a JSON Scanner and produces a JSON Structure (JSON Tree).

---

```c
void * json_parser_alloc();
```

`json_parser_alloc()` allocates a JSON Parser structure on the Heap.

---

```c
int json_parser_do (json_parser_t *parser);
```

`json_parser_do()` parsers a list of JSON Tokens and produces a JSON Structure (JSON Tree).  Returns 0 upon success, otherwise returns -1.

---

```c
void json_parser_free(json_parser_t *parser);
```

`json_parser_free()` frees memory allocated for a JSON Parser on the Heap.

---

```c
int json_parser_init (json_parser_t *parser, char const *buffer);
```

`json_parser_init()` initializes the JSON Parser structure.  Returns 0 upon success, otherwise returns -1.

---

```c
void json_parser_term(json_parser_t *parser);
```

`json_parser_term()` terminates a JSON Parser.  Call `json_parser_term()` prior to calling `json_parser_free()`.
## JSON Writer
The JSON Writer outputs a JSON Tree to a JSON File.

---

```c
int json_writer_init (json_writer_t *writer, json_t *json, char const *path);
```

`json_writer_init()` initializes the JSON Writer structure.  Returns 0 upon success, otherwise returns -1.

---

```c
int json_writer_do (json_writer_t *);
```

`json_writer_do()` writes the JSON Tree out to a JSON File.  Returns 0 upon success, otherwise returns -1.

---

```c
void json_writer_term (json_writer_t *);
```
`json_writer_term` terminates a JSON Writer.  Call `json_writer_term()` prior to calling `json_writer_free()`.
