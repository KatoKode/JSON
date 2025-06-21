


Just Another Armchair Programmer

JSON Library Written in C with Assembly Language Support Libraries

by Jerry McIntosh
# Introduction
## JSON\_T Structure
The `json_t` structure is the main JSON structure and represents the top of the JSON tree.

```c
int json_add_array (json_t *parent, char *name, json_array_t *child);
```

    Add a named `json_array_t` structure to a `json_t` structure.

```c
int json_add_object (json_t *parent, char *name, json_object_t *child);
```

    Add a named `json_object_t` structure to a `json_t` structure.

```c
int json_add_value (json_t *parent, char  *name, json_value_t *child);
```

    Add a named `json_value_t` structure to a `json_t` structure.

```c
int json_init (json_t *);
```

    Initialize a `json_t` structure.

```c
void json_term (json_t *);
```

    Terminate a `json_t` structure. Call `json_term()` prior to calling `json_free()`.

## JSON\_ARRAY\_T Structure
The `json_array_t` structure can hold unnamed objects, arrays, and values.

```c
int json_array_add_array (json_array_t *parent, json_array_t *child);
```

    Add `json_array_t` structure to a `json_array_t` structure.

```c
int json_array_add_object (json_array_t *parent, json_object_t *child);
```

    Add `json_object_t` structure to a `json_array_t` structure.

```c
int json_array_add_value (json_array_t *parent, json_value_t *child);
```

    Add `json_value_t` structure to a `json_array_t` structure.

```c
int json_array_init (json_array_t *);
```

    Initialize a `json_array_t` structure.

```c
void json_array_term (json_array_t *);
```

    Terminate a `json_array_t` structure.  Call `json_array_term()` prior to calling `json_array_free()`.

## JSON\_NODE\_T Structure
```c
json_array_t * json_node_get_array (json_node_t *);
```
json_object_t * json_node_get_object (json_node_t *);
json_value_t * json_node_get_value (json_node_t *);
void json_node_init (json_node_t *, void *);
void json_node_set_array (json_node_t *, json_array_t *);
void json_node_set_object (json_node_t *, json_object_t *);
void json_node_set_value (json_node_t *, json_value_t *);
void json_node_term (json_node_t *);
int json_node_type (json_node_t *);

int json_object_add_array (json_object_t *, char *, json_array_t *);
int json_object_add_object (json_object_t *, char *, json_object_t *);
int json_object_add_value (json_object_t *, char *, json_value_t *);
int json_object_init (json_object_t *);
void json_object_term (json_object_t *);

void json_pair_init (json_pair_t *, char *, json_node_t *);
void json_pair_term (json_pair_t *);

char const * json_value_get_boolean (json_value_t *);
double json_value_get_double (json_value_t *);
long json_value_get_long (json_value_t *);
char const * json_value_get_string (json_value_t *);
void json_value_set_boolean (json_value_t *, char const *);
void json_value_set_double (json_value_t *, double);
void json_value_set_long (json_value_t *, long);
void json_value_set_string (json_value_t *, char *);
void json_value_term (json_value_t *);

int json_walk (json_t *, void *,
    int (*enter_cb) (char const *, json_node_t *, void *),
    int (*exit_cb) (char const *, json_node_t *, void *));

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


