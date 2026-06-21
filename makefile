CFLAGS = -Wall -Wextra -g

build:
	mkdir -p build

build/libsss.a: dep/sss/build/libsss.a | build
	make -C dep/sss all
	cp dep/sss/build/libsss.a build/libsss.a

build/router.o: src/config/router.c | build
	gcc $(CFLAGS) -c $< -o $@

build/default_contoller.o: src/controller/default_controller.c | build
	gcc $(CFLAGS) -c $< -o $@

build/main.o: main.c | build
	gcc $(CFLAGS) -c $< -o $@

all: build/router.o build/default_contoller.o build/main.o build/libsss.a | build
	@gcc $^ -o build/taupyti.lt

run: all
	clear
	@./build/taupyti.lt
