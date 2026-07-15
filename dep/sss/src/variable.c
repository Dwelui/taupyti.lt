#include "variable.h"
#include <stdio.h>

bool variable_string(const variable *var, string *string)
{
    if (var == NULL) {
        return false;
    }

    string->data = var->raw.data;
    string->count = var->raw.count;

    return true;
}
