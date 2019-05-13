#ifndef _MINESWEEPER_H
#define _MINESWEEPER_H

#define NORMAL 0
#define MINE 1
#define MINBOARD 3
#define MAXBOARD 16
#define STATUS_OPEN 100
#define STATUS_FLAG 101
#define STATUS_CLOSE 102
#define STATUS_OUTOFRANGE 103

typedef struct Board {
	int statusBlock; 
	int statusMine;
	int cntNearMine;
}Board;

void Play(Board*);
void MineAllocate(Board*);
void OpenBlock(int,int,Board*);
void InitBoard(Board*,int,int);
void DrawBoard();
void CntMine(Board*); 
int IsGameReset();
int IsRetry(char);
int IsNotRetry(char);
int IsVictory();
int checkRows(int);
int checkCols(int);


#endif



