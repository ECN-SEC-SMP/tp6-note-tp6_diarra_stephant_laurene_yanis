#include "Plateau.hpp"
#include "Controleur.hpp"
#include "Joueur.hpp"
#include "JoueurHumain.hpp"
#include <iostream>

int main()
{
	// std::cout << "Hello World !" << std::endl;

	std::cout<< "============Démarrage du jeu en cours ....============"<<std::endl;

	//Création du plateau
	Plateau plateau;

	//Affichage du plateau à l'état initial
	plateau.Affichage();

	//Création des joueurs(humains, inclure bot quant classe prete)
	JoueurHumain j1(&plateau, CouleurCercle::bleu, 1);
	JoueurHumain j2(&plateau, CouleurCercle::rouge, 2);
	Joueur *joueurs[2] = {&j1, &j2};

	//Appelle de l'orchestreur du jeu avec 2 joueurs humains
	Controleur controleur(2, &plateau, joueurs);
	
	//Lancer la partie
	controleur.runPartie();

	std::cout<< "============ \n Fin du jeu============\n"<<std::endl;

	return 0;
}
