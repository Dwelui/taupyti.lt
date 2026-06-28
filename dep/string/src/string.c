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

string_array string_split(string string, const char *delimiter)
{
    string_array result = {
        .items = NULL,
        .count = 0,
    };

    // TODO:
    // - [x] count seperate string amount (how many time delimiter is found minus if input string starts or ends with delimiter)
    // - [x] set count and allocate memory for strings in string_array
    // - [ ] travel input string and create strings that have data pointer and count according

    size_t delimiter_len = strlen(delimiter);
    size_t string_data_start = 1;
    size_t string_data_end = string.count - delimiter_len;

    bool delimeter_matches;
    int delimiter_count = 0;
    for (size_t i = string_data_start; i < string_data_end; i++) {
        delimeter_matches = true;
        for (size_t y = 0; y < delimiter_len; y++) {
            if (string.data[i + y] != delimiter[y]) {
                delimeter_matches = false;
                break;
            }
        }

        if (delimeter_matches) {
            delimiter_count++;
        }
    }

    result.count = delimiter_count + 1;
    result.items = malloc(sizeof(string) * result.count);

    size_t current_string_start = 0;
    size_t current_string_len = 0;
    size_t string_count = 0;
    for (size_t i = 0; i < string.count; i++) {
        delimeter_matches = true;
        for (size_t y = 0; y < delimiter_len && i + y <= string.count; y++) {
            if (string.data[i + y] != delimiter[y]) {
                delimeter_matches = false;
                break;
            }
        }

        if (delimeter_matches) {
            if (i < delimiter_len) {
                current_string_start += current_string_len + delimiter_len;
                continue;
            }

            current_string_len = i - current_string_start;
            result.items[string_count] = string_from_data(string.data + current_string_start, current_string_len);

            current_string_start += current_string_len + delimiter_len;

            char *s = string_to_cstring(result.items[string_count]);
            printf("(%s)", s);
            continue;
        }
    }

    if (current_string_start < string.count) {
        result.items[string_count] = string_from_data(string.data + current_string_start, current_string_len);
        char *s = string_to_cstring(result.items[string_count]);
        printf("(%s)", s);
    }

    return result;
}
