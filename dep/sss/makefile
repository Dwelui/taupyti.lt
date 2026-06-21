CFLAGS = -Wall -Wextra -g

build:
	mkdir -p build

build/http.o: src/http/request.c | build
	gcc $(CFLAGS) -c $< -o $@

build/unit_tests.o: tests/unit/unit_tests.c | build
	gcc $(CFLAGS) -c $< -o $@

build/test_request.o: tests/unit/http/test_request.c | build
	gcc $(CFLAGS) -c $< -o $@

build/tests.o: tests/tests.c | build
	gcc $(CFLAGS) -c $< -o $@

build/test_case.o: tests/test_case.c | build
	gcc $(CFLAGS) -c $< -o $@

tests: build/tests.o build/test_case.o build/unit_tests.o build/test_request.o build/http.o
	@gcc $^ -o build/tests
