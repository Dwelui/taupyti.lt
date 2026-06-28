#ifndef STRING_H
#define STRING_H

#include <stddef.h>

typedef struct {
    char *data;
    size_t count;
} string;

string string_from_cstring(const char *data);
char *string_to_cstring(string string);

#endif // STRING_H
