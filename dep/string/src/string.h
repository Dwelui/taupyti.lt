#ifndef STRING_H
#define STRING_H

#include <stddef.h>

typedef struct {
    char *data;
    size_t count;
} string;

typedef struct {
    string *items;
    size_t count;
} string_array;

string string_from_data(char* data, size_t count);
string string_from_cstring(char *data);
char *string_to_cstring(string string);

string_array string_split(string string, const char *delimiter);
void string_array_free(string_array array);

#endif // STRING_H
