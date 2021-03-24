#define BLK_WIDTH 4
#define BLK_HEIGHT 4

const int ZBLK[BLK_WIDTH*BLK_HEIGHT] = {
	0, 0, 0, 0,
	0, 0, 0, 0,
	0, 1, 1, 0,
	0, 0, 1, 1
};

const int SBLK[BLK_WIDTH*BLK_HEIGHT] = {
	0, 0, 0, 0,
	0, 0, 0, 0,
	0, 1, 1, 0,
	1, 1, 0, 0
};

const int OBLK[BLK_WIDTH*BLK_HEIGHT] = {
	0, 0, 0, 0,
	0, 0, 0, 0,
	1, 1, 0, 0,
	1, 1, 0, 0
};

const int LBLK[BLK_WIDTH*BLK_HEIGHT] = {
	1, 0, 0, 0,
	1, 0, 0, 0,
	1, 0, 0, 0,
	1, 1, 0, 0
};

const int IBLK[BLK_WIDTH*BLK_HEIGHT] = {
	1, 0, 0, 0,
	1, 0, 0, 0,
	1, 0, 0, 0,
	1, 0, 0, 0
};

const int JBLK[BLK_WIDTH*BLK_HEIGHT] = {
	0, 1, 0, 0,
	0, 1, 0, 0,
	0, 1, 0, 0,
	1, 1, 0, 0
};

const int TBLK[BLK_WIDTH*BLK_HEIGHT] = {
	0, 0, 0, 0,
	0, 0, 0, 0,
	1, 1, 1, 0,
	0, 1, 0, 0
};
