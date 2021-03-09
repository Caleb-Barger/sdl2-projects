#include "display.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
uint32_t* color_buffer = NULL;
SDL_Texture* color_buffer_texture = NULL;
int window_width = 800;
int window_height = 600;

void clear_color_buffer(uint32_t color) {
	for (int y=0; y<window_height;y++) {
		for (int x=0; x<window_width;x++) {
			color_buffer[(window_width*y)+x] = color;
		}
	}
}

void render_color_buffer(void) {
	/* update the texture to match the color buffer */	
	SDL_UpdateTexture(
		color_buffer_texture,
		NULL,
		color_buffer,
		(int)(window_width * sizeof(uint32_t))
	);

	/* update the renderer with the new texture */
	SDL_RenderCopy(
		renderer,
		color_buffer_texture,
		NULL,
		NULL
	);
}

int setup(void) {
	/* display setup */
	SDL_Init(SDL_INIT_EVERYTHING);

	window = SDL_CreateWindow(
		NULL,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		window_width,
		window_height,
		SDL_WINDOW_BORDERLESS
	);

	if(!window) {
		printf("%s\n", SDL_GetError());
		return 0;
	}

	renderer = SDL_CreateRenderer(window, -1, 0);

	if(!renderer) {
		printf("%s\n", SDL_GetError());
		return 0;
	}
	
	/* initalize color buffer */	
	color_buffer = (uint32_t*) malloc(sizeof(uint32_t)*window_width*window_height);

	if(!color_buffer) {
		printf("Could not init color buffer\n");
		return 0;
	}
	
	/* create a color buffer texture */
	color_buffer_texture = SDL_CreateTexture(
		renderer,
		SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING,
		window_width,
		window_height
	);

	return 1;
}

void cleanup(void) {
	/* free resources */
	free(color_buffer);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);	
	SDL_Quit();
}
