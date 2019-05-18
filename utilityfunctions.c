
#include"Minesweeper.h"
#include <stdio.h>

int checkRows(int boardRows) {
	return (boardRows >= MINBOARD && boardRows <= MAXBOARD);
}
int checkCols(int boardCols) {
	return (boardCols >= MINBOARD && boardCols <= MAXBOARD);
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
