#include <fcntl.h>
#include <unistd.h>

#include "../../tests.h"
#include "../../../src/http/response.h"

void test_response_simple_ok_is_valid(TestCaseOutput *output)
{
    Response *response = response_create();

    string_array lines = string_split(response_to_string(response), "\r\n");
    string statusLine = lines.items[0];

    string_trim(&statusLine);
    test_cstring_is_equal_to_string(output, "HTTP/1.1 200 OK", statusLine);

    response_free(response);
    string_array_free(lines);
}
