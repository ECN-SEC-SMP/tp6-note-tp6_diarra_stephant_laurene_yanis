#pragma once

#include <string>
#include <array>
#include <vector>

#include "Cercle.hpp"

/**
 * @brief Classe case, pour la gestion d'une case du tableau.
 * Une case contient jusqu'à trois cercles d'une taille différente.
 */
class Case
{
private:
    int Pos_X;                       // Position X
    int Pos_Y;                       // Position Y
    std::array<Cercle *, 3> cercles; // Nombre de cercles possibles dans une case

public:
    /// @name Constructeurs

    /**
     * @brief Constructeur d'une case.
     */
    Case();

    /**
     * @brief Constructeur d'une case.
     * @param Pos_X Coordonnée X.
     * @param Pos_Y Coordonnée Y.
     */
    Case(int Pos_X, int Pos_Y);

    /// @name Accesseurs

    /**
     * @brief Position X de la case
     */
    int getPosX();

    /**
     * @brief Position Y de la case
     */
    int getPosY();

    /**
     * @brief Retourne l'ensemble des cercles
     */
    std::array<Cercle *, 3> getCercles();

    /// @name Mutateurs

    /**
     * @brief Attribue la X de la case
     * @param Pos_X Coordonnée X.
     */
    void setPosX(int Pos_X);

    /**
     * @brief Attribue la Y de la case
     * @param Pos_Y Coordonnée Y.
     */
    void setPosY(int Pos_Y);

    /**
     * @brief Ajoute un cercle à un index défini dans une case
     * @param cercle pointeur vers un cercle
     * @param index index d'ajout
     */
    void setCercles(Cercle *cercle, int index);

    /// @name Méthodes

    /**
     * @brief Affichage d'une case et des cercles à l'intérieur (s'il y en a)
     */
    void AffichageCase(std::vector<std::string> &buffer, int startLine);

    /// @name Destructeurs
    ~Case();
};