#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "grille.h"
#include "jeu.h"

#define GRILLEMAX 16

int main()
{
	srand(time(NULL)); // Init rand avec le le nombre de secondes écoulées depuis le premier janvier 1970 au moment du lancement
	printf("--------------------- DEMINEUR ---------------------\n");

	int nbCols;
	int nbRows;

	printf("Veuillez choisir un nombre de lignes (max : %d) :  \n",GRILLEMAX);
	scanf("%d", &nbRows);

	printf("Veuillez choisir un nombre de colonnes (max : %d) : \n",GRILLEMAX);
	scanf("%d", &nbCols);

	if (nbRows > 2 && nbRows <= GRILLEMAX)
	{
		if (nbCols > 2 && nbCols <= GRILLEMAX)
		{
			Liste *maGrille = initialisation(nbRows, nbCols); // Initialisation de la grille
			remplissageGrille(nbRows, nbCols, maGrille); // On créer une grille de la taille donnée
			printf("La partie commence ! \n\n\n");
			afficherGrille(maGrille); // Affichage de la grille pour débuter la partie
			Play(nbRows, nbCols, maGrille); // On démarre la partie en demandant au joueur de choisir où jouer, la méthode est récursive
		}
	}
	else
	{
		printf("Erreur dans le nombre de lignes et de colonnes, au revoir !");
		main();
		exit(0);
	}
	return 0;
}
