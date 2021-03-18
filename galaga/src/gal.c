/* galaga clone by caleb barger written with SDL2 03/08/21 */

#define SHIP_SPEED 10
#define ENEMY_SPEED 1
#define BULLET_SPEED 3
#define BULLET_LIMBO -31
#define ENEMY_LIMBO -199
#define EXPLOSION_SIZE 500

#include "display.h"
#include "imgldr.h"

int is_running = 0;
int can_fire = 0;
int enemy_dir = 0;
uint32_t delta = 0;
uint32_t time_passed = 0;

SDL_Point bullet = {0, 0};

struct debre_t {
	SDL_Point pos;
	SDL_Point inc;
	uint32_t color;	
};

struct debre_t debre[EXPLOSION_SIZE];

// what would I like my explosion struct to have?
	// SDL_Point x and y pos
	// SDL_Point dest x and y pos
	// a color value (uin32_t)
	

// DDA works by incremnting x and y depending
// on the larger of the two deltas ( x y)
 

void explode(SDL_Rect* r) {
	memset(debre, 0, EXPLOSION_SIZE * sizeof(struct debre_t));
	for (int i=0; i<EXPLOSION_SIZE; i++) {
		uint32_t color;

	       	switch(rand() % 3) {
			case 0:
				color = 0xFFFF0000;
				break;
			case 1:
				color = 0xFF00FF00;
				break;
			case 2:
				color = 0xFF0000FF;
				break;
		}
		
		debre[i].color = color;
		debre[i].pos.x = r->x; debre[i].pos.y = r->y;

		int tarx = rand() % window_width;
		int tary = rand() % window_height;

		float dx = (tarx - r->x);
	       	float dy = (tary - r->y);
		float st;

		if (abs(dx) > dy) st = dx;
		else {
			st = dy;
		}
		
		dx /= st;
		dy /= st;

		debre[i].inc.x = (int)dx; debre[i].inc.y = (int)dy;
	}
}

void update_debre(void) {
	// look at all the debre and move
	for (int i=0; i<EXPLOSION_SIZE; i++) {
		debre[i].pos.x += debre[i].inc.x;
		debre[i].pos.y += debre[i].inc.y;
	}

	//TODO fix this 
	if (debre[0].pos.x > window_width || debre[0].pos.y > window_height || debre[0].pos.x < 0) memset(debre, 0, EXPLOSION_SIZE * sizeof(struct debre_t));
}

void draw_debre(void) {
	for (int i=0; i<EXPLOSION_SIZE; i++) 
		draw_pixel(debre[i].pos.x, debre[i].pos.y, debre[i].color);
}

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
	draw_debre();
	//draw_stars(); 
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
		case SDL_KEYDOWN:
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
	if (time_passed % 100 == 0) {
		printf("\n====================\n");	
		//printf("Player pos: (%d, %d)\n", player_r.x, player_r.y);
		//printf("Bullet pos: (%d, %d)\n", bullet.x, bullet.y);
		printf("debre 0 pos: (%d, %d)\n", debre[0].pos.x, debre[0].pos.y);
		//printf("Enemy state: %d\n", enemy_dir);
	}
}

void update_enemy() {

	if (SDL_PointInRect(&bullet, &enemy_r)) {
		explode(&enemy_r);
		enemy_r.x = ENEMY_LIMBO;
		bullet.y = BULLET_LIMBO;
	}

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
	update_debre();
	//debug_info();
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
