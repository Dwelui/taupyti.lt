CFLAGS = -Wall -Wextra -g

all: build/libtest.a

build_dir:
	@mkdir -p build

build/test_case.o: src/test_case.c | build_dir
	gcc $(CFLAGS) -c $< -o $@

build/libtest.a: build/test_case.o | build_dir
	@ar rcs $@ $^
