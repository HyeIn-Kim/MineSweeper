#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Minesweeper.h"

void MineAllocate(Board my_Board[][MAXBOARD], int boardRows, int boardCols) {
	srand(time(NULL));
	const double mineRate = 0.15;
	int mineNum = (boardRows * boardCols) * mineRate;
	int row;
	int col;

	while (mineNum > 0) {
		row = rand() % boardRows;
		col = rand() % boardCols;
		if (my_Board[row][col].statusMine == NORMAL) {
			my_Board[row][col].statusMine = MINE;
			mineNum--;
		}
	}
}

void Play(Board my_Board[][MAXBOARD], int boardRows, int boardCols) {
	MineAllocate(*my_Board, boardRows, boardCols);
	return;
}