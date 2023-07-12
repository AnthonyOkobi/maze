build:
	gcc -Wall -Werror -Wextra -pedantic ./src/*.c -o maze -lm -ldl `sdl2-config --cflags` `sdl2-config --libs`;

run:
	./maze;

clean:
	rm maze;
