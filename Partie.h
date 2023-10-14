#ifndef _PARTIE_
#define _PARTIE_

#include "Joueur.h"

/**
 * @brief Type Partie
*/
typedef struct {
	Joueur* participants;
	unsigned int nombres_joueurs;
}Partie;

/**
*@brief Initialise mon tableau j en m�moire dynamiquede capacit� strlen(argv[1])
* @see supprimer, pour sa d�sallocation en fin d'utilisation
* @param[in] p : type � initialiser
* @param[in] argv[] : on initialise � une taille de strlen(argv[1])
*/
void initialiser(Partie& p, const char* argv[]);

/**
*@brief Verification que le nombre de chaque joueur < 1
* @param[in] p : structure ou sont stocker le score des joueurs
*/
bool verif_point_joueur(Partie* p);

/**
 * @brief Affichage des scores
 * @param[in] p : donne le score de chaque joueur (car stocker dans la structure)
 */
void score(Partie& p);

#endif