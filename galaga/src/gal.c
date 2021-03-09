/* galaga clone by caleb barger written with SDL2 03/08/21 */

#include "display.h"

int is_running = 0;

void render(void) {
	clear_color_buffer(0xFFFFFFFF);

	render_color_buffer();

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
			break;
	}
}

void update(void) {

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


