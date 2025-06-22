


Just Another Armchair Programmer

JSON Library Written in C with Assembly Language Support Libraries

by Jerry McIntosh
## JSON Structure
A JSON structure is the main JSON structure and represents the top of the JSON tree.  A JSON structure can hold Objects, Arrays, and Values.

```c
int json_add_array (json_t *json, char *name, json_array_t *array);
```

Adds a named Array to the top level of a JSON tree.

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
int json_init (json_t *);
```

`json_init()` initializes a JSON structure.

```c
void json_term (json_t *);
```

`json_term()` terminates a JSON structure.  Call `json_term()` prior to calling `json_free()`.
## Array Structure
An Array structure can hold unnamed Objects, Arrays, and Values.  Each item in an Array is a member of a Node.  A Node can hold one of the following: an Object, an Array, or a Value.

```c
int json_array_add_array (json_array_t *parent, json_array_t *child);
```

`json_array_add_array()` adds an Array to an Array.

```c
int json_array_add_object (json_array_t *parent, json_object_t *child);
```

`json_array_add_object()` adds an Object to an Array.

```c
int json_array_add_value (json_array_t *parent, json_value_t *child);
```

`json_array_add_value()` adds a Value to an Array.

```c
void * json_array_alloc();
```

`json_array_alloc()` allocates an Array on the Heap.

```c
void json_array_free(json_array_t *array);
```

`json_array_free()` free memory allocated for an Array on the Heap.

```c
int json_array_init (json_array_t *);
```

`json_array_init()` initializes an Array.  An Array must be initialized before use.

```c
void json_array_term (json_array_t *);
```

`json_array_term()` terminates an Array.  Call `json_array_term()` prior to calling `json_array_free()`.
## Node Structure
A Node structure can hold one member: an Object, an Array, or a Value.  A Node is used to hold a member of an Array.  A Node is also used to hold the value of a key-value Pair in an Object.

```c
json_array_t * json_node_get_array (json_node_t *);
```

`json_node_get_array()` returns the address of an Array stored in a Node, or `NULL` if a Node is empty.

```c
json_object_t * json_node_get_object (json_node_t *);
```

`json_node_get_object()` returns the address of an Object stored in a Node, or `NULL` if a Node is empty.

```c
json_value_t * json_node_get_value (json_node_t *);
```

`json_node_get_value()` returns the address of a Value stored in a Node, or `NULL` if a Node is empty.

```c
void json_node_init (json_node_t *, void *);
```

`json_node_init()()` initializes a Node.  A Node must be initialized before use.

```c
void json_node_set_array (json_node_t *, json_array_t *);
```

`json_node_set_array()` sets an Array as the new member of a Node.

```c
void json_node_set_object (json_node_t *, json_object_t *);
```

`json_node_set_object()` sets an Object as the new member of a Node.

```c
void json_node_set_value (json_node_t *, json_value_t *);
```

`json_node_set_value()` sets a Value as the new member of a Node.

```c
void json_node_term (json_node_t *);
```

`json_node_term()` terminates a Node.  Call `json_node_term()` prior to calling `json_node_free()`.

```c
int json_node_type (json_node_t *);
```

`json_node_type()` returns the type of member held in a Node, or `JSON_NULL` if no member is present.
## Object Structure
An Object structure can hold named Objects, Arrays, and Values.  Each item in an Object is a member of a Node which in turn is a member of a key-value Pair.  A Node can hold one of the following: an Object, an Array, or a Value.

```c
int json_object_add_array (json_object_t *, char *, json_array_t *);
```

`json_object_add_array()` adds an Array to an Object.

```c
int json_object_add_object (json_object_t *, char *, json_object_t *);
```

`json_object_add_object()` adds an Object to an Object.

```c
int json_object_add_value (json_object_t *, char *, json_value_t *);
```

`json_object_add_value()` adds a Value to an Object.

```c
void * json_object_alloc();
```

`json_object_alloc()` allocate memory on the Heap for an Object.

```c
void json_object_free(json_object_t *object);
```

`json_object_free()` free memory allocated for an Object on the Heap.

```c
int json_object_init (json_object_t *);
```

`json_object_init()` initializes an Object.  An Object must be initialized before use.

```c
void json_object_term (json_object_t *);
```

`json_object_term()` terminates a Node.  Call `json_object_term()` prior to calling `json_object_free()`.
## Value Structure
```c
void * json_value_alloc();
```

`json_value_alloc()` allocate memory on the Heap for a Value.

```c
void json_value_free(json_value_t *value);
```

`json_value_free()` free memory allocated for a Value on the Heap.

```c
char const * json_value_get_boolean (json_value_t *);
```

`json_value_get_boolean()` returns the Boolean value stored in a Value.  If Value is empty or contains something other than a Boolean the behavior is undefined.

```c
double json_value_get_double (json_value_t *);
```

`json_value_get_double()` retrieves the Double value stored in a Value.  If Value is empty or contains something other than a Double the behavior is undefined.

```c
long json_value_get_long (json_value_t *);
```

`json_value_get_long()` retrieves the Long value stored in a Value.  If Value is empty or contains something other than a Long the behavior is undefined.

```c
char const * json_value_get_string (json_value_t *jvalue);
```

`json_value_get_string()` retrieves the String value stored in a Value.  If Value is empty or contains something other than a String the behavior is undefined.

```c
void json_value_set_boolean (json_value_t *jvalue, char const *value);
```

`json_value_set_boolean()` sets the type and value of a Value to a Boolean value.

```c
void json_value_set_double (json_value_t *jvalue, double value);
```

`json_value_set_double()` sets the type and value of a Value to a Double value.

```c
void json_value_set_long (json_value_t *jvalue, long value);
```

`json_value_set_long()` sets the type and value of a Value to a Long value.

```c
void json_value_set_string (json_value_t *jvalue, char *value);
```

`json_value_set_string()` sets the type and value of a Value to a String value.

```c
void json_value_term (json_value_t *jvalue);
```

`json_value_term()` terminates a Value.  Call `json_value_term()` prior to calling `json_value_free()`

## JSON Tree Walk Function
```c
int json_walk (json_t *json, void *cb_data,
    int (*enter_cb) (char const *, json_node_t *, void *),
    int (*exit_cb) (char const *, json_node_t *, void *));
