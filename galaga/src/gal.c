/* galaga clone by caleb barger written with SDL2 03/08/21 */

#include "display.h"
#include "vec.h"

#define STAR_COUNT 300
#define MAX_BULLETS 100

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
uint32_t* color_buffer = NULL;
SDL_Texture* color_buffer_texture = NULL;

vec2_t stars[STAR_COUNT];
SDL_Rect bullets[MAX_BULLETS];
int bullet_counter = 0;

SDL_Texture* ship_texture = NULL;
SDL_Rect ship_r; 
float ship_speed = 5.0f;

int window_width = 800;
int window_height = 600;
float world_speed = 0.1f;

int is_running = 0;

void draw_stars(void) {

	for (int i=0; i < STAR_COUNT; i++) {
		stars[i].y += world_speed;

		if (stars[i].y > window_height)  {
			stars[i].y = 0;
			stars[i].x = rand() % window_width;
		}
			
		draw_pixel(stars[i].x, stars[i].y, 0xFFFFFFFF);
	}
}

void render(void) {

	/* set background to black */
	clear_color_buffer(0xFF000000);

	/* draw stars to color buffer */
	draw_stars();
	
	/* display the color buff */
	render_color_buffer();

	/* draw the ship to the screen */
	SDL_RenderCopy(
		renderer,
		ship_texture,
		NULL,
		&ship_r
	);

	/* dispay the color_buffer_texture */
	SDL_RenderPresent(renderer);
}

void process_input(void) {
	SDL_Event e;
	SDL_PollEvent(&e);
	
	switch(e.type) {
		case SDL_QUIT:
			is_running = 0;
			break;
		case SDL_KEYDOWN:
			if (e.key.keysym.sym == SDLK_ESCAPE)
				is_running = 0;
			if (e.key.keysym.sym == SDLK_LEFT)
				ship_r.x -= ship_speed; //* time_since_last_frame;
			if (e.key.keysym.sym == SDLK_RIGHT)
				ship_r.x += ship_speed; //* time_since_last_frame;

			break;
	}
}

void update(void) {
	draw_stars();

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
	
	/* load ship bmp */
	SDL_Surface* ship_surface = SDL_LoadBMP("./image/ship.bmp"); 

	if (!ship_surface) {
		printf("%s\n", SDL_GetError()); 
		return 0;
	}

	ship_texture = SDL_CreateTextureFromSurface(renderer, ship_surface);

	int w, h;
	SDL_QueryTexture(ship_texture, NULL, NULL, &w, &h);

	ship_r.w = w*1.5; 
	ship_r.h = h*1.5;
	ship_r.x = window_width/2;
	ship_r.y = window_height - ship_r.h*1.5;

	SDL_FreeSurface(ship_surface);

	/* initalize the stars */
	for (int i=0; i < STAR_COUNT; i++) {
		stars[i].x = rand() % window_width;
		stars[i].y = rand() % window_height;
	}

	return 1;
}

int main(void) {
	is_running = setup();
	
	while(is_running) {
		process_input();
		update();
		render();
	}
	
	SDL_DestroyTexture(ship_texture);
	cleanup();

	return 0;
}
