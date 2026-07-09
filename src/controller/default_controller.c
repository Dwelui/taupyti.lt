#include "default_controller.h"
#include <stdio.h>
#include <stdlib.h>

int default_controller_index(const Request *req, Response *res)
{
    res->template_path = "index.html";

    return 0;
}

int default_controller_store(const Request *req, Response *res)
{
    Variable *nameVar = request_body_get(req, "name");
    string name = string_empty();
    if (variableString(nameVar, &name) == false) {
        printf("failed to get product name\n");
        return -1; // INFO: error cuz the name is required!
    }

    char *nameCstr = string_to_cstring(name);
    printf("product name: %s\n", nameCstr);
    free(nameCstr);

    res->template_path = "index.html";

    return 0;
}
