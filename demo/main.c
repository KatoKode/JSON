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
#include "main.h"
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// MAIN
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int main (int argc, char *argv[]) {

  json_test();

  return 0;
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// JSON_TEST
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void json_test (void)
{
  puts("Build JSON Tree\n");

  // Allocate a JSON Structure on the Heap
  json_t *json;
  if ((json = json_alloc()) == NULL) return;

  // Initialize a JSON Structure
  if (json_init(json) < 0) { json_free(json); }

  // Add a named Double Value to a JSON Structure (at uppermost level)
  json_value_t *json_value = json_alloc();
  json_value_set_double(json_value, DBL_MAX);

  char name [JSON_NAME_LEN + 1] = "DOUBLE_01";
  if (json_add_value(json, name, json_value) < 0) return;

  // Add a named Long Value to a JSON Structure (at uppermost level)
  json_value = json_value_alloc();
  json_value_set_long(json_value, LONG_MAX);

  (void) strncpy(name, "LONG_01", JSON_NAME_LEN);
  if (json_add_value(json, name, json_value) < 0) return;

  // Add a named JSON Object to a JSON Structure (at uppermost level)
  json_object_t *json_object = json_object_alloc();
  json_object_init(json_object);

  (void) strncpy(name, "OBJECT_01", JSON_NAME_LEN);
  if (json_add_object(json, name, json_object) < 0) return;

  // Add a named String Value to JSON Object "OBJECT_01"
  json_value = json_alloc();
  json_value_set_string(json_value, "THIS STRING WILL BE DELETED");

  (void) strncpy(name, "STRING_00", JSON_NAME_LEN);
  if (json_object_add_value(json_object, name, json_value) < 0) return;

  // Add a named String Value to JSON Object "OBJECT_01"
  json_value = json_alloc();
  json_value_set_string(json_value, "THIS IS A STRING");

  (void) strncpy(name, "STRING_01", JSON_NAME_LEN);
  if (json_object_add_value(json_object, name, json_value) < 0) return;

  // Add a named Long Value to JSON Object "OBJECT_01"
  json_value = json_alloc();
  json_value_set_long(json_value, -32768);

  (void) strncpy(name, "LONG_02", JSON_NAME_LEN);
  if (json_object_add_value(json_object, name, json_value) < 0) return;

  // Add a named Boolean Value to JSON Object "OBJECT_01"
  json_value = json_alloc();
  json_value_set_boolean(json_value, json_true);

  (void) strncpy(name, "BOOL_01", JSON_NAME_LEN);
  if (json_object_add_value(json_object, name, json_value) < 0) return;

  // Add a named JSON Array to a JSON Structure (at uppermost level)
  json_array_t *json_array = json_array_alloc();
  json_array_init(json_array);

  (void) strncpy(name, "ARRAY_01", JSON_NAME_LEN);
  if (json_add_array(json, name, json_array) < 0) return;

  // Add a Long Value to JSON Array "ARRAY_01"
  json_value = json_alloc();
  json_value_set_long(json_value, 65536);

  if (json_array_add_value(json_array, json_value) < 0) return;

  // Add a String Value to JSON Array "ARRAY_01"
  json_value = json_alloc();
  json_value_set_string(json_value, "THIS TOO IS A STRING");

  if (json_array_add_value(json_array, json_value) < 0) return;

  // Add a Boolean Value to JSON Array "ARRAY_01"
  json_value = json_alloc();
  json_value_set_boolean(json_value, json_false);

  if (json_array_add_value(json_array, json_value) < 0) return;

  // Add a Double Value to JSON Array "ARRAY_01"
  json_value = json_alloc();
  json_value_set_double(json_value, 0.00654);

  if (json_array_add_value(json_array, json_value) < 0) return;

  // Add a JSON Array to JSON Array "ARRAY_01"
  json_array_t *json_array_2 = json_array_alloc();
  json_array_init(json_array_2);

  if (json_array_add_array(json_array, json_array_2) < 0) return;

  // Add a String Value to JSON Array "ARRAY_01"
  json_value = json_alloc();
  json_value_set_string(json_value, "THIS STRING WILL ALSO BE DELETED");

  if (json_array_add_value(json_array, json_value) < 0) return;

  // Add a String Value to a JSON Array
  json_value = json_alloc();
  json_value_set_string(json_value, "ONE");

  if (json_array_add_value(json_array_2, json_value) < 0) return;

  // Add a String Value to a JSON Array
  json_value = json_alloc();
  json_value_set_string(json_value, "TWO");

  if (json_array_add_value(json_array_2, json_value) < 0) return;

  // Add a String Value to a JSON Array
  json_value = json_alloc();
  json_value_set_string(json_value, "THREE");

  if (json_array_add_value(json_array_2, json_value) < 0) return;

  // Add a named String Value to the JSON Object "OBJECT_01"
  json_value = json_alloc();
  json_value_set_string(json_value, "THIS IS ALSO A STRING");

  (void) strncpy(name, "STRING_02", JSON_NAME_LEN);
  if (json_object_add_value(json_object, name, json_value) < 0) return;

  // Add a named Double Value to the JSON Object "OBJECT_01"
  json_value = json_alloc();
  json_value_set_double(json_value, 0.0005432);

  (void) strncpy(name, "DOUBLE_02", JSON_NAME_LEN);
  if (json_object_add_value(json_object, name, json_value) < 0) return;

  // Add a named JSON Object to JSON Object "OBJECT_01"
  json_object_t *json_object_2 = json_object_alloc();
  json_object_init(json_object_2);

  (void) strncpy(name, "OBJECT_02", JSON_NAME_LEN);
  if (json_object_add_object(json_object, name, json_object_2) < 0) return;

  // Add a named String Value to the JSON Object "OBJECT_02"
  json_value = json_alloc();
  json_value_set_string(json_value, "YET ANOTHER STRING");

  (void) strncpy(name, "STRING_03", JSON_NAME_LEN);
  if (json_object_add_value(json_object_2, name, json_value) < 0) return;

  // Add a named Long Value to the JSON Object "OBJECT_02"
  json_value = json_alloc();
  json_value_set_long(json_value, 131072);

  (void) strncpy(name, "LONG_03", JSON_NAME_LEN);
  if (json_add_value(json, name, json_value) < 0) return;

  puts("Build JSON Tree Successful\n");

  puts("Delete String \"STRING_00\" from JSON Object \"OBJECT_01\"\n");

  // Delete String "STRING_00" from JSON Object "OBJECT_01"
  json_member_t *member;
  if ((member = json_search(json, "OBJECT_01")) == NULL) return;

  json_object = member;
  if (json_object_delete_member(json_object, "STRING_00") < 0) return;

  puts("Delete String Successful\n");

  puts("Delete String from JSON ARRAY \"ARRAY_01\"\n");

  // Delete String from JSON ARRAY "ARRAY_01"
  if ((member = json_search(json, "ARRAY_01")) == NULL) return;

  json_array = member;
  if (json_array_delete_member(json_array, 5) < 0) return;

  puts("Delete String Successful\n");

  puts("Write JSON Tree to File\n");

  // Allocate a JSON Writer
  char const path[] = "./demo_1.json";
  json_writer_t *json_writer;
  if ((json_writer = json_writer_alloc()) == NULL) return;

  // Initialize a JSON Writer
  if (json_writer_init(json_writer, json, path) < 0) return;

  // Write a JSON Tree to a JSON File
  if (json_writer_do(json_writer) < 0) return;

  // Terminate a JSON Writer
  json_writer_term(json_writer);
  // Free a JSON Writer
  json_writer_free(json_writer);

  puts("Write JSON Tree Successful\n");

  // Terminate a JSON Structure
  json_term(json);
  // Free a JSON Structure
  json_free(json);

  // Take a break, share CPU
  puts("Pause\n");

  struct timespec req = { 0, 500000000 };
  (void) nanosleep(&req, NULL);

  puts("Scan JSON File into JSON Tokens\n");

  // Initialize a JSON Scanner
  json_scanner_t json_scanner;
  if (json_scanner_init(&json_scanner, path) < 0) return;

  // Scan a JSON File into JSON Tokens
  if (json_scanner_do(&json_scanner) < 0) return;

  puts("Scan JSON File Successful\n");

  // Take a break, share CPU
  puts("Pause\n");

  (void) nanosleep(&req, NULL);

  puts("Parse JSON Tokens into JSON Tree\n");

  // Initialize a JSON Parser
  json_parser_t json_parser;
  if (json_parser_init(&json_parser, &json_scanner) < 0) return;

  // Parse JSON Tokens into a JSON Structure
  if (json_parser_do(&json_parser) < 0) return;

  puts("Parse JSON Tokens Successful\n");

  // Take a break, share CPU
  puts("Pause\n");

  (void) nanosleep(&req, NULL);

  json = json_parser.json;

  // Terminate a JSON Parser
  json_parser_term(&json_parser);

  // Terminate a JSON Scanner
  json_scanner_term(&json_scanner);

  puts("Search JSON Tree for JSON Object \"OBJECT_01\"\n");

  // Retrieve a named JSON Object from a JSON Structure
  if ((member = json_search(json, "OBJECT_01")) == NULL) return;

  if (json_member_type(member) != JSON_OBJECT) return;

  puts("Search JSON Tree Successful\n");

  json_object_t *object = member;

  puts("Search JSON Object \"OBJECT_01\" for Long Value \"LONG_02\"\n");

  // Retreive a Long Value from JSON Object "OBJECT_01"
  if ((member = json_object_search(object, "LONG_02")) == NULL) return;

  if (json_member_type(member) != JSON_LONG) return;

  puts("Search JSON Object Successful\n");

  puts("Output JSON Value \"LONG_02\"\n");

  json_value_t *value = member;
  printf("  LONG_02: %ld\n\n", json_value_get_long(value));

  puts("Search JSON Tree for JSON Array \"ARRAY_01\"\n");

  // Retrieve a named JSON Array from a JSON Structure
  if ((member = json_search(json, "ARRAY_01")) == NULL) return;

  if (json_member_type(member) != JSON_ARRAY) return;

  puts("Search JSON Tree Successful\n");

  json_array = member;

  puts("Output JSON Array \"ARRAY_01\"\n");

  // Print the members of JSON Array "ARRAY_01"
  printf("  ARRAY_01: ");
  print_json_array(json_array);
  putchar('\n');
  putchar('\n');

  puts("Write JSON Tree to File\n");

  // Allocate a JSON Writer
  char const path2[] = "./demo_2.json";
  json_writer = json_writer_alloc();

  // Initialize a JSON Writer
  if (json_writer_init(json_writer, json, path2) < 0) return;

  // Write a JSON Tree to a JSON File
  if (json_writer_do(json_writer) < 0) return;

  puts("Write JSON Tree Successful\n");

  // Terminate a JSON Writer
  json_writer_term(json_writer);
  // Free a JSON Writer
  json_writer_free(json_writer);

  // Terminate a JSON Structure
  json_term(json);
  // Free a JSON Structure
  json_free(json);
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// print_json_array
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void print_json_array (json_array_t *json_array)
{
  int do_comma = 0;

  putchar('[');

  for (json_member_t *member = json_array_begin(json_array);
      member != NULL;
      member = json_array_next(json_array))
  {
    if (do_comma) putchar(',');
    else do_comma = 1;

    switch (json_member_type(member))
    {
      case JSON_BOOLEAN:
        {
          json_value_t *value = member;
          printf("%s", json_value_get_boolean(value));
        }
        break;
      case JSON_DOUBLE:
        {
          json_value_t *value = member;
          printf("%g", json_value_get_double(value));
        }
        break;
      case JSON_LONG:
        {
          json_value_t *value = member;
          printf("%ld", json_value_get_long(value));
        }
        break;
      case JSON_STRING:
        {
          json_value_t *value = member;
          printf("\"%s\"", json_value_get_string(value));
        }
        break;
      case JSON_ARRAY:
        {
          json_array_t *json_array_2 = member;
          print_json_array(json_array_2);
        }
        break;
      case JSON_OBJECT:
        puts("OBJECT\n");
        break;
      default:;
    }
  }
  putchar(']');
}
