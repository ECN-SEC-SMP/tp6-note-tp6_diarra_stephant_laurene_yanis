#include <cassert>
#include <iostream>

#include "Case.hpp"
#include "CouleurCercle.hpp"
#include "TailleCercle.hpp"
#include "Plateau.hpp"

// Constructeurs
Plateau::Plateau() {        
    //Instancier toutes les cases du plateau
    for(int y = 0; y < 5; y++) {
        for(int x = 0; x < 5; x++) {
            //Ne pas instancier les coins
            if((y == 0 || y == 4) && (x == 0 || x == 4)) {
                cases[x][y] = nullptr;
                continue;
            }

            cases[x][y] = new Case(x, y);

            //Initialiser la case avec des cercles si besoin
            if(y == 0) {
                //TODO: Moche de ouf
                cases[x][y]->setCercles(new Cercle(TailleCercle::grande, CouleurCercle::bleu), TailleCercle::grande);
                cases[x][y]->setCercles(new Cercle(TailleCercle::moyenne, CouleurCercle::bleu), TailleCercle::moyenne);
                cases[x][y]->setCercles(new Cercle(TailleCercle::petite, CouleurCercle::bleu), TailleCercle::petite);
            } else if(y == 4) {
                cases[x][y]->setCercles(new Cercle(TailleCercle::grande, CouleurCercle::rouge), TailleCercle::grande);
                cases[x][y]->setCercles(new Cercle(TailleCercle::moyenne, CouleurCercle::rouge), TailleCercle::moyenne);
                cases[x][y]->setCercles(new Cercle(TailleCercle::petite, CouleurCercle::rouge), TailleCercle::petite);
            } else if(x == 0) {
                cases[x][y]->setCercles(new Cercle(TailleCercle::grande, CouleurCercle::jaune), TailleCercle::grande);
                cases[x][y]->setCercles(new Cercle(TailleCercle::moyenne, CouleurCercle::jaune), TailleCercle::moyenne);
                cases[x][y]->setCercles(new Cercle(TailleCercle::petite, CouleurCercle::jaune), TailleCercle::petite);
            } else if(x == 4) {
                cases[x][y]->setCercles(new Cercle(TailleCercle::grande, CouleurCercle::vert), TailleCercle::grande);
                cases[x][y]->setCercles(new Cercle(TailleCercle::moyenne, CouleurCercle::vert), TailleCercle::moyenne);
                cases[x][y]->setCercles(new Cercle(TailleCercle::petite, CouleurCercle::vert), TailleCercle::petite);
            }
        }
    }
}

Plateau::~Plateau() {
    //Détruire toutes les instances de case
    for(int x = 0; x < 5; x++) {
        for(int y = 0; y < 5; y++) {
            Case* c = cases[x][y];
            if(c) {
                delete c;
            }
        }
    }
}

// Accesseur
Case* Plateau::getCase(int x, int y) {
    //Validation des entrées
    assert(x >= 0 && x<5);
    assert(y >= 0 && y<5);
    return cases[x][y];
}

// Méthodes
void Plateau::Affichage() {
    // Buffer pour stocker les lignes
    std::vector<std::string> buffer(7, "");  // 7 lignes pour une case (0-6)
    
    for(int y = 0; y < 5; y++) {
        for(int x = 0; x < 5; x++) {
            if(cases[x][y]) {
                cases[x][y]->AffichageCase(buffer, 0);
            } 
        }
        // Afficher les 7 lignes du plateau actuel
        for(const auto& ligne : buffer) {
            std::cout << ligne << std::endl;
        }
        // Réinitialiser le buffer pour la prochaine rangée
        buffer.assign(7, "");
    }
}

bool Plateau::placerCercle(Cercle* cercle, Case* cible) {
    //TODO: STUB
    return false;
}

bool Plateau::victoire(CouleurCercle couleur) {
    //TODO: STUB
    return false;
}
