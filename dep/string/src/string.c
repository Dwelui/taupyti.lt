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

// TODO: Do not allocate additional for copying string into seperate structs.
// Make all string structs look at the same string data.
string_array string_split(string string, const char *delimiter)
{
    string_array result = {
        .items = NULL,
        .count = 0,
    };

    // TODO:
    // count seperate string amount (how many time delimiter is found minus if input string starts or ends with delimiter)
    // allocate memory for strings in string_array
    // travel input string and create strings that have data pointyer and count according


    for (size_t i = 0; i <= string.count; i++) {
        
    }

    return result;
}
