


Just Another Armchair Programmer

JSON Library Written in C with Assembly Language Support Libraries

by Jerry McIntosh
## JSON Structure
A JSON structure is the main structure and represents the top of the JSON tree.  A JSON structure can hold Objects, Arrays, and Values.

```c
int json_add_array (json_t *json, char *name, json_array_t *array);
```

`json_add_array` adds a named Array to the top level of a JSON tree.

```c
int json_add_object (json_t *json, char *name, json_object_t *object);
```

`json_add_object()` adds a named Object to the top level of a JSON tree.

```c
int json_add_value (json_t *json, char  *name, json_value_t *value);
```

`json_add_value()` adds a named Value to the top level of a JSON tree.

```c
void * json_alloc();
```

`json_alloc()` allocates a JSON structure on the Heap.

```c
void json_free(json_t *json);
```

`json_free()` free memory allocated for a JSON structure on the Heap.

```c
int json_init (json_t *json);
```

`json_init()` initializes a JSON structure.

```c
json_member_t * json_search (json_t *json, char *name);
```

`json_search()` searches the top of the JSON tree for a member with a name matching `name`.  If a match is found a pointer to the corresponding member is returned, otherwise, `NULL` is returned.

```c
void json_term (json_t *json);
```

`json_term()` terminates a JSON structure.  Call `json_term()` prior to calling `json_free()`.
## Array Structure
An Array structure can hold unnamed Objects, Arrays, and Values.  Each member of an Array is stored in a Node.  A Node can hold one of the following: an Object, an Array, or a Value.

```c
int json_array_add_array (json_array_t *array, json_array_t *new_array);
```

`json_array_add_array()` adds an Array to an Array.

```c
int json_array_add_object (json_array_t *array, json_object_t *object);
```

`json_array_add_object()` adds an Object to an Array.

```c
int json_array_add_value (json_array_t *array, json_value_t *value);
```

`json_array_add_value()` adds a Value to an Array.

```c
void * json_array_alloc();
```

`json_array_alloc()` allocates an Array on the Heap.

```c
json_member_t * json_array_begin (json_array_t *array);
```

`json_array_begin` returns the first member of an Array or `NULL` should the Array be empty.  `json_array_begin` must be called prior to `json_array_next` to initiate the iteration through an Array.

```c
void json_array_free (json_array_t *array);
```

`json_array_free()` free memory allocated for an Array on the Heap.

```c
json_member_t * json_array_get_member (json_array_t *array, size_t index);
```

`json_array_get_member()` returns a pointer to the member[`index`] of an Array or `NULL` should `index` be out-of-bounds.

```c
int json_array_init (json_array_t *);
```

`json_array_init()` initializes an Array.  An Array must be initialized before use.

```c
json_member_t * json_array_next (json_array_t *array);
```

`json_array_next()` returns a pointer to the next member of an Array or `NULL` when the end of an Array has been reached.  NOTE: `json_array_begin()` must be called prior to any call to `json_array_next()`.

```c
void json_array_term (json_array_t *array);
```

`json_array_term()` terminates an Array.  Call `json_array_term()` prior to calling `json_array_free()`.
## Object Structure
An Object structure can hold named Objects, Arrays, and Values.  Each item in an Object is a member of a key-value Pair.  A key-value Pair can hold one of the following: an Object, an Array, or a Value.

```c
int json_object_add_array (json_object_t *object, char *name, json_array_t *array);
```

`json_object_add_array()` adds a named Array to an Object.

```c
int json_object_add_object (json_object_t *object, char *name, json_object_t *new_object);
```

`json_object_add_object()` adds a named Object to an Object.

```c
int json_object_add_value (json_object_t *object, char *name, json_value_t *value);
```

`json_object_add_value()` adds a named Value to an Object.

```c
void * json_object_alloc();
```

`json_object_alloc()` allocate memory on the Heap for an Object.

```c
void json_object_free(json_object_t *object);
```

`json_object_free()` free memory allocated for an Object on the Heap.

```c
int json_object_init (json_object_t *object);
```

`json_object_init()` initializes an Object.  An Object must be initialized before use.

```c
void json_object_term (json_object_t *object);
```

`json_object_term()` terminates a Node.  Call `json_object_term()` prior to calling `json_object_free()`.
## Value Structure
A Value structure can hold one of the following primary values: a Boolean, a Double, a Long, or a String.

```c
void * json_value_alloc();
```

`json_value_alloc()` allocate memory on the Heap for a Value.

```c
void json_value_free(json_value_t *value);
```

`json_value_free()` free memory allocated for a Value on the Heap.

