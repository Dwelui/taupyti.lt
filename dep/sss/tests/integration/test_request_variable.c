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
    variable_free(fooVariable);

    variable *xVariable = request_body_get(request, "x");
    test_is_null(output, xVariable, "failed to find 'x' variable");

    string x = string_empty();
    if (variable_string(xVariable, &x) == false) {
        test_fail(output, "failed to get 'x' value");
    }

    test_cstring_is_equal_to_string(output, "1", x);
    variable_free(xVariable);

    request_free(request);
}
