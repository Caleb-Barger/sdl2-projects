#include "display.h"
#include "vec.h"

extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern uint32_t* color_buffer;
extern SDL_Texture* color_buffer_texture;
extern int window_width;
extern int window_height;

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
