
#include"Minesweeper.h"
#include <stdio.h>

int checkRows(int boardRows) {
	return (boardRows >= MINBOARD && boardRows <= MAXBOARD);
}
int checkCols(int boardCols) {
	return (boardCols >= MINBOARD && boardCols <= MAXBOARD);
}

int checkRowsinGame(int currentRow, int boardRows) {
	return (currentRow > 0 && currentRow <= boardRows);
}
int checkColsinGame(int currentCol, int boardCols) {
	return (currentCol > 0 && currentCol <= boardCols);
}

int IsRetry(char user){
	return (user=='y' || user == 'Y');
}
int IsNotRetry(char user){
	return (user=='n' || user=='N');
}

int IsGameReset(){
	char user;
	user=NULL;
	while(!IsRetry(user) && !IsNotRetry(user)){
		getchar();
		printf("Retry? (Y/N): ");
		scanf_s("%c",&user);
		if(IsRetry(user)){return 1;}
		else if(IsNotRetry(user)){return 0;}
	}
}

int ActionInRange(int action) {
	if (action == 1 || action == 2) {
		return 1;
	}
	else
		return 0;
}