#ifndef _MINESWEEPER_H
#define _MINESWEEPER_H

#include <Windows.h>

#define OFFSET_X 10
#define OFFSET_Y 2

#define NORMAL 0
#define MINE 1
#define MINBOARD 5
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

Board my_Board[MAXBOARD][MAXBOARD];
int boardRows;
int boardCols;

void Play(int, int);
void MineAllocate(int, int, int, int);
int OpenBlock(int, int, int, int);
void FlagBlock(int, int);
void InitBoard(int, int);
void DrawBoard(int, int);
void CntMine(int, int, int, int);
void setBoardSize();
int IsGameReset();
int IsRetry(char);
int IsNotRetry(char);
int IsVictory(int, int); 
int checkRows(int);
int checkCols(int);
int checkRowsinGame(int, int);
int checkColsinGame(int, int);
int ActionInRange(int);
void setCurrentCursorPos(int, int);
COORD getCurrentCursorPos(void);
void IntroShow();
void OpenAllBlock(int, int, int, int);

#endif