```

Parameters:
+ pointer to a JSON structure.
+ pointer to user-defined data.
+ pointer to user-defined callback function, `enter_cb`.
+ pointer to user-defined callback function, `exit_cb` or `NULL`.

`json_walk()` walks the JSON tree calling `enter_cb` and `exit_cb` at each node.  Parameter `cb_data` is passed to both callback functions as the last parameter.

`cb_data` is for user-defined data.  `cb_data` is passed to both `enter_cb` and `exit_cb` as the last paramenter.

`enter_cb()` is a user-defined callback function that is called at each Node.  The parameters are as follows:

+ pointer to a name (key) associated with the Node.  Could be `NULL`.
+ pointer to the current Node.
+ pointer to user-defined `cb_data` parameter.

`exit_cb()` is a user-defined callback function that is called just prior to leaving the current Node.  `NULL` can be passed in place of `exit_cb`.  The parameters are as follows:

+ pointer to a name (key) associated with the Node.  Could be `NULL`.
+ pointer to the current Node.
+ pointer to user-defined `cb_data` parameter.
## Convenience Functions
```c
int json_add_boolean_value (json_t *json, char *name, char const *value);
```

`json_add_boolean_value()` is a convenience function for adding a Boolean value to the upper-most level of a JSON tree.

```c
int json_add_double_value (json_t *, char *, double);
```

`json_add_double_value()` is a convenience function for adding a Double value to the upper-most level of a JSON tree.

```c
int json_add_long_value (json_t *, char *, long);
```

`json_add_long_value()` is a convenience function for adding a Long value to the upper-most level of a JSON tree.

```c
int json_add_string_value (json_t *, char *, char *);
```

`json_add_string_value()` is a convenience function for adding a String value to the upper-most level of a JSON tree.

```c
int json_array_add_boolean_value (json_array_t *, char const *);
```

`json_array_add_boolean_value()` is a convenience function for adding a Boolean value to an Array.

```c
int json_array_add_double_value (json_array_t *, double);
```

`json_array_add_double_value()` is a convenience function for adding a Double value to an Array.

```c
int json_array_add_long_value (json_array_t *, long);
```

`json_array_add_long_value()` is a convenience function for adding a Long value to an Array.

```c
int json_array_add_string_value (json_array_t *, char *);
```

`json_array_add_string_value()` is a convenience function for adding a String value to an Array.

```c
int json_object_add_boolean_value (json_object_t *, char *, char const *);
```

`json_object_add_boolean_value()` is a convenience function for adding a Boolean value to an Object.

```c
int json_object_add_double_value (json_object_t *, char *, double);
```

`json_object_add_double_value()` is a convenience function for adding a Double value to an Object.

```c
int json_object_add_long_value (json_object_t *, char *, long);
```

`json_object_add_long_value()` is a convenience function for adding a Long value to an Object.

```c
int json_object_add_string_value (json_object_t *, char *, char *);
```

`json_object_add_string_value()` is a convenience function for adding a String value to an Object.

