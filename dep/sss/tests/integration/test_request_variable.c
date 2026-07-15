#include "../tests.h"
#include "../../src/variable.h"
#include "../../src/http/request.h"

void test_request_get_variable_from_body(TestCaseOutput *output)
{
    Request *request = requestFromFixturePath("tests/fixtures/http/valid_post_form_1_urlencoded.http");

    variable *fooVariable = request_body_get(request, "foo");
    test_is_null(output, fooVariable, "failed to find 'foo' variable");

    string name = string_empty();
    if (variable_string(fooVariable, &name) == false) {
        test_fail(output, "failed to get 'bar' value");
    }

    test_cstring_is_equal_to_string(output, "bar", name);

    request_free(request);
    variable_free(fooVariable);
}
