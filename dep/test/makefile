CFLAGS = -Wall -Wextra -g

build:
	mkdir -p build

build/test_case.o: src/test_case.c | build
	gcc $(CFLAGS) -c $< -o $@

build/libtest.a: build/test_case.o | build
	@ar rcs $@ $^

all: build/libtest.a
