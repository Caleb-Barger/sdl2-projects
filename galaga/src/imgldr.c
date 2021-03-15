#include "imgldr.h"
#include "display.h"

SDL_Texture* player_texture = NULL;
SDL_Surface* player_surface = NULL;
SDL_Rect player_r = {0, 0, 0, 0};

void set_player_ckey(uint32_t color) {
	SDL_SetColorKey(player_surface, SDL_TRUE, 0xFF000000);
}

int load_player_sat(void) {
	SDL_Surface* player_surface = SDL_LoadBMP("./image/ship.bmp"); 
	if (!player_surface) return 0;
	set_player_ckey(0xFF000000);
	player_texture = SDL_CreateTextureFromSurface(renderer, player_surface);
	if (!player_texture) return 0;
	return 1;
}

void init_player_rect(void) {
	int w, h;
	SDL_QueryTexture(player_texture, NULL, NULL, &w, &h);

	player_r.w = w*SHIP_SCALE; 
	player_r.h = h*SHIP_SCALE;
	player_r.x = window_width/2;
	player_r.y = window_height - player_r.h*SHIP_SCALE;
}

int init_player(void) {
	if(!load_player_sat())
		return 0;
	init_player_rect();

	SDL_FreeSurface(player_surface);

	return 1;
}
