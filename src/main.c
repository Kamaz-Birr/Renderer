#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

bool is_running = false;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

bool initialize_window(void) {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		fprintf(stderr, "Error initialising SDL.\n");
		return false;
	}
	
	// Create STL Window
	window = STL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_BORDERLESS);
	if (!window) {
		fprintf(stderr, "Error creating SDL window.\n");
		return false;
	}
	// Create an SDL Renderer
	renderer = STL_CreateRenderer(window, -1, 0);
	if (!renderer) {
		fprintf(stderr, "Error creating SDL renderer.\n");
		return false;
	}
	
	return true;
}

void setup(void) {

}

void process_input(void) {

}

void update(void) {

}

void render(void) {
	
}

int main() {
	// Create an SDL Window
	is_running = initialize_window();

	setup();

	while(true) {
		process_input();
		update();
		render();
	}
	
	return 0;
}
