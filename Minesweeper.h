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
int row;
int col;

void Play();
void MineAllocate();
int OpenBlock();
void FlagBlock();
void InitBoard();
void DrawBoard();
void CntMine(int, int);
void setBoardSize();
int IsGameReset();
int IsRetry(char);
int IsNotRetry(char);
int IsVictory(); 
int checkRows();
int checkCols();
int checkRowsinGame(int);
int checkColsinGame(int);
int ActionInRange(int);
void setCurrentCursorPos(int, int);
COORD getCurrentCursorPos(void);
void IntroShow();
void OpenAllBlock();

#endif
