#include "Plateau.hpp"
#include "Controleur.hpp"
#include "Joueur.hpp"
#include "JoueurHumain.hpp"
#include <iostream>

// Codes ANSI (ne touche pas au plateau)
static constexpr const char *RESET = "\033[0m";
static constexpr const char *BOLD = "\033[1m";
static constexpr const char *ROUGE = "\033[31m";
static constexpr const char *BLEU = "\033[34m";
static constexpr const char *VERT = "\033[32m";
static constexpr const char *JAUNE = "\033[33m";
static constexpr const char *CYAN = "\033[36m";

int main()
{
	std::cout << BOLD << CYAN
			  << "============ Demarrage du jeu ============\n"
			  << RESET << std::endl;

	// Création du plateau (style inchangé)
	Plateau plateau;

	std::cout << JAUNE << "Initialisation du plateau...\n"
			  << RESET << std::endl;
	plateau.Affichage();

	// Création des joueurs
	JoueurHumain j1(&plateau, CouleurCercle::bleu, 1);
	JoueurHumain j2(&plateau, CouleurCercle::rouge, 2);
	Joueur *joueurs[2] = {&j1, &j2};

	std::cout << VERT << "Joueurs crees : "
			  << BLEU << "J1 (bleu) " << RESET
			  << "vs "
			  << ROUGE << "J2 (rouge)" << RESET
			  << "\n"
			  << std::endl;

	// Controleur
	Controleur controleur(2, &plateau, joueurs);

	std::cout << BOLD << "La partie commence !\n"
			  << RESET << std::endl;

	// Lancer la partie
	controleur.runPartie();

	std::cout << BOLD << CYAN
			  << "\n============ Fin du jeu ============\n"
			  << RESET << std::endl;

	return 0;
}