#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int BOARD_WIDTH = 5;
int BOARD_HEIGHT = 50;

#define BLOCK_WIDTH  3 
#define BLOCK_HEIGHT 3

struct vec2_t {
	int x;
	int y;
};

void print_map(int w, int h, int* map) {
	for (int i=0; i < w*h; i++) {
		if (i % w == 0) printf("\n");

		if (!map[i]) printf("  ");
		else 
			printf(" %d", map[i]);
		
	}

	printf("\n");
}

void map_onto(int* board, int* block, struct vec2_t* pos) {
	for (int y=0; y<BLOCK_HEIGHT; y++) {
		for (int x=0; x<BLOCK_WIDTH; x++) {
			board[((y+pos->y)*BOARD_WIDTH)+(x+pos->x)] = block[(y*BLOCK_WIDTH) + x];
		}	
	}
}

void clear_map(int* map, int w, int h) {
	for (int y=0; y<h; y++) {
		for (int x=0; x<w; x++) {
			map[(y*w) + x] = 0;
		}	
	}
}

int* rot(int w, int h, int* mata) {
	int* matb = malloc(sizeof(int)*w*h);

	for (int by=0; by<h; by++) { 				
		for (int ax=by, ay=h-1, bx=0; ay>-1; ay--, bx++) {
			matb[(by*w)+bx] = mata[(ay*w)+ax];
		}
	}

	memcpy(mata, matb, sizeof(int)*w*h);
	free(matb);
	
	return mata;
}


int main(void) {
	int seconds = 0, called = 0, interval = 2;
	clock_t t;
	t = clock();

	int posx = 0;
	int posy = 0;
	struct vec2_t pos = {posx, posy};

	int block[BLOCK_WIDTH*BLOCK_HEIGHT] = { 
		//'x', 'x', 'x', ' ', ' ', 'x', ' ', ' ', 'x', ' ', ' ', ' ', 'x', 'x', 'x', ' ', 'x', 'x', 'x', ' ', ' ', 'x', 'x', 'x', ' ', ' ', 'x', ' ', ' ', 'x', 'x', ' ', ' ', 'x', 'x', 'x', ' ', 'x', 'x', 'x', ' ', 'x', 'x', ' ',
	  	//'x', ' ', ' ', ' ', 'x', ' ', 'x', ' ', 'x', ' ', ' ', ' ', 'x', ' ', ' ', ' ', 'x', ' ', 'x', ' ', ' ', 'x', ' ', 'x', ' ', 'x', ' ', 'x', ' ', 'x', ' ', 'x', ' ', 'x', ' ', ' ', ' ', 'x', ' ', ' ', ' ', 'x', ' ', 'x',
	  	//'x', ' ', ' ', ' ', 'x', 'x', 'x', ' ', 'x', ' ', ' ', ' ', 'x', 'x', 'x', ' ', 'x', 'x', ' ', ' ', ' ', 'x', 'x', ' ', ' ', 'x', 'x', 'x', ' ', 'x', 'x', ' ', ' ', 'x', 'x', 'x', ' ', 'x', 'x', 'x', ' ', 'x', 'x', ' ',
	  	//'x', ' ', ' ', ' ', 'x', ' ', 'x', ' ', 'x', ' ', ' ', ' ', 'x', ' ', ' ', ' ', 'x', ' ', 'x', ' ', ' ', 'x', ' ', 'x', ' ', 'x', ' ', 'x', ' ', 'x', ' ', 'x', ' ', 'x', ' ', 'x', ' ', 'x', ' ', ' ', ' ', 'x', ' ', 'x',
	   	//'x', 'x', 'x', ' ', 'x', ' ', 'x', ' ', 'x', 'x', 'x', ' ', 'x', 'x', 'x', ' ', 'x', 'x', 'x', ' ', ' ', 'x', 'x', 'x', ' ', 'x', ' ', 'x', ' ', 'x', ' ', 'x', ' ', 'x', 'x', 'x', ' ', 'x', 'x', 'x', ' ', 'x', ' ', 'x'
		
		0, 1, 0,
		1, 1, 0,
		1, 0, 0		
	}; 

	int* board = (int*) malloc(BOARD_WIDTH*BOARD_HEIGHT*sizeof(int));
	//memset(board, 0, BOARD_WIDTH*BOARD_HEIGHT);

	//print_map(BLOCK_WIDTH, BLOCK_HEIGHT, block);
	//print_map(BOARD_WIDTH, BOARD_HEIGHT, board);
	
	while(BOARD_HEIGHT-pos.y-BLOCK_HEIGHT >= 0) {

		seconds = t/CLOCKS_PER_SEC;

		if (seconds % interval == 0 && !called && seconds > 0) {
			clear_map(board, BOARD_WIDTH, BOARD_HEIGHT);
			map_onto(board, block, &pos);
			rot(BLOCK_WIDTH, BLOCK_HEIGHT, block);
			pos.y++;
			print_map(BOARD_WIDTH, BOARD_HEIGHT, board);
			called = 1;

			if (BOARD_HEIGHT-pos.y-BLOCK_HEIGHT < 0) {
				pos.y = 0;
			}
		}

		else if (seconds % interval == 1) called = 0;

		t = clock();
	}

	free(board);
	return 0;
}
