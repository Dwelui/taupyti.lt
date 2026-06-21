#include <stdio.h>

#include "unit/unit_tests.h"

int main()
{
    printf("Running unit tests...\n");
    if (run_unit_tests() == 0) {
        printf("[PASS] Unit tests\n");
    } else {
        printf("[FAIL] Unit tests\n");
    }
}
