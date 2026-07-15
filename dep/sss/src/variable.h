#ifndef VARIABLE_H
#define VARIABLE_H

#include "../../string/src/string.h"

typedef struct {
    string raw;
} Variable;

bool variable_string(const Variable *var, string *string);

#endif // VARIABLE_H
