#include <SDL2/SDL.h>
#include <math.h>

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
	SDL_UpdateTexture(
		color_buffer_texture,
		NULL,
		color_buffer,
		(int)(window_width * sizeof(uint32_t))
	);

	SDL_RenderCopy(
		renderer,
		color_buffer_texture,
		NULL,
		NULL
	);
}

void draw_pixel(int x, int y, uint32_t color) {
	if (x > 0 && y > 0 && x <= window_width && 
		y <= window_height) {
		color_buffer[(window_width*y)+x] = color;
	}
}

void draw_line(int x1, int y1, int x2, int y2, uint32_t color) {
	// DDA algorithm
	int step; 
	float dx = (x2 - x1), x;
	float dy = (y2 - y1), y;

	if (abs(dx) >= abs(dy))
		step = abs(dx);
	else
		step = abs(dy);

	dx /= step;
	dy /= step;
	x = x1;
	y = y1;

	for (int i=1; i<=step; i++) {
		draw_pixel((int)x, (int)y, color);
		x += dx;
		y += dy;
	}
}
int setup(void) {
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
	
	color_buffer = (uint32_t*) malloc(sizeof(uint32_t)*window_width*window_height);

	if(!color_buffer) {
		printf("Could not init color buffer\n");
		return 0;
	}
	
	color_buffer_texture = SDL_CreateTexture(
		renderer,
		SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING,
		window_width,
		window_height
	);
	
	return 1;
}

int proc_input(void) {
		SDL_Event e;
		SDL_PollEvent(&e);

		switch(e.type) {
			case SDL_KEYDOWN:
				if (e.key.keysym.sym == SDLK_ESCAPE) return 0;
				break;
		}

	return 1;
}

void update(void) {
}

void render(void) {
	clear_color_buffer(0x00000000);
	render_color_buffer(); 
	SDL_RenderPresent(renderer);
}

void house_cleaning(void) {
	free(color_buffer);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);	
	SDL_Quit();
}

int* rot(int w, int h, int* mata) {
	int* matb = malloc(sizeof(int)*w*h);

	for (int by=0; by<h; by++) { 				
		for (int ax=by, ay=h-1, bx=0; ay>-1; ay--, bx++) {
			matb[(by*w)+bx] = mata[(ay*w)+ax];
		}
	}

	memcpy(mata, matb, sizeof(int)*w*h);
	free(matb);
	
	return mata;
}

int main(void) {
	int is_running = 0;
	
	if (setup()) is_running = 1;
	
	while(is_running) {
		if(!proc_input()) is_running = 0;
		update();
		render();
	}
	
	house_cleaning();

	return 0;
}
