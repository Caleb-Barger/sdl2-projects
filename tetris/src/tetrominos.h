#define BLK_WIDTH 4
#define BLK_HEIGHT 4

int zblk[BLK_WIDTH*BLK_HEIGHT] = {
	0, 0, 0, 0,
	0, 0, 0, 0,
	0, 1, 1, 0,
	0, 0, 1, 1
};

int sblk[BLK_WIDTH*BLK_HEIGHT] = {
	0, 0, 0, 0,
	0, 0, 0, 0,
	0, 1, 1, 0,
	1, 1, 0, 0
};

int oblk[BLK_WIDTH*BLK_HEIGHT] = {
	0, 0, 0, 0,
	0, 0, 0, 0,
	1, 1, 0, 0,
	1, 1, 0, 0
};
int lblk[BLK_WIDTH*BLK_HEIGHT] = {
	1, 0, 0, 0,
	1, 0, 0, 0,
	1, 0, 0, 0,
	1, 1, 0, 0
};
int iblk[BLK_WIDTH*BLK_HEIGHT] = {
	1, 0, 0, 0,
	1, 0, 0, 0,
	1, 0, 0, 0,
	1, 0, 0, 0
};
int jblk[BLK_WIDTH*BLK_HEIGHT] = {
	0, 1, 0, 0,
	0, 1, 0, 0,
	0, 1, 0, 0,
	1, 1, 0, 0
};
int tblk[BLK_WIDTH*BLK_HEIGHT] = {
	0, 0, 0, 0,
	0, 0, 0, 0,
	1, 1, 1, 0,
	0, 1, 0, 0
};
