CFLAGS = -Wall -Wextra -g

build: build/default_contoller.o build/main.o build/libsss.a | build_dir
	@gcc $^ -o build/taupyti.lt

build_dir:
	@mkdir -p build

build/libsss.a: | build_dir
	@make -C dep/sss all
	@cp dep/sss/build/libsss.a build/libsss.a

build/default_contoller.o: src/controller/default_controller.c | build_dir
	gcc $(CFLAGS) -c $< -o $@

build/main.o: main.c | build_dir
	gcc $(CFLAGS) -c $< -o $@

run: build
	clear
	@./build/taupyti.lt

clear:
	rm -rf build
