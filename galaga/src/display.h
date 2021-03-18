#ifndef DISPLAY_H
#define DISPLAY_H

#define STAR_COUNT 300
#define SHIP_SCALE 1.5
#define WORLD_SPEED 0.1

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "vec.h"

extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern uint32_t* color_buffer;
extern SDL_Texture* color_buffer_texture;
extern int window_width;
extern int window_height;
extern vec2_t stars[];

void clear_color_buffer(uint32_t color);
void draw_pixel(int x, int y, uint32_t color);
void draw_line(int x1, int y1, int x2, int y2, uint32_t color);
void render_color_buffer(void);
void cleanup(void);
void update_stars(void);
void draw_stars(void);
void draw_player(void);
void draw_enemy(void);


#endif
