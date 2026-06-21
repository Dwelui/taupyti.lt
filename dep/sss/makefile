CFLAGS = -Wall -Wextra -g

http.o: src/http/request.c
	gcc $(CFLAGS) -c src/http/request.c -o build/http.o

unit_tests.o: tests/unit/unit_tests.c
	gcc $(CFLAGS) -c tests/unit/unit_tests.c -o build/unit_tests.o

test_request.o: tests/unit/http/test_request.c
	gcc $(CFLAGS) -c tests/unit/http/test_request.c -o build/test_request.o

tests.o: tests/tests.c
	gcc $(CFLAGS) -c tests/tests.c -o build/tests.o

test_case.o: tests/test_case.c
	gcc $(CFLAGS) -c tests/test_case.c -o build/test_case.o

build:
	mkdir -p build

tests: tests.o test_case.o unit_tests.o test_request.o http.o build
	gcc build/tests.o build/test_case.o build/unit_tests.o build/test_request.o build/http.o -o build/tests
