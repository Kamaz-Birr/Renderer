build:
	gcc -Wall -std=c99 ./src/*.c -o render

run:
	./render

clean:
	rm render
