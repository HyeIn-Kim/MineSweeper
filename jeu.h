typedef struct Liste Liste;

void Play(int row, int col, Liste *grille);
int checkForBombes(Liste *grille, int rowCible, int colCible);
char isWon(Liste *grille);

