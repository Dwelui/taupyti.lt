#ifndef VARIABLE_H
#define VARIABLE_H

#include "../../string/src/string.h"

typedef struct {
    string rawData;
} Variable;

bool variableString(Variable *var, string *string);

#endif // VARIABLE_H
