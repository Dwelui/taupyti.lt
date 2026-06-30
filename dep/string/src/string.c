#include "string.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

string string_from_data(char* data, size_t count)
{
    string result = {
        .data = data,
        .count = 0,
    };

    if (data == NULL) {
        return result;
    }

    result.count = count;

    return result;
}

string string_from_cstring(char *data)
{
    return string_from_data(data, strlen(data));
}

char *string_to_cstring(string str)
{
    char *result = malloc(str.count + 1);
    if (result == NULL) {
        return NULL;
    }

    memcpy(result, str.data, str.count);
    result[str.count] = '\0';

    return result;
}

// string_is_equal -> string_starts_at(a_string, b_string) == 0 && a_string.count == b_string.count

string_array string_split(string str, const char *delimiter)
{
    string_array result = {
        .items = NULL,
        .count = 0,
    };

    string delimiter_string = string_from_cstring((char *)delimiter);
    size_t delimiter_len = strlen(delimiter);

    bool delimeter_matches;
    int delimiter_count = 0;
    for (size_t i = 1; i < str.count - delimiter_len; i++) {
        delimeter_matches = true;
        for (size_t y = 0; y < delimiter_len; y++) {
            if (str.data[i + y] != delimiter[y]) {
                delimeter_matches = false;
                break;
            }
        }

        // if (string_starts_at(str, delimiter_string) == i) {
        //     delimeter_matches = false;
        // }

        if (delimeter_matches) {
            delimiter_count++;
        }
    }

    result.count = delimiter_count + 1;
    result.items = malloc(sizeof(str) * result.count);

    size_t current_string_start = 0;
    size_t current_string_len = 0;
    int string_count = 0;
    for (size_t i = 0; i < str.count; i++) {
        delimeter_matches = true;
        //                                                            ,-delimiter
        //                                                           \/
        // TODO: Can be abstracted into string_starts_at(string, substring) == i
        for (size_t y = 0; y < delimiter_len && i + y < str.count; y++) {
            if (str.data[i + y] != delimiter[y]) {
                delimeter_matches = false;
                break;
            }
        }

        // if (string_starts_at(str, delimiter_string) == i) {
        //     delimeter_matches = false;
        // }

        if (delimeter_matches) {
            if (i < delimiter_len) {
                current_string_start += current_string_len + delimiter_len;
                continue;
            }
            current_string_len = i - current_string_start;

            result.items[string_count] = string_from_data(str.data + current_string_start, current_string_len);

            string_count++;
            current_string_start += current_string_len + delimiter_len;
        }
    }

    if (current_string_start < str.count) {
        result.items[string_count] = string_from_data(str.data + current_string_start, str.count - current_string_start);
    }

    return result;
}

void string_array_free(string_array array)
{
    free(array.items);
}


size_t string_starts_at(string str, string substr)
{
    size_t position = -1;

    if (str.count < substr.count) {
        return position;
    }

    size_t y = 0;
    for (size_t i = 0; i < str.count; i++) {
        y = 0;
        for (; y < substr.count; y++) {
            if (str.data[i + y] != substr.data[y]) {
                break;
            }

        }

        if (y == substr.count) {
            position = i;
            break;
        }
    }

    return position;
}
