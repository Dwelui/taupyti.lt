#include "../tests.h"
#include "../../src/variable.h"
#include "../../src/http/request.h"

void test_request_get_variable_from_body(TestCaseOutput *output)
{
    char *input = file_read("tests/fixtures/http/valid_get_1.http");
    Request *request = request_create(input, sizeof(input));

    Variable *nameVar = request_body_get(request, "name");
    string name = string_empty();
    if (variableString(nameVar, &name) == false) {
        test_fail(output, "failed to get product name");
    }

    test_cstring_is_equal_to_string(output, "milk", name);

    request_free(request);
}
