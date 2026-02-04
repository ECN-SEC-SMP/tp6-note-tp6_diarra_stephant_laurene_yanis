#pragma once
#include <iostream>
#include "Joueur.hpp"


/**
 * @file JoueurHumain.hpp
 * @author Laurène
 * @brief Déclaration de la classe JoueurHumain
 */

/**
 * @class JoueurHumain
 * @brief Représente un joueur contrôlé par un humain.
 *
 * La classe JoueurHumain hérite de la classe Joueur.
 * Elle gère les entrées clavier de l'utilisateur afin de
 * créer un coup valide (position + taille du cercle).
 */
class JoueurHumain : public Joueur
{
private:
public:
    // Constructeur :
    /**
     * @brief Constructeur de JoueurHumain
     *
     * @param p Pointeur vers le plateau de jeu
     * @param c Couleur du joueur
     * @param id Identifiant unique du joueur
     */
    JoueurHumain( Plateau *p, CouleurCercle c,int id);

    // Définition d'une méthde virtuelle :
    /**
     * @brief Demande à l'utilisateur de jouer un coup
     *
     * Cette méthode interroge l'utilisateur via l'entrée standard
     * pour obtenir la position (ligne, colonne) ainsi que la taille
     * du cercle à jouer. Elle vérifie la validité du coup avant de
     * le retourner.
     *
     * @return Coup choisi par le joueur humain
     */
    Coup Jouer() override;

    // Destructeur :
    /**
     * @brief Destructeur de JoueurHumain
     */
    ~JoueurHumain() = default;
};
