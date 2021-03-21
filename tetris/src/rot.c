#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_map(int w, int h, int* map) {
	for (int i=0; i < w*h; i++) {
		if (i % w == 0) printf("\n");
		printf("%d ", map[i]);
	}

	printf("\n");
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
	int w=3, h=3;
	int* mata = malloc(sizeof(int)*h*w); 

	for (int i=0; i < w*h; i++) mata[i] = i;

	print_map(w, h, mata);
	rot(w, h, mata);
	print_map(w, h, mata);

	free(mata);
}
