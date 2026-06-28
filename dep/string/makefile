CFLAGS = -Wall -Wextra -g

build_dir:
	@mkdir -p build

# build/libstring.a: | build_dir
# 	@ar rcs $@ $^
#
##### Tests #####
build/libtest.a: | build_dir
	@make -C ../test
	@cp ../test/build/libtest.a build/libtest.a

build/tests.o: tests/main.c | build_dir
	gcc $(CFLAGS) -c $< -o $@

build/test_string.o: tests/unit/test_string.c | build_dir
	gcc $(CFLAGS) -c $< -o $@

tests: build/tests.o build/test_string.o build/libtest.a
	@gcc $^ -o build/tests

test: tests
	@./build/tests
