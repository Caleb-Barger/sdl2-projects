#ifndef DISPLAY_H
#define DISPLAY_H

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern uint32_t* color_buffer;
extern SDL_Texture* color_buffer_texture;
extern int window_width;
extern int window_height;

void clear_color_buffer(uint32_t color);
void draw_pixel(int x, int y, uint32_t color);
void render_color_buffer(void);
void cleanup(void);

#endif
