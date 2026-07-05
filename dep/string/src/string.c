#include "string.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

string string_empty()
{
    return string_from_cstring("");
}

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

string_array string_split(string str, const char *delimiter)
{
    string_array result = {
        .items = NULL,
        .count = 0,
    };

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
        for (size_t y = 0; y < delimiter_len && i + y < str.count; y++) {
            if (str.data[i + y] != delimiter[y]) {
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

bool string_is_equal(string a, string b)
{
    return string_starts_at(a, b) == 0 && a.count == b.count;
}

bool string_is_equal_cstring(string a, const char *b)
{
    string b_string = string_from_cstring((char *) b);

    return string_is_equal(a, b_string);
}

void string_trim_start(string *str)
{
    const char *trimmable_characters = "\n\r ";

    bool is_trimmable_character = false;
    for (size_t i = 0; i < str->count; i++) {
        for (size_t y = 0; y < strlen(trimmable_characters); y++) {
            if (str->data[i] == trimmable_characters[y]) {
                is_trimmable_character = true;
                break;
            }
        }

        if (is_trimmable_character == false) {
            str->data += i;
            str->count -= i;
            return;
        }

        is_trimmable_character = false;
    }
}

void string_trim_end(string *str)
{
    const char *trimmable_characters = "\n\r ";

    bool is_trimmable_character = false;
    for (size_t i = str->count - 1; i > 0; i--) {
        for (size_t y = 0; y < strlen(trimmable_characters); y++) {
            if (str->data[i] == trimmable_characters[y] || str->data[i] == '\0') {
                is_trimmable_character = true;
                break;
            }
        }

        if (is_trimmable_character == false) {
            str->count -= str->count - i - 1;
            return;
        }

        is_trimmable_character = false;
    }
}

void string_trim(string *str)
{
    string_trim_start(str);
    string_trim_end(str);
}
