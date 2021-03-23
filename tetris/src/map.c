// DOES NOT COMPILE RN

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "tetrominos.h"
#include <ncurses.h>

int BOARD_WIDTH = 10;
int BOARD_HEIGHT = 18;

int* board_state = NULL;
int* board = NULL;

struct vec2_t {
	int x;
	int y;
};

struct vec2_t pos = {0, 0};

void display_board() {
	for(int y=0; y<BOARD_HEIGHT; y++) {
		for (int x=0; x<BOARD_WIDTH; x++) {
			if (!board[(y*BOARD_WIDTH)+x]) mvprintw(y, x, " ");
			else mvprintw(y, x, "%d",board[(y*BOARD_WIDTH)+x]); 
			refresh();
		}
	}
}

void map_onto(int* block) {
	for (int y=0; y<BLK_HEIGHT; y++) {
		for (int x=0; x<BLK_WIDTH; x++) {
			if (!board_state[((y+pos.y)*BOARD_WIDTH)+(x+pos.x)])
				board[((y+pos.y)*BOARD_WIDTH)+(x+pos.x)] = block[(y*BLK_WIDTH) + x];
		}	
	}
}

void clear_board() {
	for (int y=0; y<BOARD_HEIGHT; y++) {
		for (int x=0; x<BOARD_WIDTH; x++) {
			board[(y*BOARD_WIDTH) + x] = board_state[(y*BOARD_WIDTH)+x];
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

void get_blk_width(int* bwp, int* blk, int dx) {
	int found_edge = 0, this_blk_width = 0;	
   	int x = dx > 0 ? BLK_WIDTH-1: 0;
	int y = BLK_HEIGHT-1;
	int xinc = dx > 0 ? -1 : 1;
	
	while(!found_edge) {
		for(int cur_y=y;cur_y>-1;cur_y--) {
			if (blk[(cur_y*BLK_WIDTH)+x]) {
				this_blk_width = x+1;
				found_edge = 1;
			}
		}
		x+=xinc;
	}
	
	*bwp = this_blk_width;
}

void get_blk_height(int* bhp, int* blk) {
	int found_edge = 0, this_blk_height= 0;	
	int x = BLK_HEIGHT-1, y = BLK_HEIGHT-1;
	
	while(!found_edge) {
		for(int cur_x=x;cur_x>-1;cur_x--) {
			if (blk[(y*BLK_WIDTH)+cur_x]) {
				this_blk_height = y+1;
				found_edge = 1;
			}
		}
		y--;
	}

	*bhp = this_blk_height;
}

//TODO
//void check_collision(int* cp, int* blk, int this_blk_height) {
//	// look at the last row of 1's on our blk
//		// for each of those (x's) we calculate from that 
//		// x cord + height if we hit a blk below
//		for (int y=0; y<BLK_HEIGHT; y++) {
//			for (int x=0; x<BLK_WIDTH; x++) {
//				if (blk[(y*BLK_WIDTH)+x]) {
//					if (board[(pos.y+1)*BOARD_WIDTH + pos.x]) {
//						*cp = 1;
//						return;
//					}
//				}
//			}
//		}
//}

int move_blk(int dx, int dy, int* blk) {
	int this_blk_width, this_blk_height, collision = 0;
	
	get_blk_height(&this_blk_height, blk);
	get_blk_width(&this_blk_width, blk, dx);
	
	// we only need to check for a collision
	// if the player or the game forces a block down
	// when this happens we will see a 1 for dy
	if (dy) check_collision(&collision, blk, this_blk_height); //TODO DOES NOT COMPILE

	// we have hit a block or the bottom..
	if (BOARD_HEIGHT-pos.y-this_blk_height< 0 || collision) {
		memcpy(board_state, board, sizeof(int)*BOARD_HEIGHT*BOARD_WIDTH);
		pos.y = 0;
		return 0;
	}
	
	// if player is trying to move off board
	if (pos.x+dx > BOARD_WIDTH-this_blk_width && dx > 0) return 0;
	else if (pos.x+dx+this_blk_width <= 0 && dx < 0) return 0;
	
	pos.x += dx;
	pos.y += dy;
	return 1;
}

void init_curses(void) {
	initscr();
	raw();
	keypad(stdscr, TRUE);
	noecho();
	nodelay(stdscr, TRUE);
	curs_set(0);
}

int main(void) {
	init_curses();

	int seconds = 0, called = 0, interval = 2;
	clock_t t;
	t = clock();

	board = (int*) malloc(BOARD_WIDTH*BOARD_HEIGHT*sizeof(int));
	board_state = (int*) malloc(BOARD_WIDTH*BOARD_HEIGHT*sizeof(int));
	
	int is_running = 1;
	while(is_running) {		

		int c = getch();
		switch(c) {
			case KEY_RIGHT:
				move_blk(1, 0, lblk);
				break;
			case KEY_LEFT:
				move_blk(-1, 0, lblk);
				break;
			case KEY_DOWN:
				move_blk(0, 1, lblk);
				break;
			case 114: // R KEY
				if (BOARD_WIDTH-pos.x >= BLK_WIDTH && pos.x >= 0)
					rot(BLK_WIDTH, BLK_HEIGHT, lblk);
				break;
			case 27: // ESCAPE KEY
				is_running = 0;
				break;
			default:
				break;
		}

		clear_board();
		map_onto(lblk);
		display_board();

		seconds = t/CLOCKS_PER_SEC;
		if (seconds % interval == 0 && !called && seconds > 0) {
			move_blk(0, 1, lblk);
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
