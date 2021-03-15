#include "display.h"
#include "imgldr.h"

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

void draw_pixel(int x, int y, uint32_t color) {
	if (x > 0 && y > 0 && x <= window_width && 
		y <= window_height) {
		color_buffer[(window_width*y)+x] = color;
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

void cleanup(void) {
	/* free resources */
	free(color_buffer);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);	
	SDL_Quit();
}

void update_stars(void) {
	for (int i=0; i < STAR_COUNT; i++) {
		stars[i].y += WORLD_SPEED;
		if (stars[i].y > window_height)  {
			stars[i].y = 0;
			stars[i].x = rand() % window_width;
		}
	}
}

void draw_stars(void) {
	for (int i=0; i < STAR_COUNT; i++) {
		draw_pixel(stars[i].x, stars[i].y, 0xFFFFFFFF);
	}
}

void draw_player(void) {

	/* draw the ship to the screen */
	SDL_RenderCopy(
		renderer,
		player_texture,
		NULL,
		&player_r
	);
}
