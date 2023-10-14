/**
* @file singe.cpp
* Projet SAE C++ Periode B
* @author Oum Kaltoum LAMRABET et Ines Kadji
* @date 25/12/22
* @brief jeu du singe baser sur un dictionnaire odt4.txt
* Structure de données et algorithmes - BUT1 S1 Periode B Université Paris Cité
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring> 
#include "Mot.h"
using namespace std;

enum {
	MAX_CARACTERE = 26
};

int main(int argc, const char* argv[]) {
	Partie p;
	Mot m;
	Joueur j;
	unsigned int position = 0;
	unsigned int gage = 0;
	initialiser(p, argv);
	ini(m, 1);

	// Permet de jouer tant que personne n'a de point = ou > à 1
	while (verif_point_joueur(&p) == false) {
		if (position < 26) {
			const int MAX = 26;
			char s[MAX];
			//Fais jouer tour par tour chaque joueur
			for (unsigned int i = 0; i < p.nombres_joueurs; ++i) {
				//verification a chaque tour de joueur pour verifier les points
				if (verif_point_joueur(&p) == true) {
					cout << "Le joueur " << p.participants[i].numero_joueur << p.participants[i].type_de_joueur << " a perdu" << endl;			
					cout << "La partie est finie" << endl;
					supprimer(p, m);
					return 0;
				}
				//Boucle rassemblant les commandes faisant jouer les humains
				if (p.participants[i].type_de_joueur == 'H') {
					if (position == 0) {
						//Fais jouer l'humain
						cout << p.participants[i].numero_joueur << p.participants[i].type_de_joueur << ", (" << ") > ";
						saisie_joueur(m, position);
						++position;
						//Empeche le premier joueur de la manche de ne pas saisir un caractére correct
						if (m.Mot[position - 1] == '?' || m.Mot[position - 1] == '!') {
							cout << "Veuillez entrer un caractere et non un '" << m.Mot[position - 1] << "', rejouez votre tour" << endl;
							position = 0;
							i = i - 1;
						}
					}
					else {
						//Fais jouer l'humain
						cout << p.participants[i].numero_joueur << p.participants[i].type_de_joueur << ", (";
						afficher_mot(&m, position, gage);
						cout << ") > ";
						saisie_joueur(m, position);
						++position;
						if (m.Mot[position - 1] == '!') {
							//Fais abandonner l'humain
							cout << "Le Joueur " << p.participants[i].numero_joueur << p.participants[i].type_de_joueur << " abandonne la manche et prend un quart de singe" << endl;
							p.participants[i].point += 0.25;
							position = 0;
							i = i - 1;
							score(p);
						}
						else
							if (m.Mot[position - 1] == '?') {
								//Toute les possibilité possible en cas de saisit d'un '?'
								if (i == 0) {
									//Puisque le joueur précedent correspond pas à i-1 mais à p.nombres de joueurs-1
									cout << p.participants[p.nombres_joueurs - 1].numero_joueur << p.participants[p.nombres_joueurs - 1].type_de_joueur << ", saisir le mot > ";
									if (interogation(p.nombres_joueurs - 1, p, m, position) == -2 || interogation(p.nombres_joueurs - 1, p, m, position) == 2) {
										for (unsigned int i = 0; i < m.taille_reponse; ++i) {
											cout << m.reponse[i];
										}
										cout << endl;
										if (interogation(p.nombres_joueurs - 1, p, m, position) == 2) {
											//Le robot saisie un mot qui ne commence pas par les bonnes lettres
											cout << "Le mot ";
											for (unsigned int i = 0; i < m.taille_reponse; ++i) {
												cout << m.reponse[i];
											}
											cout << " ne commence pas par les lettres attendues, le joueur";
											cout << " " << p.participants[p.nombres_joueurs - 1].numero_joueur << p.participants[p.nombres_joueurs - 1].type_de_joueur << " prend un quart de singe" << endl;
											p.participants[p.nombres_joueurs - 1].point += 0.25;
											position = 0;
											i = p.nombres_joueurs - 2;
											score(p);
										}
										if (interogation(p.nombres_joueurs - 1, p, m, position) == -2) {
											//Le robot saisie un mot cohérent
											cout << "Le mot ";
											for (unsigned int i = 0; i < m.taille_reponse; ++i) {
												cout << m.reponse[i];
											}
											cout << " existe, le joueur " << p.participants[i].numero_joueur << p.participants[i].type_de_joueur << " prend un quart de singe" << endl;
											p.participants[i].point += 0.25;
											position = 0;
											i = i - 1;
											score(p);
										}
									}
									else {
										cin >> m.reponse;
										if (interogation(p.nombres_joueurs - 1, p, m, position) == 0) {
											//L'humain saisie un mot cohérent
											gage = 1;
											cout << "Le mot ";
											afficher_mot(&m, position, gage);
											gage = 0;
											cout << " existe, le joueur " << p.participants[i].numero_joueur << p.participants[i].type_de_joueur << " prend un quart de singe" << endl;
											p.participants[i].point += 0.25;
											position = 0;
											i = i - 1;
											score(p);
										}
										if (interogation(p.nombres_joueurs - 1, p, m, position) == -1) {
											//L'humain saisie un mot qui ne commence pas par les bonnes lettres
											gage = 1;
											cout << "Le mot ";
											afficher_mot(&m, position, gage);
											cout << " ne commence pas par les lettres attendues, le joueur";
											gage = 0;
											cout << " " << p.participants[p.nombres_joueurs - 1].numero_joueur << p.participants[p.nombres_joueurs - 1].type_de_joueur << " prend un quart de singe" << endl;
											p.participants[p.nombres_joueurs - 1].point += 0.25;
											position = 0;
											i = p.nombres_joueurs - 2;
											score(p);
										}
										if (interogation(p.nombres_joueurs - 1, p, m, position) == 1) {
											//L'humain saisie un mot qui n'existe pas
											gage = 1;
											cout << "Le mot ";
											afficher_mot(&m, position, gage);
											gage = 0;
											cout << " n'existe pas, le joueur " << p.participants[p.nombres_joueurs - 1].numero_joueur << p.participants[p.nombres_joueurs - 1].type_de_joueur << " prend un quart de singe" << endl;
											p.participants[p.nombres_joueurs - 1].point += 0.25;
											position = 0;
											i = p.nombres_joueurs - 2;
											score(p);
										}
									}
								}
								else {
									cout << p.participants[i - 1].numero_joueur << p.participants[i - 1].type_de_joueur << ", saisir le mot > ";
									if (interogation(i - 1, p, m, position) == -2 || interogation(i - 1, p, m, position) == 2) {
										for (unsigned int i = 0; i < m.taille_reponse; ++i) {
											cout << m.reponse[i];
										}
										cout << endl;
										if (interogation(i - 1, p, m, position) == 2) {
											cout << "Le mot ";
											for (unsigned int i = 0; i < m.taille_reponse; ++i) {
												cout << m.reponse[i];
											}
											cout << " ne commence pas par les lettres attendues, le joueur";
											cout << " " << p.participants[i - 1].numero_joueur << p.participants[i - 1].type_de_joueur << " prend un quart de singe" << endl;
											p.participants[i - 1].point += 0.25;
											position = 0;
											i = i - 2;
											score(p);
										}
										if (interogation(i - 1, p, m, position) == -2) {
											cout << "Le mot ";
											for (unsigned int i = 0; i < m.taille_reponse; ++i) {
												cout << m.reponse[i];
											}
											cout << " existe, le joueur " << p.participants[i].numero_joueur << p.participants[i].type_de_joueur << " prend un quart de singe" << endl;
											p.participants[i].point += 0.25;
											position = 0;
											i = i - 1;
											score(p);
										}
									}
									else {
										cin >> m.reponse;
										if (interogation(i - 1, p, m, position) == 0) {
											gage = 1;
											if (i == 0) {
												cout << "Le mot ";
												afficher_mot(&m, position, gage);
												gage = 0;
												cout << " existe, le joueur " << p.participants[i].numero_joueur << p.participants[i].type_de_joueur << " prend un quart de singe" << endl;
												p.participants[i].point += 0.25;
												position = 0;
												i = i - 1;
												score(p);
											}
											else {
												cout << "Le mot ";
												afficher_mot(&m, position, gage);
												gage = 0;
												cout << " existe, le joueur " << p.participants[i].numero_joueur << p.participants[i].type_de_joueur << " prend un quart de singe" << endl;
												p.participants[i].point += 0.25;
												position = 0;
												i = i - 1;
												score(p);
											}
										}
										else
											if (interogation(i - 1, p, m, position) == -1) {
												gage = 1;
												if (i == 0) {
													cout << "Le mot ";
													afficher_mot(&m, position, gage);
													cout << " ne commence pas par les lettres attendues, le joueur";
													gage = 0;
													cout << " " << p.participants[p.nombres_joueurs - 1].numero_joueur << p.participants[p.nombres_joueurs - 1].type_de_joueur << " prend un quart de singe" << endl;
													p.participants[p.nombres_joueurs - 1].point += 0.25;
													position = 0;
													i = p.nombres_joueurs - 2;
													score(p);
												}
												else {
													cout << "Le mot ";
													afficher_mot(&m, position, gage);
													cout << " ne commence pas par les lettres attendues, le joueur";
													gage = 0;
													cout << " " << p.participants[i - 1].numero_joueur << p.participants[i - 1].type_de_joueur << " prend un quart de singe" << endl;
													p.participants[i - 1].point += 0.25;
													position = 0;
													i = i - 2;
													score(p);
												}
											}
											else
												if (interogation(i - 1, p, m, position) == -2) {
													gage = 1;
													if (i == 0) {
														cout << "Le mot ";
														afficher_mot(&m, position, gage);
														gage = 0;
														cout << " existe, le joueur " << p.participants[i].numero_joueur << p.participants[i].type_de_joueur << " prend un quart de singe" << endl;
														p.participants[i].point += 0.25;
														position = 0;
														i = i - 1;
														score(p);
													}
													else {
														cout << "Le mot ";
														afficher_mot(&m, position, gage);
														gage = 0;
														cout << " existe, le joueur " << p.participants[i].numero_joueur << p.participants[i].type_de_joueur << " prend un quart de singe" << endl;
														p.participants[i].point += 0.25;
														position = 0;
														i = i - 1;
														score(p);
													}
												}
												else {
													gage = 1;
													if (i == 0) {
														cout << "Le mot ";
														afficher_mot(&m, position, gage);
														gage = 0;
														cout << " n'existe pas, le joueur " << p.participants[p.nombres_joueurs - 1].numero_joueur << p.participants[p.nombres_joueurs - 1].type_de_joueur << " prend un quart de singe" << endl;
														p.participants[p.nombres_joueurs - 1].point += 0.25;
														position = 0;
														i = i - 2;
														score(p);
													}
													else {
														cout << "Le mot ";
														afficher_mot(&m, position, gage);
														gage = 0;
														cout << " n'existe pas, le joueur " << p.participants[i - 1].numero_joueur << p.participants[i - 1].type_de_joueur << " prend un quart de singe" << endl;
														p.participants[i - 1].point += 0.25;
														position = 0;
														i = i - 2;
														score(p);
													}
												}
									}
								}
							}

						if (comparaison(&m, i, p) == 1) {
							//Verif que la derniere lettre saisir ne permet pas de former un mot
							p.participants[i].point += 0.25;
							score(p);
							position = 0;
							i = i - 1;
						}
					}
				}
				//Sinon boucle rassemblant les commandes faisant jouer les robots
				else {
				//fais jouer le robot
					cout << p.participants[i].numero_joueur << p.participants[i].type_de_joueur << ", (";
					afficher_mot(&m, position, gage);
					cout << ") > ";
					saisie_robot(m, position, i);
					cout << m.Mot[position] << endl;
					++position;

					if (m.Mot[position - 1] == '?') {
						//Toute les possibilité possible en cas de saisit d'un '?'
						if (i == 0) {
							cout << p.participants[p.nombres_joueurs - 1].numero_joueur << p.participants[p.nombres_joueurs - 1].type_de_joueur << ", saisir le mot > ";
							if (interogation(i - 1, p, m, position) == -2 || interogation(i - 1, p, m, position) == 2) {
								for (unsigned int i = 0; i < m.taille_reponse; ++i) {
									cout << m.reponse[i];
								}
								cout << endl;
								if (interogation(i - 1, p, m, position) == 2) {
									cout << "Le mot ";
									for (unsigned int i = 0; i < m.taille_reponse; ++i) {
										cout << m.reponse[i];
									}
									cout << " ne commence pas par les lettres attendues, le joueur";
									gage = 0;
									cout << " " << p.participants[p.nombres_joueurs - 1].numero_joueur << p.participants[p.nombres_joueurs - 1].type_de_joueur << " prend un quart de singe" << endl;
									p.participants[p.nombres_joueurs - 1].point += 0.25;
									position = 0;
									i = p.nombres_joueurs - 2;
									score(p);
								}
								if (interogation(i - 1, p, m, position) == -2) {
									cout << "Le mot ";
									for (unsigned int i = 0; i < m.taille_reponse; ++i) {
										cout << m.reponse[i];
									}
									gage = 0;
									cout << " existe, le joueur " << p.participants[i].numero_joueur << p.participants[i].type_de_joueur << " prend un quart de singe" << endl;
									p.participants[i].point += 0.25;
									position = 0;
									i = i - 1;
									score(p);
								}
							}
							
						}
						else{
							cout << p.participants[i - 1].numero_joueur << p.participants[i - 1].type_de_joueur << ", saisir le mot > ";
							cin >> m.reponse;
							if (interogation(i - 1, p, m, position) == -2 || interogation(i - 1, p, m, position) == 2) {
								for (unsigned int i = 0; i < m.taille_reponse; ++i) {
									cout << m.reponse[i];
								}
								cout << endl;
								if (interogation(i - 1, p, m, position) == 2) {
									cout << "Le mot ";
									for (unsigned int i = 0; i < m.taille_reponse; ++i) {
										cout << m.reponse[i];
									}
									cout << "  ne commence pas par les lettres attendues, le joueur";
									gage = 0;
									cout << " " << p.participants[i - 1].numero_joueur << p.participants[i - 1].type_de_joueur << " prend un quart de singe" << endl;
									p.participants[i - 1].point += 0.25;
									position = 0;
									i = p.nombres_joueurs - 2;
									score(p);
								}
								if (interogation(i - 1, p, m, position) == -2) {
									cout << "Le mot ";
									for (unsigned int i = 0; i < m.taille_reponse; ++i) {
										cout << m.reponse[i];
									}
									gage = 0;
									cout << " existe, le joueur " << p.participants[i].numero_joueur << p.participants[i].type_de_joueur << " prend un quart de singe" << endl;
									p.participants[i].point += 0.25;
									position = 0;
									i = i - 1;
									score(p);
								}
							}
							else {
								if (interogation(i - 1, p, m, position) == 0) {
									gage = 1;
									if (i == 0) {
										cout << "Le mot ";
										afficher_mot(&m, position, gage);
										gage = 0;
										cout << " existe, le joueur " << p.participants[i].numero_joueur << p.participants[i].type_de_joueur << " prend un quart de singe" << endl;
										p.participants[i].point += 0.25;
										position = 0;
										i = i - 1;
										score(p);
									}
									else {
										cout << "Le mot ";
										afficher_mot(&m, position, gage);
										gage = 0;
										cout << " existe, le joueur " << p.participants[i].numero_joueur << p.participants[i].type_de_joueur << " prend un quart de singe" << endl;
										p.participants[i].point += 0.25;
										position = 0;
										i = i - 1;
										score(p);
									}
								}
								else
									if (interogation(i - 1, p, m, position) == -1) {
										gage = 1;
										if (i == 0) {
											cout << "Le mot ";
											afficher_mot(&m, position, gage);
											cout << "  ne commence pas par les lettres attendues, le joueur";
											gage = 0;
											cout << " " << p.participants[p.nombres_joueurs - 1].numero_joueur << p.participants[p.nombres_joueurs - 1].type_de_joueur << " prend un quart de singe" << endl;
											p.participants[p.nombres_joueurs - 1].point += 0.25;
											position = 0;
											i = p.nombres_joueurs - 2;
											score(p);
										}
										else {
											cout << "Le mot ";
											afficher_mot(&m, position, gage);
											cout << " ne commence pas par les lettres attendues, le joueur";								
											gage = 0;
											cout << " " << p.participants[i - 1].numero_joueur << p.participants[i - 1].type_de_joueur << " prend un quart de singe" << endl;
											p.participants[i - 1].point += 0.25;
											position = 0;
											i = i - 2;
											score(p);
										}
									}
									else
										if (interogation(i - 1, p, m, position) == -2) {
											gage = 1;
											if (i == 0) {
												cout << "Le mot ";
												afficher_mot(&m, position, gage);
												gage = 0;
												cout << " existe, le joueur " << p.participants[i].numero_joueur << p.participants[i].type_de_joueur << " prend un quart de singe" << endl;
												p.participants[i].point += 0.25;
												position = 0;
												i = i - 1;
												score(p);
											}
											else {
												cout << "Le mot ";
												afficher_mot(&m, position, gage);
												gage = 0;
												cout << " existe, le joueur " << p.participants[i].numero_joueur << p.participants[i].type_de_joueur << " prend un quart de singe" << endl;
												p.participants[i].point += 0.25;
												position = 0;
												i = i - 1;
												score(p);
											}
										}
										else {
											gage = 1;
											if (i == 0) {
												cout << "Le mot ";
												afficher_mot(&m, position, gage);
												gage = 0;
												cout << " n'existe pas, le joueur " << p.participants[p.nombres_joueurs - 1].numero_joueur << p.participants[p.nombres_joueurs - 1].type_de_joueur << " prend un quart de singe" << endl;
												p.participants[p.nombres_joueurs - 1].point += 0.25;
												position = 0;
												i = p.nombres_joueurs - 2;
												score(p);
											}
											else {
												cout << "Le mot ";
												afficher_mot(&m, position, gage);
												gage = 0;
												cout << " n'existe pas, le joueur " << p.participants[i - 1].numero_joueur << p.participants[i - 1].type_de_joueur << " prend un quart de singe" << endl;
												p.participants[i - 1].point += 0.25;
												position = 0;
												i = i - 2;
												score(p);
											}
										}
							}
						}
					}
					else
						if (comparaison(&m, i, p) == 1) {
							//Verif que la derniere lettre saisir ne permet pas de former un mot
							p.participants[i].point += 0.25;
							score(p);
							position = 0;
							i = i - 1;
						}
				}
			}
		}
		else {
			cout << "Il n'y a pas de mot faisant plus de 25 caracteres, veuillez recommencer la manche" << endl;
			position = 0;
		}
	}
}