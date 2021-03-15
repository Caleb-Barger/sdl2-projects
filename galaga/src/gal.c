/* galaga clone by caleb barger written with SDL2 03/08/21 */

#define SHIP_SPEED 10
#define ENEMY_SPEED 1
#define BULLET_SPEED 3
#define BULLET_LIMBO -31
#define ENEMY_LIMBO -199

#include "display.h"
#include "imgldr.h"

int is_running = 0;
int can_fire = 0;
int enemy_dir = 0;
uint32_t delta = 0;
uint32_t time_passed = 0;

SDL_Point bullet = {0, 0};

void update_bullet(void) {
	if (bullet.y < window_height && bullet.y > 0)
		bullet.y -= BULLET_SPEED;
	else { 
		bullet.y = BULLET_LIMBO;
		can_fire = 1;
	}
}

void draw_bullet(void) {
	draw_line(
	bullet.x, 
	bullet.y,
	bullet.x,
	bullet.y-(player_r.h/2),
 	0xFFFFFFFF);
}

void fire(void) {
	bullet.x = player_r.x+18;
	bullet.y = player_r.y-5;
	can_fire = 0;
}

void render(void) {
	clear_color_buffer(0xFF000000);
	draw_stars(); 
	draw_bullet();
	render_color_buffer(); 
	draw_player(); 
	draw_enemy();
	SDL_RenderPresent(renderer); 
}

void process_input(void) {
	SDL_Event e;
	SDL_PollEvent(&e);
	
	switch(e.type) {
		case SDL_QUIT:
			is_running = 0;
			break;
		case SDL_KEYUP:
			if (e.key.keysym.sym == SDLK_ESCAPE)
				is_running = 0;
			if (e.key.keysym.sym == SDLK_RIGHT)
				player_r.x += SHIP_SPEED; 
			if (e.key.keysym.sym == SDLK_LEFT)
				player_r.x -= SHIP_SPEED;
			if (e.key.keysym.sym == SDLK_SPACE) {
				if (can_fire) fire();
			}
			break;
	}
}

void debug_info(void) {
	if (time_passed % 500 == 0) {
		printf("\n====================\n");	
		//printf("Player pos: (%d, %d)\n", player_r.x, player_r.y);
		//printf("Bullet pos: (%d, %d)\n", bullet.x, bullet.y);
		printf("Enemy pos: (%d, %d)\n", enemy_r.x, enemy_r.y);
		printf("Enemy state: %d\n", enemy_dir);
	}
}

void update_enemy() {
	if (SDL_PointInRect(&bullet, &enemy_r)) enemy_r.x = ENEMY_LIMBO;
	if (enemy_r.x + ENEMY_SPEED + enemy_r.w > window_width) 
		enemy_dir = !enemy_dir;
	else if (enemy_r.x - ENEMY_SPEED - enemy_r.w < 0)
		enemy_dir = !enemy_dir;
	if ((SDL_GetTicks() % 3) == 0) {
		switch (enemy_dir) {
			case 0:
				enemy_r.x += ENEMY_SPEED;
				break;
			case 1:
				enemy_r.x -= ENEMY_SPEED;
		}
	}
}

void update(void) {
	delta = SDL_GetTicks() - time_passed;
	time_passed = SDL_GetTicks();
	update_stars();
	update_bullet();
	update_enemy();
	debug_info();
}

int setup(void) {
	SDL_Init(SDL_INIT_EVERYTHING);

	window = SDL_CreateWindow(
		NULL,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		window_width,
		window_height,
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
	
	color_buffer = (uint32_t*) malloc(sizeof(uint32_t)*window_width*window_height);

	if(!color_buffer) {
		printf("Could not init color buffer\n");
		return 0;
	}
	
	color_buffer_texture = SDL_CreateTexture(
		renderer,
		SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING,
		window_width,
		window_height
	);
	
	if (!init_player()) {
		printf("%s\n", SDL_GetError());
		return 0;
	}

	if (!init_enemy()) {
		printf("%s\n", SDL_GetError());
		return 0;
	}

	/* initalize the stars */
	for (int i=0; i < STAR_COUNT; i++) {
		stars[i].x = rand() % window_width;
		stars[i].y = rand() % window_height;
	}

	// init_stars();

	return 1;
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