```c
char const * json_value_get_boolean (json_value_t *value);
```

`json_value_get_boolean()` returns the Boolean value stored in a Value.  If Value is empty or contains something other than a Boolean the behavior is undefined.

```c
double json_value_get_double (json_value_t *value);
```

`json_value_get_double()` retrieves the Double value stored in a Value.  If Value is empty or contains something other than a Double the behavior is undefined.

```c
long json_value_get_long (json_value_t *value);
```

`json_value_get_long()` retrieves the Long value stored in a Value.  If Value is empty or contains something other than a Long the behavior is undefined.

```c
char * json_value_get_string (json_value_t *value);
```

`json_value_get_string()` retrieves the String value stored in a Value.  If Value is empty or contains something other than a String the behavior is undefined.

```c
void json_value_set_boolean (json_value_t *value, char const *new_value);
```

`json_value_set_boolean()` sets the type and value of a Value to a Boolean value.

```c
void json_value_set_double (json_value_t *value, double new_value);
```

`json_value_set_double()` sets the type and value of a Value to a Double value.

```c
void json_value_set_long (json_value_t *value, long new_value);
```

`json_value_set_long()` sets the type and value of a Value to a Long value.

```c
void json_value_set_string (json_value_t *value, char *new_value);
```

`json_value_set_string()` sets the type and value of a Value to a String value.

```c
void json_value_term (json_value_t *value);
```

`json_value_term()` terminates a Value.  Call `json_value_term()` prior to calling `json_value_free()`

## JSON Tree Walk Function
```c
int json_walk (json_t *json, void *cb_data,
    int (*enter_cb) (char const *, json_member_t *, void *),
    int (*exit_cb) (char const *, json_member_t *, void *));
```
Note: `NULL` can be passed for `exit_cb`.

`json_walk()` walks the JSON tree calling `enter_cb` and `exit_cb` at each member.  Parameter `cb_data` is passed to both callback functions as the last parameter.

`cb_data` is for user-defined data.  `cb_data` is passed to both `enter_cb` and `exit_cb` as the last paramenter.

`enter_cb()` is a user-defined callback function that is called at each member.  The parameters are as follows:

+ pointer to a name (key) associated with the Node.  Could be `NULL`.
+ pointer to the current member.
+ pointer to user-defined `cb_data` parameter.

`exit_cb()` is a user-defined callback function that is called just prior to leaving the current member.  `NULL` can be passed in place of `exit_cb`.  The parameters are as follows:

+ pointer to a name (key) associated with the member.  Could be `NULL`.
+ pointer to the current member.
+ pointer to user-defined `cb_data` parameter.
## Convenience Functions
```c
int json_add_boolean_value (json_t *json, char *name, char const *value);
```

`json_add_boolean_value()` is a convenience function for adding a Boolean value to the upper-most level of a JSON tree.

```c
int json_add_double_value (json_t *json, char *name, double value);
```

`json_add_double_value()` is a convenience function for adding a Double value to the upper-most level of a JSON tree.

```c
int json_add_long_value (json_t *json, char *name, long value);
```

`json_add_long_value()` is a convenience function for adding a Long value to the upper-most level of a JSON tree.

```c
int json_add_string_value (json_t *json, char *name, char *value);
```

`json_add_string_value()` is a convenience function for adding a String value to the upper-most level of a JSON tree.

```c
int json_array_add_boolean_value (json_array_t *array, char const *value);
```

`json_array_add_boolean_value()` is a convenience function for adding a Boolean value to an Array.

```c
int json_array_add_double_value (json_array_t *array, double value);
```

`json_array_add_double_value()` is a convenience function for adding a Double value to an Array.

```c
int json_array_add_long_value (json_array_t *array, long value);
```

`json_array_add_long_value()` is a convenience function for adding a Long value to an Array.

```c
int json_array_add_string_value (json_array_t *array, char *value);
```

`json_array_add_string_value()` is a convenience function for adding a String value to an Array.

```c
int json_object_add_boolean_value (json_object_t *object, char *name, char const *value);
```

`json_object_add_boolean_value()` is a convenience function for adding a Boolean value to an Object.

```c
int json_object_add_double_value (json_object_t *object, char *name, double value);
```

`json_object_add_double_value()` is a convenience function for adding a Double value to an Object.

```c
int json_object_add_long_value (json_object_t *object, char *name, long value);
```

`json_object_add_long_value()` is a convenience function for adding a Long value to an Object.

```c
int json_object_add_string_value (json_object_t *object, char *name, char *value);
```

`json_object_add_string_value()` is a convenience function for adding a String value to an Object.

