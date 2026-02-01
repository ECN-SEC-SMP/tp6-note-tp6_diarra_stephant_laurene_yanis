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

int Controleur::getNbrJoueur()
{
    return nbrJoueur;
}

Plateau *Controleur::getPlateau()
{
    return plateau;
}

int Controleur::getJoueurCourant()
{
    return joueurCouant;
}

Joueur *Controleur::getJoueurs(int i)
{
    return joueurs[i];
}

Joueur *Controleur::getlistJoueurs()
{
    if (nbrJoueur > 0)
    {
        return joueurs[0];
    }
    return nullptr;
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
    joueurCouant = (joueurCouant + 1) % nbrJoueur; // passe au joueur suivant de façon circulaire
}

void Controleur::jouerCoup(Joueur *joueur)
{
    while (true)
    {
        Coup propal = joueur->Jouer();                                                      // récupère le coup proposé par le joueur
        bool coupValide = plateau->placerCercle(propal.getCercle(), propal.getCaseCible()); // vérifie et place si valide
        if (coupValide)
        {
            // Mettre à jour l'affichage global du plateau
            plateau->Affichage();
            break;
        }
        else
        {
            cout << "Coup invalide, veuillez rejouer." << endl;
        }
    }
}

void Controleur::gererTour()
{
    if (nbrJoueur <= 0 || plateau == nullptr)
        return;

    cout << "C'est au joueur " << joueurs[joueurCouant]->getIdJoueur() << " de jouer." << endl;
    jouerCoup(joueurs[joueurCouant]);

    // Vérifier la condition de victoire après le coup
    if (plateau->victoire(joueurs[joueurCouant]->getCouleur()))
    {
        partieTerminee = true;
        cout << "Le joueur " << joueurs[joueurCouant]->getIdJoueur() << " a gagné !" << endl;
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
        gererTour();          // gère le tour du joueur courant (et avance si nécessaire)
    }
}
