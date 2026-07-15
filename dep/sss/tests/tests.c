#include "../../test/src/test.h"
#include "tests.h"

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

TestCase unitTests[] = {
    TEST_CASE_REGISTER(test_request_parse_version),
    TEST_CASE_REGISTER(test_request_parse_method),
    TEST_CASE_REGISTER(test_request_parse_path),
    TEST_CASE_REGISTER(test_request_parse_path_2),
};

TestCase integrationTests[] = {
    TEST_CASE_REGISTER(test_request_get_variable_from_body),
};

int main()
{
    test_run_tests("Unit", unitTests, sizeof(unitTests) / sizeof(unitTests[0]));
    test_run_tests("Integration", integrationTests, sizeof(integrationTests) / sizeof(integrationTests[0]));
}

char *file_read(const char *path)
{
    int file_fd = open(path, O_RDONLY);
    if (file_fd == -1) {
        perror("file_read open");
        return NULL;
    }

    size_t buf_len = 1024;
    char *buf = malloc(buf_len * sizeof(char));
    ssize_t bytes_read = read(file_fd, buf, buf_len - 1);
    if (bytes_read == -1) {
        perror("file_read read");
        return NULL;
    }

    buf[bytes_read] = '\0';

    close(file_fd);

    return buf;
}

Request *requestFromFixturePath(const char *path)
{
    char *input = file_read(path);
    Request *result = request_create(input, sizeof(input));

    free(input);
    return result;
}
