#include <stdio.h>
#include <stdlib.h>
#include "grille.h"
#include "jeu.h"

Liste *initialisation(int _nbRow, int _nbCol)
{
	Liste *grille = malloc(sizeof(*grille));
	Element *element = malloc(sizeof(*element));

	if (grille == NULL || element == NULL)
	{
		exit(EXIT_FAILURE);
	}

	element->row = 0;
	element->col = 0;
	element->statut = 'c';
	element->mine = isMined();
	element->numCase = 1;
	element->suivant = NULL;

	grille->premier = element; // le premier element de la grille est element que l'on vient de créer
	grille->dernier = element; // le dernier element de la grille est element que l'on vient de créer
	grille->nbRow = _nbRow;    // On récupère le nombre de ligne que l'utilisateur à choisi et on l'insert dans les infos de la Grille
	grille->nbCol = _nbCol;    // On récupère le nombre de colonnes que l'utilisateur à choisi et on l'insert dans les infos de la Grille
	grille->nbCases = 1;       // On met le nombre de case de la grille égale à 1 car on vient de créer une case

	return grille;
}

int isMined()
{
	int random = rand() % 100; // aléatoire entre 0 et 100;
	if (random > 50)           // si > à 50 on dit qu'il y a une mine
	{
		return 1;
	}
	return 0; // sinon on retroune qu'il n'y a pas de mine dans cette case
}

void insertionFin(Liste *grille, int _row, int _col, char _statut, int _mine)
{
	Element *nouvelleCase = malloc(sizeof(*nouvelleCase));

	if (grille == NULL)
	{
		exit(EXIT_FAILURE);
	}

	// On initialise notre nouvelle case
	nouvelleCase->row = _row;
	nouvelleCase->col = _col;
	nouvelleCase->statut = _statut;
	nouvelleCase->mine = _mine;
	nouvelleCase->numCase = grille->nbCases + 1;
	nouvelleCase->suivant = NULL;

	
	grille->dernier->suivant = nouvelleCase; // On change le NULL du dernier élement de la liste et on le fait pointer sur notre élement
	grille->dernier = nouvelleCase; // Le dernier élément est égal à notre élement
	grille->nbCases++; // augmente le compteur d'élement de la liste de 1
}

void afficherGrille(Liste *grille) // Gère l'affichage de la grille
{
	if (grille == NULL)
	{
		exit(EXIT_FAILURE);
	}

	Element *actuel = grille->premier;

	while (actuel != NULL)
	{
		switch (actuel->statut) // On gère l'affichage en fonction du statut de la case 
		{
		case 'c':
			if (actuel->suivant != NULL)
			{
				if (actuel->row < actuel->suivant->row) // Si la case d'après est sur une autre ligne on fait un retour à la ligne
				{
					printf("|%d|\n", actuel->numCase);
				}
				else
				{
					printf("|%d|", actuel->numCase);
				}
			}	
			else
			{
				printf("|%d|\n", actuel->numCase);
			}
			break;
		case 'f':
			if (actuel->suivant != NULL)
			{
				if (actuel->row < actuel->suivant->row) // Si la case d'après est sur une autre ligne on fait un retour à la ligne
				{
					printf("|F|\n");
				}
				else
				{
					printf("|F|");
				}
			}
			else
			{
				printf("|F|\n");
			}			
			break;
		case 'o':
			if (actuel->mine == 1) // Si la case ouverte est miné
			{
				printf("|X|");
			}
			else
			{
				int nbBombes = checkForBombes(grille, actuel->row, actuel->col);
				if (actuel->suivant != NULL)
				{
					if (actuel->row < actuel->suivant->row) // Si la case d'après est sur une autre ligne on fait un retour à la ligne
					{
						printf("|*%d*|\n", nbBombes);
					}
					else
					{
						printf("|*%d*|", nbBombes);
					}
				}
				else
				{
					printf("|*%d*|\n", nbBombes);
				}				
			}
			break;
		default:
			printf("Erreur lors de l'affichage de la grille");
			break;
		}
		actuel = actuel->suivant;
	}
}

Element *findCase(Liste *maGrille, int _numCase) // Permet de trouver un element avec son numéro de case
{
	if (maGrille == NULL)
	{
		exit(EXIT_FAILURE);
	}

	Element *actuel = maGrille->premier;
	while (actuel != NULL)
	{
		if (actuel->numCase == _numCase)
		{
			return actuel;
		}
		actuel = actuel->suivant;
	}
	if (actuel == maGrille->premier)
	{
		actuel = NULL;
		return actuel;
	}
	return actuel;
}

void remplissageGrille(int nbRows, int nbCols, Liste *maGrille)
{
	int r;
	int c;
	for (r = 0; r < nbRows; r++)
	{
		for (c = 0; c < nbCols; c++)
		{
			if (r == 0 && c == 0)
			{
				c++;
				insertionFin(maGrille, r, c, 'c', isMined());
			}
			else
				insertionFin(maGrille, r, c, 'c', isMined());
		}
	}
}
