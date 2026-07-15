#include "variable.h"
#include <stdlib.h>

variable *variable_create(string string)
{
    variable *result = malloc(sizeof(variable));
    result->raw.data = string.data;
    result->raw.count = string.count;

    return result;
}

void variable_free(variable *variable)
{
    free(variable);
}

bool variable_string(const variable *var, string *string)
{
    if (var == NULL) {
        return false;
    }

    string->data = var->raw.data;
    string->count = var->raw.count;

    return true;
}
