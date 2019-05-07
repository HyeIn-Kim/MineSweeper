#ifndef _MINESWEEPER_H
#define _MINESWEEPER_H

#define NORMAL 0
#define MINE 1
#define STATUS_OPEN 100
#define STATUS_FLAG 101
#define STATUS_CLOSE 102
#define STATUS_OUTOFRANGE 103

const double mineRate = 0.15;
const int minBoard = 3;
const int maxBoard = 16;

typedef struct Board {
	int structBlock;
	int statusMine;
	int cntNearMine;
}Board;

void Play(Board*);
void MineAllocate(Board*);
void OpenBlock(int,int,Board*);
void InitBoard(Board*);
int IsGameOver();
int IsGameReset();
int IsVictory();
void DrawBoard();
void CntMine(Board*); 
int checkRows(int);
int checkCols(int);


#endif



