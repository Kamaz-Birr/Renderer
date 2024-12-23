#include "display.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Texture* color_buffer_texture = NULL;

uint32_t* color_buffer = NULL;
int window_width = 800;
int window_height = 600;

bool initialize_window(void) {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		fprintf(stderr, "Error initialising SDL.\n");
		return false;
	}
	
	// Use SDL to query the fullscreen dimensions of the host device
	SDL_DisplayMode display_mode;
	SDL_GetCurrentDisplayMode(0, &display_mode);

	window_width = display_mode.w;
	window_height = display_mode.h;

	// Create STL Window
	window = SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_width, window_height, SDL_WINDOW_BORDERLESS);
	if (!window) {
		fprintf(stderr, "Error creating SDL window.\n");
		return false;
	}
	// Create an SDL Renderer
	renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer) {
		fprintf(stderr, "Error creating SDL renderer.\n");
		return false;
	}

	SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
	
	return true;
}

// Renders the color buffer array in a texture and displays it
void render_color_buffer(void) {
	SDL_UpdateTexture(color_buffer_texture, NULL, color_buffer, (int)(window_width * sizeof(uint32_t)));
	SDL_RenderCopy(renderer, color_buffer_texture, NULL, NULL);
}

void clear_color_buffer(uint32_t color) {
	for(int y = 0; y < window_height; y++) {
		for(int x = 0; x < window_width; x++) {
			color_buffer[(window_width * y) + x] = color;
		}
	}
}

void draw_grid(void) {
	for(int y = 0; y < window_height; y++) {
		for(int x = 0; x < window_width; x++) {
			if(x % 10 == 0 || y % 10 == 0) {
				color_buffer[(window_width * y) + x] = 0xFF333333;
			}
		}
	}
}

void draw_pixel(int x, int y, uint32_t color) {
    if(x < window_width && y < window_height) {
        color_buffer[(window_width * y) + x] = color;
    }
}

void draw_rect(int x, int y, int width, int height, uint32_t color) {
	for(int i = 0; i < height; i++) {
		for(int j = 0; j < width; j++) {
			int y_axis = y + i;
			int x_axis = x + j;
			color_buffer[(window_width * y_axis) + x_axis] = color;
		}
	}
}

void destroy_window(void) {
	// Clean up.
	// Notice everything happens in the reverse order of creation.
	free(color_buffer);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

