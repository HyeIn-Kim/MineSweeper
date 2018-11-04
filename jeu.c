#include <stdio.h>
#include <stdlib.h>
#include "grille.h"
#include "jeu.h"

void Play(int row, int col, Liste *grille)
{
	if (isWon(grille) == 'n')
	{
		printf("Veuillez selectionner une case ou jouer \n");

		int caseJoue = 0;
		int casesMax = row * col; //Nombres max de cases jouables dans la grille
		scanf_s("%d", &caseJoue);

		if (caseJoue > 0 && caseJoue <= casesMax) // Le joueur doit entrer une valeur supérieur à 0 et inférieur ou égale à la taille maximal de la grille
		{
			printf("Veuillez decider d'une action sur cette case : \n 1 - Ouvrir la case \n 2 - Mettre un drapeau sur la case \n");
			int choix;
			scanf_s("%d", &choix);

			Element *caseATrouver = NULL;

			switch (choix)
			{
			case 1:
				caseATrouver = findCase(grille, caseJoue);
				if (caseATrouver != NULL)
				{
					if (caseATrouver->statut == 'o')
					{
						printf("Case deja ouverte !\n");
					}
					else
					{
						if (caseATrouver->mine == 0) // Si il n'y a pas de mine on ouvre la case
						{
							caseATrouver->statut = 'o';
							afficherGrille(grille);
							Play(row, col, grille); // relance la methode de jeu
						}
						else
						{
							printf("\n---------------------------------\n");
							printf(" BOOM !\nVous avez perdu !\n"); // Message de défaite, on ne relance pas le jeu
							printf("\n---------------------------------\n");
							afficherGrille(grille); // On réaffiche la grille avec la mine qui a explosé
						}
					}
				}
				else
				{
					printf("Impossible de trouver la case !\n");
					afficherGrille(grille);
					Play(row, col, grille); // relance la methode de jeu
				}
				break;
			case 2:
				caseATrouver = findCase(grille, caseJoue);
				if (caseATrouver != NULL)
				{
					if (caseATrouver->statut == 'f')
					{
						printf("Un drapeau est deja présent sur cette case !\n");
						afficherGrille(grille);
						Play(row, col, grille); // relance la methode de jeu
					}
					else
					{
						caseATrouver->statut = 'f';
						afficherGrille(grille);
						Play(row, col, grille); // relance la methode de jeu            
					}
				}
				else
				{
					printf("Impossible de trouver la case !\n");
					afficherGrille(grille);
					Play(row, col, grille); // relance la methode de jeu
				}
				break;
			default:
				printf("Choix errone ! Rejouez \n");
				afficherGrille(grille);
				Play(row, col, grille); // relance la methode de jeu
				break;
			}
		}
	}
	else
	{
		printf("\n \n Vous avez gagne ! Felicitation \n");
		printf("-------------------FIN DE LA PARTIE------------------ \n");

	}
}



int checkForBombes(Liste *grille, int rowCible, int colCible)
{
	int nbBombes = 0;

	Element *currentCase = grille->premier;

	while (currentCase != NULL)
	{
		if (currentCase->row == rowCible - 1) // Si il existe une ligne de la grille inférieure à celle envoyée en paramètre
		{
			// On verifie que les elements sur la ligne adjacent à notre case sont minés ou non
			if (currentCase->col == colCible - 1)
			{
				if (currentCase->mine == 1)
				{
					nbBombes++;
				}
			}
			if (currentCase->col == colCible)
			{
				if (currentCase->mine == 1)
				{
					nbBombes++;
				}
			}
			if (currentCase->col == colCible + 1)
			{
				if (currentCase->mine == 1)
				{
					nbBombes++;
				}
			}
		}


		if (currentCase->row == rowCible) // On regarde sur la meme ligne que notre case
		{
			if (currentCase->col == colCible - 1)
			{
				if (currentCase->mine == 1)
				{
					nbBombes++;
				}
			}
			if (currentCase->col == colCible + 1)
			{
				if (currentCase->mine == 1)
				{
					nbBombes++;
				}
			}
		}

		if (currentCase->row == rowCible + 1)
		{			
			if (currentCase->col == colCible - 1)
			{
				if (currentCase->mine == 1)
				{
					nbBombes++;
				}
			}
			if (currentCase->col == colCible)
			{
				if (currentCase->mine == 1)
				{
					nbBombes++;
				}
			}
			if (currentCase->col == colCible + 1)
			{
				if (currentCase->mine == 1)
				{
					nbBombes++;
				}
			}
		}
		currentCase = currentCase->suivant;
	}
	return nbBombes;
}


char isWon(Liste *grille)
{
	char gameStatut = 'n';
	Element *current = grille->premier;

	while (current != NULL)
	{
		if (current->statut == 'f')
			if (current->mine == 1)
				gameStatut = 'w';

		if (current->statut == 'c')
			gameStatut = 'n';
			if (current->mine == 1)

		current = current->suivant;
	}
	return gameStatut; // La partie est gagnée
}