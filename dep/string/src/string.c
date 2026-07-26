#include "string.h"
#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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

string_array string_array_create(size_t capacity)
{
    string_array result = {
        .items = NULL,
        .count = 0,
    };

    if (capacity > 0) {
        result.items = malloc(sizeof(string) * capacity);
        result.capacity = capacity;
    }

    return result;
}

void string_array_free(string_array array)
{
    free(array.items);
}

void string_array_push(string_array *str_array, string str)
{
    // TODO: expand string_array to fit more.
    assert(str_array->count < str_array->capacity);

    str_array->items[str_array->count] = str;
    str_array->count++;
}

string_array string_split(string str, const char *delimiter)
{
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

    string_array result = string_array_create(delimiter_count + 1);

    size_t current_string_start = 0;
    size_t current_string_len = 0;
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

            string_array_push(&result, string_from_data(str.data + current_string_start, current_string_len));

            current_string_start += current_string_len + delimiter_len;
        }
    }

    if (current_string_start < str.count) {
        string_array_push(&result, string_from_data(str.data + current_string_start, str.count - current_string_start));
    }

    return result;
}

ssize_t string_starts_at(string str, string substr)
{
    ssize_t position = -1;

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
    if (str->count == 0) {
        return;
    }

    const char *trimmable_characters = "\n\r ";

    bool is_trimmable_character = false;
    size_t trim_position = 0;
    for (size_t i = 0; i < str->count; i++) {
        for (size_t y = 0; y < strlen(trimmable_characters); y++) {
            if (str->data[i] == trimmable_characters[y]) {
                is_trimmable_character = true;
                break;
            }
        }

        trim_position = i;
        if (is_trimmable_character == false) {
            break;
        }

        is_trimmable_character = false;
    }

    if (trim_position != 0) {
        str->data += trim_position;
        str->count -= trim_position + 1;
    }
}

void string_trim_end(string *str)
{
    if (str->count == 0) {
        return;
    }

    const char *trimmable_characters = "\n\r ";

    bool is_trimmable_character = false;
    size_t trim_position = 0;
    for (size_t i = str->count - 1; i > 0; i--) {
        for (size_t y = 0; y < strlen(trimmable_characters); y++) {
            if (str->data[i] == trimmable_characters[y]) {
                is_trimmable_character = true;
                break;
            }
        }

        trim_position = i;
        if (is_trimmable_character == false) {
            break;
        }

        is_trimmable_character = false;
    }

    if (trim_position != 0) {
        str->count = trim_position + 1;
    }
}

void string_trim(string *str)
{
    string_trim_start(str);
    string_trim_end(str);
}

string string_substring(string str, size_t start, size_t end)
{
    string result;

    result.data = str.data += start;
    result.count = str.count - start;
    if (end == 0) {
        return result;
    }

    result.count -= str.count - end;

    return result;
}
