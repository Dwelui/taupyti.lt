#ifndef TEST_CASE_H
#define TEST_CASE_H

#define TEST_CASE_REGISTER(fn) { #fn, fn }

typedef struct {
    const char *name;
    char *(*fn)(void);
} TestCase;

#endif // TEST_CASE_H
