/**
* @file Mot.cpp
* Projet SAE C++ Periode B
* @author Oum Kaltoum LAMRABET et Ines Kadji
* @date 20/12/22
* @brief jeu du singe baser sur un dictionnaire odt4
* Structure de données et algorithmes - BUT1 S1 Periode B Université Paris Cité
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring> 
#include "Mot.h"
using namespace std;

void ini(Mot& m, unsigned int capa) {
	m.taille = capa;
	m.Mot = new char[capa];
}

void saisie_joueur(Mot& m, unsigned int position) {
	char lettre;
	char* newT = new char[position + 2];
	for (unsigned int i = 0; i < position; ++i) {
		newT[i] = m.Mot[i];
	}
	delete[] m.Mot;
	m.Mot = newT;
	m.taille = position;
	cin >> lettre;
	m.Mot[position] = lettre;
	m.Mot[position + 1] = '\0';
}

void afficher_mot(Mot* m, unsigned int taille, unsigned int gage) {
	if (gage == 1) {
		unsigned int x = strlen(m->reponse);
		for (unsigned int i = 0; i < x; ++i) {
			cout << m->reponse[i];
		}
	}
	else
		if (gage == 2) {
			for (unsigned int i = 0; i < m->taille; ++i) {
				cout << m->Mot[i];
			}
		}
		else {
			for (unsigned int i = 0; i < taille; ++i) {
				cout << m->Mot[i];
			}
		}
}

int compare(Mot& m) {
	ifstream in("ods4.txt");
	const int MAX = 26;
	char s[MAX];
	while (in) {
		in >> setw(MAX) >> s;
		if (strcmp(s, m.reponse) == 0) {
			in.close();
			return 1;
		}
	}
	in.close();
	return 0;
}

int interogation(int joueur, Partie& p, Mot& m, int taille) {
	m.taille_reponse = strlen(m.reponse);
	m.reponse[m.taille_reponse + 1] = '\0';
	if (p.participants[joueur].type_de_joueur == 'R') {
		ifstream in("ods4.txt");
		const int MAX = 26;
		char s[MAX];
		while (in) {
			in >> setw(MAX) >> s;
			m.taille_reponse = strlen(s);
			for (unsigned int i = 0; i < m.taille - 1; ++i) {  //mot existe pas
				if (s[i] != m.Mot[i]) {
					for (unsigned int j = 0; j < m.taille_reponse; ++j) {
						m.reponse[j] = s[j];
					}
					in.close();
					return 2;
				}
			}
			for (unsigned int j = 0; j < m.taille; ++j) { // mot existe
				if (m.Mot[j] != s[j]) {
					in >> setw(MAX) >> s;
					j = 0;
				}
			}
			m.taille_reponse = strlen(s);
			for (unsigned int i = 0; i < m.taille_reponse; ++i) {
				m.reponse[i] = s[i];
			}
			in.close();
			return -2;
		}
		in.close();
	}
	if (p.participants[joueur].type_de_joueur == 'H') {
		if (m.reponse[0] != m.Mot[0]) {
			return -1;
		}
		if (compare(m) == 1) {
			for (unsigned int i = 0; i < m.taille; ++i) {
				if (m.reponse[i] != m.Mot[i]) {
					if (m.Mot[i] == '?') {
						return 0;
					}
					return -1;
				}
			}
			return 0;
		}
	}
	return 1;
}

int comparaison(const Mot* m, int numero_joueur, Partie& p) {
	ifstream in("ods4.txt");
	const int MAX = 26;
	char s[MAX];
	while (in) {
		in >> setw(MAX) >> s;
		if (strcmp(s, m->Mot) == 0) {
			cout << "le mot " << m->Mot << " existe, le joueur " << p.participants[numero_joueur].numero_joueur << p.participants[numero_joueur].type_de_joueur << " prend un quart de singe" << endl;
			in.close();
			return 1;
		}
	}
	in.close();
	return 0;
}

int saisie_robot(Mot& m, unsigned int position, int numero_joueur) {
	ifstream in("ods4.txt");
	const int MAX = 26;
	char s[MAX];
	char lettre;
	char mot[25];
	char* newT = new char[position + 2];
	for (unsigned int i = 0; i < position; ++i) {
		newT[i] = m.Mot[i];
	}
	delete[] m.Mot;
	m.Mot = newT;
	m.taille = position + 1;
	while (in) {
		in >> setw(MAX) >> s;
		for (unsigned int i = 0; i < m.taille - 1; ++i) {
			if (i == 0) {
				if (s[i] != m.Mot[i]) {
					in >> setw(MAX) >> s;
				}
			}
			if (i != 0) {
				if (s[i] != m.Mot[i]) {
					m.Mot[position] = '?';
					m.Mot[position + 1] = '\0';
					in.close();
					return 0;
				}
			}
		}
		m.Mot[position] = s[position];
		m.Mot[position + 1] = '\0';
		if (m.Mot[position] == NULL) {
			m.Mot[position] = '?';
		}
		in.close();
		return 1;
	}
}

void supprimer(Partie& p, Mot& m) {
	delete[] p.participants;
	delete[] m.Mot;
}