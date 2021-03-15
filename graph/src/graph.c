#include <SDL2/SDL.h>
#include <math.h>


/* 
	Sin(a) => o/h // y
		y = sin(a) * h  
			h => sqrt(x*x + y*y) 
		
		y = (y/sqrt(x*x + y*y)) * sqrt(x*x + y*y)
				
	Cos(a) => a/h // x
*/

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
		//x += dx / sin(dx);
		x += dx;
		//y += dy / cos(dy);
		y += (dy/sqrt(dx*dx + dy*dy)) * sqrt(dx*dx + dy*dy);
	}
}

int main(void) {
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
	int is_running = 1;
	while(is_running) {
		clear_color_buffer(0xFFFFFFFF);
		draw_line(0, window_height, window_width, 0, 0xFF000000);
		render_color_buffer(); 
		SDL_RenderPresent(renderer);
		SDL_Delay(5000);
		is_running = 0;
	}

	free(color_buffer);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);	
	SDL_Quit();

	return 0;
}
