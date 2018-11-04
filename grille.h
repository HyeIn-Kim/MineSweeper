typedef struct Element Element;
struct Element
{
	int row;
	int col;
	char statut; // o - open / f - flag / c - closed
	int mine; // 0 = no / 1 = yes
	int numCase;
	Element *suivant;
};


typedef struct Liste Liste;
struct Liste
{
	int nbRow;
	int nbCol;
	int nbCases;
	Element *premier;
	Element *dernier;
};

Liste *initialisation(int _nbRow, int _nbCol);
void insertionFin(Liste *grille, int _row, int _col, char _statut, int _mine);
void remplissageGrille(int nbRows, int nbCols, Liste *maGrille);

int isMined();
void afficherGrille(Liste *liste);
Element *findCase(Liste *maGrille, int _numCase);