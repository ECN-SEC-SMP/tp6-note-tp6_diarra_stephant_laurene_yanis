#pragma once

#include "CouleurCercle.hpp"
#include "Coup.hpp"
#include "Plateau.hpp"


/**
 * @file Joueur.hpp
 * @author Laurène
 * @brief Déclaration de la classe abstraite Joueur
 */

/**
 * @class Joueur
 * @brief Classe abstraite représentant un joueur du jeu.
 *
 * La classe Joueur définit l'interface commune à tous les types de joueurs
 * (joueur humain ou bot). Elle contient les informations communes telles que
 * la couleur, l'identifiant et l'accès au plateau de jeu.
 *
 * La méthode virtuelle pure Jouer() doit être implémentée par les classes
 * dérivées.
 */
class Joueur {
        
    protected:
        /** Couleur associée au joueur */
        CouleurCercle  Couleur;
        /** Pointeur vers le plateau de jeu */
        Plateau* plateau;
        /** Identifiant unique du joueur */
        int idJoueur;

    public :
        // Constructeurs
        /**
         * @brief Constructeur de la classe Joueur
         *
         * @param plateau Pointeur vers le plateau de jeu
         * @param c Couleur associée au joueur
         * @param id Identifiant unique du joueur
         */
        Joueur(Plateau* plateau, CouleurCercle c, int id);


        /**
         * @brief Destructeur virtuel de Joueur
         *
         * Nécessaire pour garantir une destruction correcte
         * des objets dérivés via un pointeur de type Joueur.
         */
        virtual ~Joueur() = default;


        // méthode virtuel Jouer à définir dans JoueurHumain et dans Bot
        /**
         * @brief Propose un coup à jouer
         *
         * Méthode virtuelle pure à implémenter dans les classes dérivées
         * (JoueurHumain, Bot, etc.).
         *
         * @return Coup proposé par le joueur
         */
        virtual Coup Jouer()=0; //propose un coup

        //getters
        /**
         * @brief Retourne la couleur du joueur
         *
         * @return CouleurCercle associée au joueur
         */
        CouleurCercle getCouleur() const;

         /**
         * @brief Retourne l'identifiant du joueur
         *
         * @return Identifiant unique du joueur
         */
        int getIdJoueur()const ;
};


