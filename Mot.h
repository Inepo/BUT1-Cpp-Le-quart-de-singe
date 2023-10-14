#ifndef _MOT_
#define _MOT_

#include "Partie.h"


/**
 * @brief Type Mot
*/
typedef struct {
	unsigned int taille;
	char* Mot;
	unsigned int taille_reponse;
	char reponse[26];
}Mot;

/**
*@brief Initialise mon tableau de mot en memoire dynamique
* @see supprimer, pour sa désallocation en fin d'utilisation
* @param[in] m : initialise en tableau en capacité capa

*/
void ini(Mot& m, unsigned int capa);

/**
*@brief Saisie par un humain
* @param[in] m : saisie d'une lettre à la position (position)
*/
void saisie_joueur(Mot& m, unsigned int position);

/**
 * @brief Affichage d'un mot
 * @param[in] m : mot à afficher lettre par lettre en fonction de la taille
 */
void afficher_mot(Mot* m, unsigned int taille, unsigned int gage);

/**
 * @brief Compare mot stocker avec les mots du dictionnaire
 * @param[in] m : le mot à comparer
 */
int compare(Mot& m);

/**
 * @brief Verification du mot saisie lors de l'interrogation
 * @param[in] p : connaitre le type du joueur, m : verification du mot stocker avec le mot saisie pour afficher le bon message d'erreur
 */
int interogation(int joueur, Partie& p, Mot& m, int taille);

/**
 * @brief Compare mot stocker avec les mots du dictionnaire
 * @param[in] m : le mot à comparer, p : pour viser la personne dans le message d'erreur
 */
int comparaison(const Mot* m, int numero_joueur, Partie& p);

/**
 * @brief Saisie du robot
 * @param[in] m : lettre à saisir à la position (position)
 */
int saisie_robot(Mot& m, unsigned int position, int numero_joueur);

/**
 * @brief Désalloue mes tableaux en mémoire dynamique
 */
void supprimer(Partie& p, Mot& m);

#endif