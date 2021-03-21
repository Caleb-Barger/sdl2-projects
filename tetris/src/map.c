#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "tetrominos.h"
#include <ncurses.h>

int BOARD_WIDTH = 10;
int BOARD_HEIGHT = 18;

int* board_state = NULL;

struct vec2_t {
	int x;
	int y;
};

struct vec2_t pos = {0, 0};

void print_map(int w, int h, int* map) {
	for(int y=0; y<BOARD_HEIGHT; y++) {
		for (int x=0; x<BOARD_WIDTH; x++) {
			if (!map[(y*w)+x]) mvprintw(y, x, " ");
			else mvprintw(y, x, "%d",map[(y*w)+x]); 
			refresh();
		}
	}
}

void map_onto(int* board, int* block, struct vec2_t* pos) {
	for (int y=0; y<BLK_HEIGHT; y++) {
		for (int x=0; x<BLK_WIDTH; x++) {
			if (!board_state[((y+pos->y)*BOARD_WIDTH)+(x+pos->x)])
				board[((y+pos->y)*BOARD_WIDTH)+(x+pos->x)] = block[(y*BLK_WIDTH) + x];
		}	
	}
}

void clear_map(int* map, int w, int h) {
	for (int y=0; y<h; y++) {
		for (int x=0; x<w; x++) {
			map[(y*w) + x] = board_state[(y*w)+x];
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

int move_blk(int dx, int dy, int* blk) {
	// if move was successful return a 1
	// otherwise a 0 is returned
	
	int found_edge = 0;	
	int x=BLK_WIDTH-1, y=BLK_HEIGHT-1;
	int this_blk_width = 0;

	while(!found_edge) {
		for(int cur_y=y;cur_y>-1;cur_y--) {
			if (blk[(cur_y*BLK_WIDTH)+x]==1) {
				this_blk_width = x+1;
			  	found_edge = 1;
			}
		}
	  	x--;
	}

	if (pos.x+dx > BOARD_WIDTH-this_blk_width) return 0;

	pos.x += dx;
	return 1;
}

int can_rotate(int* mata) {
	return 0;
}

int main(void) {
	initscr();
	raw();
	keypad(stdscr, TRUE);
	noecho();
	nodelay(stdscr, TRUE);
	curs_set(0);

	int seconds = 0, called = 0, interval = 2;
	clock_t t;
	t = clock();

	int posx = 0;
	int posy = 0;
	pos.x = posx;
	pos.y = posy;

	int* board = (int*) malloc(BOARD_WIDTH*BOARD_HEIGHT*sizeof(int));
	board_state = (int*) malloc(BOARD_WIDTH*BOARD_HEIGHT*sizeof(int));
	
	int is_running = 1;
	while(is_running) {//BOARD_HEIGHT-pos.y-BLK_HEIGHT >= 0 ) {
		
		int c = getch();

		switch(c) {
			case KEY_RIGHT:
				//pos.x+=1;
				move_blk(1, 0, lblk);
				break;
			case KEY_LEFT:
				pos.x-=1;
				break;
			case KEY_DOWN:
				pos.y+=1;
				break;
			case 114:
				if (BOARD_WIDTH - pos.x >= BLK_WIDTH) 
					rot(BLK_WIDTH, BLK_HEIGHT, lblk);
				break;
			case 27:
				is_running = 0;
				break;
			default:
				break;
		}

		seconds = t/CLOCKS_PER_SEC;

		clear_map(board, BOARD_WIDTH, BOARD_HEIGHT);
		map_onto(board, lblk, &pos);
		print_map(BOARD_WIDTH, BOARD_HEIGHT, board);

		if (seconds % interval == 0 && !called && seconds > 0) {
			pos.y++;
			called = 1;

			if (BOARD_HEIGHT-pos.y-BLK_HEIGHT < 0) {
				memcpy(board_state, board, sizeof(int)*BOARD_HEIGHT*BOARD_WIDTH);
				pos.y = 0;
			}
		}

		else if (seconds % interval == 1) called = 0;

		t = clock();
	}
	
	free(board);
	free(board_state);
	endwin();

	return 0;
}
