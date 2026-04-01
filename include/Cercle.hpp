#pragma once

#include <string>

#include "TailleCercle.hpp"
#include "CouleurCercle.hpp"

/**
 * @brief Classe Cercle, pour gérer la taille et la couleur d'un cercle dans le jeu.
 */
class Cercle
{
private:
    TailleCercle taille;   // Taille du cercle : Petit, moyen ou grand
    CouleurCercle couleur; // Couleur du cercle : Bleu, jaune, rouge ou vert

public:
    /// @name Constructeurs

    /**
     * @brief Constructeur d'un cercle.
     */
    Cercle();

    /**
     * @brief Constructeur d'un cercle.
     * @param taille taille du cercle
     * @param couleur couleur du cercle
     */
    Cercle(TailleCercle taille, CouleurCercle couleur);

    /// @name Accesseurs

    /**
     * @brief Taille d'un cercle
     */
    TailleCercle getTaille();

    /**
     * @brief Couleur d'un cercle
     */
    CouleurCercle getCouleur();

    /// @name Mutateurs

    /**
     * @brief Attribue la taille d'un cercle
     * @param taille Taille d'un cercle
     */
    void setTaille(TailleCercle taille);

    /**
     * @brief Attribue la couleur d'un cercle
     * @param couleur couleur d'un cercle
     */
    void setCouleur(CouleurCercle couleur);

    /// @name Méthodes

    /**
     * @brief Affichage d'un cercle, en fonction de sa taille et de sa couleur
     */
    void AffichageCercle(int Pos_X, int Pos_Y); // Compléter avec Case.hpp

    /// @name Destructeur
};