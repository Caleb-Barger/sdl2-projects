#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#define FONT_SIZE 10

struct idd_status_t {
	SDL_Texture* texture;  	
	SDL_Rect r;
	int integ; 
	int is_suspended;
	int is_processing;
	int computation_left;
};

struct node_t {
	struct idd_status_t* dat;
	struct node_t* next;
};

struct game_state_t {
	int ram_usage;
	int volit_level;
	int n_offloaded_conns; 
	int cpu_usage;
};

SDL_Color color = {0x00,0xFF,0x00}; 
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
struct node_t* h = NULL;
int sel = 0;

void cleanup(void) {

	while(h->next) {
		SDL_DestroyTexture(h->dat->texture);
		printf("destroying texture\n");
		
		free(h->dat);
		printf("freed data \n");

		struct node_t* temp = h;
		h = h->next;
		printf("set h to h-> next\n");

		free(temp); 
		printf("freed prev h\n");
	}

	free(h);
	printf("freeing the final head\n");
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_Quit();
	SDL_Quit();
}

int update_iddstatus_surface(TTF_Font* font, SDL_Surface** font_surface, char* text) {
	if(!(*font_surface=TTF_RenderText_Solid(font, text, color))) {
		printf("%s\n", TTF_GetError());
		return 0;
	}
	return 1;
}

int set_iddstatus_texture(struct idd_status_t* is, SDL_Surface* font_surface) {
	SDL_Texture* font_texture = SDL_CreateTextureFromSurface(renderer, font_surface);
	if (!font_texture) {
		printf("%s\n", SDL_GetError());
		return 0;
	}

	is->texture = font_texture;
	
	return 1;
}	

void set_iddstatus_r_and_pos(struct node_t* n, int multiplier) {
	if (n->dat->texture) printf("texture exists!");
	SDL_QueryTexture(n->dat->texture, NULL, NULL, &n->dat->r.w, &n->dat->r.h);
	n->dat->r.w *= 3;
	n->dat->r.h *= 3;
	int xmultiplier = multiplier % 2;
	n->dat->r.x = xmultiplier*n->dat->r.w; 
	if (!xmultiplier) multiplier--;
	n->dat->r.y = multiplier*n->dat->r.h;
}

void initalize_font_textures( TTF_Font* font, SDL_Surface* font_surface,
	size_t n_font_textures) {
	
	if (!h)	{
		h  = (struct node_t*) malloc(sizeof(struct node_t)); 
		h->dat = (struct idd_status_t*) malloc(sizeof(struct idd_status_t));
		printf("we allocated a new node!\n");
		printf("size of node & dat: %ld & %ld \n", sizeof(*h), sizeof(*h->dat));
	}

	struct node_t* curr;
	curr = h;
	char buffer [50];		
	for (int i=0; i<n_font_textures; i++) {
		memset(buffer, 0, 50);
		sprintf(buffer, "D%d [OK] => ", rand());
		printf("fmt string created?!\n");
		update_iddstatus_surface(font, &font_surface, buffer);
		printf("font surface updated.\n");
		set_iddstatus_texture(curr->dat, font_surface);  
		printf("texture set for curr.\n");
		set_iddstatus_r_and_pos(curr, i);
		printf("r and pos updated.\n");
		curr->next = (struct node_t*) malloc(sizeof(struct node_t)); 
		curr->next->dat = (struct idd_status_t*) malloc(sizeof(struct idd_status_t));
		printf("we allocated a new \"next\" node!\n");
		
		curr = curr->next;
		printf("set curr to curr->next\n");
	}
}

int init(void) {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("%s\n", SDL_GetError());
		return 0;
	}

	if (SDL_CreateWindowAndRenderer(
		800,
		600,
		SDL_WINDOW_BORDERLESS,
		&window,
		&renderer) < 0) {
		printf("%s\n", SDL_GetError());
		return 0;
	}

	if (TTF_Init() < 0) {
		printf("%s\n", TTF_GetError());
		return 0;
	}

	TTF_Font* font = TTF_OpenFont("coolfont.ttf", FONT_SIZE);
	if (!font) {
		printf("%s\n", TTF_GetError());
		return 0;
	}

	SDL_Surface* font_surface = NULL;

	initalize_font_textures(font, font_surface, 10);

	TTF_CloseFont(font);

	return 1;
}

void render(void) {
	SDL_RenderClear(renderer);
	struct node_t* curr = h;

	int count = 0;
	while(curr->next) {
		if (sel == count) {
			SDL_SetRenderDrawColor(renderer, 0x5F, 0x00, 0x00, 0x00);
			SDL_RenderFillRect(renderer, &curr->dat->r);
		}

		SDL_RenderCopy(renderer, curr->dat->texture, NULL, &curr->dat->r);
		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);

		curr = curr->next;
		count++;
	}

	SDL_RenderPresent(renderer);

}

int proc_input(void) {
	SDL_Event e;
	SDL_PollEvent(&e);
	
	if (e.type == SDL_QUIT) return 0; 
	else if (e.type == SDL_KEYDOWN &&  e.key.keysym.sym == SDLK_ESCAPE)
		return 0;
	else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_DOWN) {
		sel = (++sel % 10); //TODO fix this
	}

	return 1;
}

int main(void) {
	if (init()) {

		while(1) {
			if(!proc_input()) break;
			render();
		}
	}

	cleanup();	

	return 0;
}
