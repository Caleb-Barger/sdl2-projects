#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 640

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

SDL_Texture* screen_texture = NULL;
SDL_Surface* screen_surf = NULL;
SDL_Surface* charsheet_surf = NULL;

SDL_Rect temp_r = {0, 0, 100, 100}; //TODO temp rm this

int setup(void) { SDL_Init(SDL_INIT_EVERYTHING);

	window = SDL_CreateWindow(
		NULL,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
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

	charsheet_surf = SDL_LoadBMP("asset/charsheet.bmp");
	if(!charsheet_surf) {
		printf("%s\n", SDL_GetError());
		return 0;
	}

	//SDL_SetColorKey(charsheet_surf, SDL_TRUE, 0x000000FF);
		
	// first create empty surface
	screen_surf = SDL_CreateRGBSurface(0, WINDOW_WIDTH, WINDOW_HEIGHT,
		32, 0, 0, 0, 0);   
	
	// initalize texture form empty surface
	//screen_texture = SDL_CreateTextureFromSurface(renderer, screen_surf);
	screen_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, 
			SDL_TEXTUREACCESS_STREAMING,
			WINDOW_WIDTH,
			WINDOW_HEIGHT
	);

	return 1;
}

int proc_input(void) {
	SDL_Event e;	
	SDL_PollEvent(&e);

	switch(e.type) {
	case SDL_KEYDOWN:
		if (e.key.keysym.sym == SDLK_ESCAPE) return 0;
	default: 
		break;
	}

	return 1;
}

void cleanup(void) {
	SDL_FreeSurface(charsheet_surf);
	SDL_FreeSurface(screen_surf);
	SDL_DestroyTexture(screen_texture);
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
}

void render(void) {
	// clear renderer
	SDL_RenderClear(renderer);

	// clear screen surface 
	SDL_FillRect(screen_surf, 
				NULL, //i.e. the whole surf
				0xFF000000
	);



	SDL_Rect clip_rect = {0, 0, 8, 8}; // TODO TEMP rm this
	//SDL_SetClipRect(charsheet_surf, &clip_rect); // this should be an "A" char

	// blit the charsheet "A" 
	SDL_BlitScaled(
		charsheet_surf,
		&clip_rect,	
		//NULL,
		screen_surf,
		//NULL
		&temp_r
	);

	SDL_UpdateTexture(screen_texture,
			NULL, // Area of texture to update 
			screen_surf->pixels,
			(int)(WINDOW_WIDTH * sizeof(uint32_t))
	);

	SDL_RenderCopy(
		renderer,
		screen_texture,
		NULL, // src rect
		NULL // dest rect
	);

	SDL_RenderPresent(renderer);
}

int main(void) {
	setup();
	int running = 1;	
	
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	while(running) {
		if(!proc_input()) running = 0; 
		// update()
		render();
	}

	cleanup();

	return 0;
}
