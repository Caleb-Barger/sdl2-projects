#ifndef IMGLDR_H 
#define IMGLDR_H

#include <SDL2/SDL.h>

extern SDL_Texture* player_texture;
extern SDL_Rect player_r;
extern SDL_Texture* enemy_texture;
extern SDL_Rect enemy_r;

int init_player(void);
int init_enemy(void);
	
#endif
