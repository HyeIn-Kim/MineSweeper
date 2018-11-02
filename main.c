#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "grille.h"
#include "jeu.h"

int main()
{
    srand(time(NULL)); // Init rand avec le le nombre de secondes écoulées depuis le premier janvier 1970 au moment du lancement
    printf("--------------------- DEMINEUR ---------------------\n");

    int nbCols;
    int nbRows;

    printf("Veuillez choisir un nombre de lignes (max : 8) :  \n");
    scanf("%d",&nbRows);

    printf("Veuillez choisir un nombre de colonnes (max : 8) : \n");
    scanf("%d",&nbCols);

    if(nbRows > 0 && nbRows <= 8)
    {
        if(nbCols > 0 && nbCols <= 8)
        {
            Liste *maGrille = initialisation(nbRows, nbCols);
            int r;
            int c;
            for(r = 0; r < nbRows; r++)
            {      
                for(c = 0; c < nbCols; c++)
                {
                    if(r == 0 && c == 0)
                    {
                        ++c;
                        insertion(maGrille, r, c, 'c',isMined());
                    }
                    else
                        insertion(maGrille, r, c, 'c',isMined());
                }                
            }
            printf("La partie commence ! \n\n\n");
            afficherGrille(maGrille);
            Play(nbRows, nbCols, maGrille);
        }
    }
    else
    {
        printf("Erreur dans le nombre de lignes et de colonnes, au revoir !");
        exit(0);
    }
    return 0;
}
