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
	int indexBlock;
}Board;

void Play(Board*,int,int);
void MineAllocate(Board*,int,int);
void OpenBlock(int,int,Board*);
void InitBoard(Board*,int,int);
void DrawBoard(Board*);
void CntMine(Board **my_Board, int row, int col, int boardRows, int boardCols); //¼±ÅÃÇÑ Ä­ ÁÖÀ§ ÆøÅº ¼ö¸¦ ¼¼´Â ÇÔ¼ö.
int IsGameReset();
int IsRetry(char);
int IsNotRetry(char);
int IsVictory(Board **my_Board, int boardRows, int boardCols); //½Â¸®¿©ºÎ ÇÔ¼ö. ¹ÝÈ¯°ª: ½Â¸®(1), ½Â¸®¾Æ´Ô(0)
int checkRows(int);
int checkCols(int);


#endif



