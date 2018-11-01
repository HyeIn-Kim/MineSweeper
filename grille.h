typedef struct Element Element;
struct Element
{
    int row;
    int col;
    char statut; // o - open / f - flag / n - not open
    int mine; // 0 = no / 1 = yes
    Element *suivant;
};

typedef struct Liste Liste;
struct Liste
{
    int nbRow;
    int nbCol;
    int nbCases;
    Element *premier;
};

int isMined();
Liste *initialisation(int _nbRow, int _nbCol);
void insertion(Liste *liste, int _row, int _col, char _statut, int _mine);
void suppression(Liste *liste);
void afficherGrille(Liste *liste);