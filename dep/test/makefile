CFLAGS = -Wall -Wextra -g

all: build/libtest.a

clear:
	@rm -rf build

build_dir:
	@mkdir -p build

build/test.o: src/test.c | build_dir
	gcc $(CFLAGS) -c $< -o $@

build/libtest.a: build/test.o | build_dir
	@ar rcs $@ $^
