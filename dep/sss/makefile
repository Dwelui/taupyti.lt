http.o: src/http/request.c
	gcc -c src/http/request.c -o http.o

unit_tests.o: tests/unit/unit_tests.c
	gcc -c tests/unit/unit_tests.c -o unit_tests.o

test_request.o: tests/unit/http/test_request.c
	gcc -c tests/unit/http/test_request.c -o test_request.o

tests.o: tests/tests.c
	gcc -c tests/tests.c -o tests.o

test_case.o: tests/test_case.c
	gcc -c tests/test_case.c -o test_case.o

tests: tests.o test_case.o unit_tests.o test_request.o http.o
	gcc tests.o test_case.o unit_tests.o test_request.o http.o -o tests_final
