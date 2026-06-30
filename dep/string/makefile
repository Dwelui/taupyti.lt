CFLAGS = -fsanitize=address -O0 -Wall -Wextra -g

build: build/libstring.a

build_dir:
	@mkdir -p build

build/string.o: src/string.c | build_dir
	@gcc $(CFLAGS) -c $< -o $@

build/libstring.a: build/string.o | build_dir
	@ar rcs $@ $^

##### Tests #####
build/libtest.a: | build_dir
	@make -C ../test
	@cp ../test/build/libtest.a build/libtest.a

build/tests.o: tests/main.c | build_dir
	@gcc $(CFLAGS) -c $< -o $@

tests: build/tests.o build/libstring.a build/libtest.a
	@gcc  $(CFLAGS) $^ -o build/tests

test: tests
	@./build/tests

clear:
	@rm -rf build
