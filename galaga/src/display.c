#include "display.h"
#include "imgldr.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
uint32_t* color_buffer = NULL;
SDL_Texture* color_buffer_texture = NULL;


vec2_t stars[STAR_COUNT]; //TODO !!!!!!!

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
	SDL_DestroyTexture(player_texture);
	SDL_DestroyTexture(enemy_texture);
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
	uint32_t star_color = 0xFFFFFFFF;
	 
	for (int i=0; i < STAR_COUNT; i++) {
		if ((rand() % 3) >= 1) star_color = 0xFFFF0000 + i;
		else if ((rand() % 3) >= 2) star_color = 0xFF00FF00 + i;
		else star_color = 0xFF0000FF + i;
		draw_pixel(stars[i].x, stars[i].y, star_color);
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

void draw_enemy(void) {
	/* draw the ship to the screen */
	SDL_RenderCopy(
		renderer,
		enemy_texture,
		NULL,
		&enemy_r
	);
}
