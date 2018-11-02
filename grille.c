#include <stdio.h>
#include <stdlib.h>
#include "grille.h"

Liste *initialisation(int _nbRow, int _nbCol)
{
    Liste *grille = malloc(sizeof(*grille));
    Element *element = malloc(sizeof(*element));

    if(grille == NULL || element == NULL)
    {
       exit(EXIT_FAILURE);
    }

    element->row = 0;
    element->col = 0;
    element->statut = 'c';
    element->mine = 0;
    element->numCase = 1;
    element->suivant = NULL;

    grille->premier = element; // le premier element de la grille est element que l'on vient de créer
    grille->nbRow = _nbRow; // On récupère le nombre de ligne que l'utilisateur à choisi et on l'insert dans les infos de la Grille    
    grille->nbCol = _nbCol; // On récupère le nombre de colonnes que l'utilisateur à choisi et on l'insert dans les infos de la Grille
    grille->nbCases = 1; // On met le nombre de case de la grille égale à 1 car on vient de créer une case

    return grille;
}

int isMined()
{    
    int random = rand() % 100; // aléatoire entre 0 et 100;
    if(random > 50) // si > à 50 on dit qu'il y a une mine
    {
        return 1;
    }
    return 0; // sinon on retroune qu'il n'y a pas de mine dans cette case
}

void insertion(Liste *grille, int _row, int _col, char _statut, int _mine) // Insertion d'un élément au début de la grille
{
    /* Création du nouvelle case */
    Element *nouvelleCase = malloc(sizeof(*nouvelleCase));
    if(grille == NULL || nouvelleCase == NULL)
    {
        exit(EXIT_FAILURE);
    }

    nouvelleCase->row = _row;
    nouvelleCase->col = _col;
    nouvelleCase->statut = _statut;
    nouvelleCase->mine = _mine;
    nouvelleCase->numCase = grille->nbCases;

    /* Insertion de l'élement au début de la liste */
    nouvelleCase->suivant = grille->premier;
    grille->premier = nouvelleCase;
    grille->nbCases++;
}

void suppression(Liste *grille)
{
    if(grille == NULL)
    {
        exit(EXIT_FAILURE);
    }

    if(grille->premier != NULL)
    {
        Element *aSupprimer = grille->premier;
        grille->premier = grille->premier->suivant;
        free(aSupprimer);
    }
}

void afficherGrille(Liste *grille)
{
    if(grille == NULL)
    {
        exit(EXIT_FAILURE);
    }

    Element *actuel = grille->premier;
    int compteur = grille->nbCases;
    while(actuel != NULL)
    { 
        if(actuel->statut == 'c')
        {
            if(actuel->row > actuel->suivant->row)
            {                    
                printf("|%d|",actuel->numCase);
                printf("\n");
            }
            else
            {
                printf("|%d|",actuel->numCase);
            }
        }
        // switch (actuel->statut) Probleme avec ça verifier d'où ça vient
        // {
        //     case 'c':
        //         if(actuel->row > actuel->suivant->row)
        //         {                    
        //             printf("|%d|",actuel->numCase);
        //             printf("\n");
        //         }
        //         else
        //         {
        //             printf("|%d|",actuel->numCase);
        //         }
        //         break;
        //     case 'f':
        //         if(actuel->row > actuel->suivant->row)
        //         {
        //             printf("|F|");
        //             printf("\n");
        //         }
        //         else
        //         {
        //             printf("|F|");
        //         }                
        //         break;
        //     case 'o':
        //         if(actuel->row > actuel->suivant->row)
        //         {
        //             if(actuel->mine == 1)
        //             {
        //                 printf("|X|");
        //                 printf("\n");
        //             }
        //         }
        //         else
        //         {
        //             if(actuel->mine == 1)
        //             {
        //                 printf("|X|");
        //             }
        //         }                 
        //     default:
        //         printf("Erreur case");
        //         break;
        // }
        printf("case %d , ligne : %d // col : %d // statut : %c // isMined : %d\n \n", compteur, actuel->row, actuel->col, actuel->statut, actuel->mine); // FOR DEBUG
        actuel = actuel->suivant;
        compteur--;
    }
}

Element *findCase(Liste *maGrille,int _numCase)
{
    if(maGrille == NULL)
    {
        exit(EXIT_FAILURE);
    }

    Element *actuel = maGrille->premier;    
    while(actuel != NULL)
    {
        if(actuel->numCase == _numCase)
        {
            return actuel;
        }
        actuel = actuel->suivant;
    }
    if(actuel = maGrille->premier)
    {
        actuel = NULL;
        return actuel;
    }
}

