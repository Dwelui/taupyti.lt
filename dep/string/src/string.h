#ifndef STRING_H
#define STRING_H

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

typedef struct {
    char *data;
    size_t count;
} string;

typedef struct {
    string *items;
    size_t count;
} string_array;

string string_empty();
string string_from_data(char* data, size_t count);
string string_from_cstring(char *data);
char *string_to_cstring(string str);

string_array string_split(string str, const char *delimiter);
void string_array_free(string_array array);

ssize_t string_starts_at(string str, string substr);
bool string_is_equal(string a, string b);
bool string_is_equal_cstring(string a, const char *b);

void string_trim_start(string *str);
void string_trim_end(string *str);
void string_trim(string *str);

// Passing 0 to `end` takes the `end` of string for substring.
string string_substring(string str, size_t start, size_t end);

#endif // STRING_H
