#include "string.h"
#include <stdlib.h>
#include <string.h>

string string_from_cstring(const char *data)
{
    string result;

    result.count = strlen(data);
    result.data = malloc(result.count);

    if (result.data == NULL) {
        result.count = 0;
        return result;
    }

    memcpy(result.data, data, result.count);

    return result;
}

char *string_to_cstring(string string)
{
    char *result = malloc(string.count + 1);
    if (result == NULL) {
        return NULL;
    }

    memcpy(result, string.data, string.count);
    result[string.count + 1] = 0;

    return result;
}
