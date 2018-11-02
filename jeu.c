#include <stdio.h>
#include <stdlib.h>
#include "grille.h"
#include "jeu.h"

void Play(int row, int col, Liste *grille)
{
    printf("Veuillez selectionner une case ou jouer \n");

    int caseJoue = 0;
    int casesMax = row * col; //Nombres max de cases jouables dans la grille
    scanf("%d",&caseJoue);
    
    if (caseJoue > 0 && caseJoue <= casesMax) // Le joueur doit entrer une valeur supérieur à 0 et inférieur ou égale à la taille maximal de la grille
    {
        printf("Veuillez decider d'une action sur cette case : \n 1 - Ouvrir la case \n 2 - Mettre un drapeau sur la case \n");
        int choix;
        Element *caseATrouver = NULL;
        
        switch (choix)
        {
            case 1:
                caseATrouver = findCase(grille, caseJoue);
                if(caseATrouver != NULL)
                {
                    if(caseATrouver->statut == 'o')
                    {
                        printf("Case deja ouverte !\n");
                    }
                    else
                    {
                        if(caseATrouver->mine == 0) // Si il n'y a pas de mine on ouvre la case
                        {
                            caseATrouver->statut = 'o';
                            afficherGrille(grille);
                        }
                        else
                        {
                            printf("BOOM !\n Vous avez perdu !");
                            afficherGrille(grille);
                        }
                    }
                }
                printf("Impossible de trouver la case !\n");
                break;
            case 2:
                caseATrouver = findCase(grille, caseJoue);
                if(caseATrouver != NULL)
                {
                    if(caseATrouver->statut == 'f')
                    {
                        printf("Un drapeau est deja présent sur cette case !\n");
                    }
                    else
                    {
                        caseATrouver->statut = 'f';
                    }
                }
                printf("Impossible de trouver la case !\n");
                break; 
            default:
                printf("Choix errone !\n");
                break;
        }        
    }    
}

