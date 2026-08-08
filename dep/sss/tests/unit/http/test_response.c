#include <fcntl.h>
#include <unistd.h>

#include "../../tests.h"
#include "../../../src/http/response.h"

void test_response_simple_ok_is_valid(TestCaseOutput *output)
{
    Response *response = response_create();

    string response_string = response_to_string(response);

    test_cstring_is_equal_to_string(output, "HTTP/1.1 200 OK\r\n\r\n", response_string);

    response_free(response);
    string_free(&response_string);
}
