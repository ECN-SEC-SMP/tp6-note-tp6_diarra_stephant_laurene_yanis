#include <cstdlib> // Pour rand et srand
#include <ctime>

#include <iostream>
using namespace std;

#include "Controleur.hpp"
#include "Coup.hpp"
/*-------------------------------------------------------------------------------*/
// Constructeurs
/*-------------------------------------------------------------------------------*/
Controleur::Controleur()
{
    nbrJoueur = 0;
    this->plateau = nullptr;
    joueurCouant = 0;
    partieTerminee = false;
}

Controleur::Controleur(int nbrJoueurs, Plateau *plateau, Joueur *joueurs[])
{
    this->nbrJoueur = nbrJoueurs;
    this->plateau = plateau;
    this->joueurCouant = 0;
    if (!plateau)
        throw std::invalid_argument("plateau null");
    if (nbrJoueurs < 1 || nbrJoueurs > 4)
        throw std::invalid_argument("nb joueurs invalide");

    for (int i = 0; i < nbrJoueurs; i++)
    {
        this->joueurs[i] = joueurs[i];
    }
    partieTerminee = false;
}
/*-------------------------------------------------------------------------------*/
// Getters
/*-------------------------------------------------------------------------------*/

int Controleur::getNbrJoueur() const
{
    return nbrJoueur;
}

Plateau *Controleur::getPlateau() const
{
    return plateau;
}

int Controleur::getJoueurCourant() const
{
    return joueurCouant;
}

Joueur *Controleur::getJoueurs(int i) const
{
    return joueurs[i];
}

/*-------------------------------------------------------------------------------*/
// Setters
/*-------------------------------------------------------------------------------*/
void Controleur::setNbrJoueur(int nbrJoueurs)
{
    nbrJoueur = nbrJoueurs;
}

void Controleur::setPlateau(Plateau *plateau)
{
    this->plateau = plateau;
}

void Controleur::setJoueurCourant(int joueurCourant)
{
    joueurCouant = joueurCourant;
}
/*-------------------------------------------------------------------------------*/
// Méthodes de la classe
/*-------------------------------------------------------------------------------*/
void Controleur::nextJoueur()
{
    if (nbrJoueur <= 0)
        return;
    joueurCouant = (joueurCouant + 1) % nbrJoueur; // passe au joueur suivant de façon circulaire
}

bool Controleur::jouerCoup(Joueur *joueur)
{
    if (!joueur || !plateau)
        return false;
    int maxEssais = 3;
    for (int essai = 0; essai < maxEssais; essai++)
    {
        Coup propal = joueur->Jouer();                                                      // récupère le coup proposé par le joueur
        bool coupValide = plateau->placerCercle(propal); // vérifie et place si valide
        if (coupValide)
        {
            return true; // Coup valide et joué
        }
        cout << "Coup invalide, veuillez rejouer." << endl;
        cout << "Il vous reste " << (maxEssais - essai - 1) << " essais." << endl;
    }
    cout << "Trop de tentatives invalides. Tour annulé." << endl;
    return false;
}


void Controleur::gererTour()
{
    if (nbrJoueur <= 0 || plateau == nullptr)
        return;
    Joueur *jC = joueurs[joueurCouant];
    if (jC == nullptr)
    {
        cout << "Erreur: joueur courant invalide." << endl;
        nextJoueur();
        return;
    }
    cout << "C'est au joueur " << jC->getIdJoueur() << " de jouer." << endl;
    bool ok = jouerCoup(jC);
    if (!ok)
    {
        cout << "Le joueur " << jC->getIdJoueur() << " a fait 3 tentatives invalides." << endl;
        nextJoueur();
        return;
    }
    // Vérifier la condition de victoire après le coup
    if (plateau->victoire(jC->getCouleur()))
    {
        partieTerminee = true;
        cout << "Le joueur " << jC->getIdJoueur() << " a gagné !" << endl;
    }
    else
    {
        nextJoueur();
    }
}

void Controleur::runPartie()
{
    if (nbrJoueur <= 0 || plateau == nullptr)
        return;
    // Détermination du premier joueur de façon aléatoire
    srand((unsigned)time(NULL));
    joueurCouant = rand() % nbrJoueur; // génère 0..nbrJoueur-1

    while (!partieTerminee)
    {
        plateau->Affichage(); // affiche le plateau
        gererTour();          // gère le tour du joueur courant: JouerCoup, vérifier victoire, nextJoueur
    }
}
