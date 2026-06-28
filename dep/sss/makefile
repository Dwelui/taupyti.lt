CFLAGS = -Wall -Wextra -g

all: build/libsss.a

build_dir:
	@mkdir -p build

build/http.o: src/http/request.c | build_dir
	gcc $(CFLAGS) -c $< -o $@

build/route.o: src/route.c | build_dir
	gcc $(CFLAGS) -c $< -o $@

build/kernel.o: kernel.c | build_dir
	gcc $(CFLAGS) -c $< -o $@

build/libsss.a: build/http.o build/route.o build/kernel.o | build_dir
	@ar rcs $@ $^

##### Tests #####
build/libtest.a: | build_dir
	@make -C dep/test
	@cp dep/test/build/libtest.a build/libtest.a

build/test_request.o: tests/unit/http/test_request.c | build_dir
	gcc $(CFLAGS) -c $< -o $@

build/tests.o: tests/main.c | build_dir
	gcc $(CFLAGS) -c $< -o $@

tests: build/tests.o build/test_request.o build/libsss.a
	@gcc $^ -o build/tests

test: tests
	@./build/tests
