/* galaga clone by caleb barger written with SDL2 03/08/21 */

#include "display.h"
#include "imgldr.h"

double ship_speed = 7.0;

int is_running = 0;

void render(void) {
	clear_color_buffer(0xFF000000);
	draw_stars(); /* draw stars to color buffer */
	render_color_buffer(); /* display the color buff */
	draw_player(); /* draw the ship to the screen */
	SDL_RenderPresent(renderer); /* dispay the color_buffer_texture */
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
				player_r.x -= ship_speed; //* time_since_last_frame;
			if (e.key.keysym.sym == SDLK_RIGHT)
				player_r.x += ship_speed; //* time_since_last_frame;
			//if (e.key.keysym.sym == SDLK_SPACE) {
			//	fire();
			//}
			//break;
	}
}

void update(void) {
	update_stars();
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
	
	if (!init_player()) {
		printf("%s\n", SDL_GetError());
		return 0;
	}

	/* initalize the stars */
	for (int i=0; i < STAR_COUNT; i++) {
		stars[i].x = rand() % window_width;
		stars[i].y = rand() % window_height;
	}

	// init_stars();

	return 1;
}

int main(void) {
	is_running = setup();
	
	while(is_running) {
		process_input();
		update();
		render();
	}
	
	cleanup();

	return 0;
}
