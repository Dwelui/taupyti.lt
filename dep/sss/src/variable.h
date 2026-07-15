#ifndef VARIABLE_H
#define VARIABLE_H

#include "../../string/src/string.h"

typedef struct {
    string raw;
} variable;

bool variable_string(const variable *var, string *string);

#endif // VARIABLE_H
