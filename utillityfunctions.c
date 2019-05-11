#include"Minesweeper.h"


int checkRows(int boardRows) {
	return (boardRows >= MINBOARD && boardRows <= MAXBOARD);
}
int checkCols(int boardCols) {
	return (boardCols >= MINBOARD && boardCols <= MAXBOARD);
}
