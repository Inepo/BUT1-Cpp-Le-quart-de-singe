/**
* @file Partie.cpp
* Projet SAE C++ Periode B
* @author Oum Kaltoum LAMRABET et Ines Kadji
* @date 20/12/22
* @brief jeu du singe baser sur un dictionnaire odt4
* Structure de données et algorithmes - BUT1 S1 Periode B Université Paris Cité
*/

#include <iostream>
#include <cstring> 
#include "Partie.h"
using namespace std;

void initialiser(Partie& p, const char* argv[]) {
	p.nombres_joueurs = strlen(argv[1]);
	p.participants = new Joueur[p.nombres_joueurs];
	for (unsigned int i = 0; i < p.nombres_joueurs; ++i) {
		Joueur j;
		j.numero_joueur = i + 1;
		j.type_de_joueur = argv[1][i];
		j.point = 0;
		p.participants[i] = j;
	}
}

bool verif_point_joueur(Partie* p) {
	float un = 1;
	for (unsigned int i = 0; i < p->nombres_joueurs; ++i) {
		if (p->participants[i].point == un) {
			return true;
		}
	}
	return false;
}

void score(Partie& p) {
	for (unsigned int i = 0; i < p.nombres_joueurs; ++i) {
		if (i == 0) {
			cout << p.participants[i].numero_joueur << p.participants[i].type_de_joueur << " : " << p.participants[i].point << ";";
		}
		else
			cout << " " << p.participants[i].numero_joueur << p.participants[i].type_de_joueur << " : " << p.participants[i].point << ";";
	}
	cout << endl;
}