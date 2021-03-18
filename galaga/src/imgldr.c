#include "imgldr.h"
#include "display.h"

SDL_Texture* player_texture = NULL;
SDL_Surface* player_surface = NULL;
SDL_Rect player_r = {0, 0, 0, 0};

SDL_Texture* enemy_texture = NULL; 
SDL_Surface* enemy_surface = NULL;
SDL_Rect enemy_r = { 0, 0, 0, 0};

void set_ck(SDL_Surface* surface, uint32_t color) {
	SDL_SetColorKey(surface, SDL_TRUE, color);
}

int load_player_sat(void) {
	SDL_Surface* player_surface = SDL_LoadBMP("./image/ship.bmp"); 
	if (!player_surface) return 0;
	set_ck(player_surface, 0xFF000000);
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

int load_enemy_sat(void) {
	SDL_Surface* enemy_surface = SDL_LoadBMP("./image/blue_fighter.bmp"); 
	if (!enemy_surface) return 0;
	set_ck(enemy_surface, 0xFF000000);
	enemy_texture = SDL_CreateTextureFromSurface(renderer, enemy_surface);
	if (!enemy_texture) return 0;
	return 1;
}

void init_enemy_rect(void) {
	int w, h;
	SDL_QueryTexture(enemy_texture, NULL, NULL, &w, &h);

	enemy_r.w = w; 
	enemy_r.h = h;
	enemy_r.x = window_width/2;
	//enemy_r.y = 0 + enemy_r.h*1.5;
	enemy_r.y = window_height / 2 ;
}

int init_enemy(void) {
	if(!load_enemy_sat())
		return 0;
	init_enemy_rect();

	SDL_FreeSurface(enemy_surface);

	return 1;
}
