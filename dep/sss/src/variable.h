#ifndef VARIABLE_H
#define VARIABLE_H

#include "../../string/src/string.h"

typedef struct {
    string raw;
} variable;

variable *variable_create(string string);
void variable_free(variable *variable);

bool variable_string(const variable *var, string *string);

#endif // VARIABLE_H
