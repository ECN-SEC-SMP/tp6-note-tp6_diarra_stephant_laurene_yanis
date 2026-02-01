#include <gtest/gtest.h>
#include "Controleur.hpp"
#include "JoueurHumain.hpp"

class FakeJoueur : public Joueur
{
public:
    FakeJoueur(Plateau *p, CouleurCercle c)
        : Joueur(p, c) {}

    Coup Jouer() override
    {
        return Coup(); // coup par défaut, on ne l’utilise pas ici
    }
};

// Exemple minimal si tu as des objets constructibles facilement
TEST(ControleurTest, NextJoueurTourneEnRond)
{
    Plateau p;
    FakeJoueur j1(&p, CouleurCercle::rouge);
    FakeJoueur j2(&p, CouleurCercle::bleu);

    Joueur *js[2] = {&j1, &j2};

    Controleur c(2, &p, js);

    c.setJoueurCourant(0);
    c.nextJoueur();
    EXPECT_EQ(c.getJoueurCourant(), 1);
    c.nextJoueur();
    EXPECT_EQ(c.getJoueurCourant(), 0);
    EXPECT_EQ(c.getJoueurs(0), &j1);
    EXPECT_EQ(c.getJoueurs(1), &j2);
}

TEST(ControleurTest, ConstructeurTropDeJoueurs) {
    Plateau p;

    FakeJoueur j1(&p, CouleurCercle::rouge);
    FakeJoueur j2(&p, CouleurCercle::bleu);
    FakeJoueur j3(&p, CouleurCercle::vert);
    FakeJoueur j4(&p, CouleurCercle::jaune);
    FakeJoueur j5(&p, CouleurCercle::rouge);
    Joueur* joueurs[5] = { &j1, &j2, &j3, &j4, &j5 };

    Controleur ctrl(5, &p, joueurs); // trop de joueurs

    EXPECT_EQ(ctrl.getNbrJoueur(), 0); 
}
TEST(ControleurTest, ConstructeurValide) {
    Plateau p;

    FakeJoueur j1(&p, CouleurCercle::rouge);
    FakeJoueur j2(&p, CouleurCercle::bleu);
    FakeJoueur j3(&p, CouleurCercle::vert);

    Joueur* joueurs[3] = { &j1, &j2, &j3 };

    Controleur ctrl(3, &p, joueurs);

    EXPECT_EQ(ctrl.getNbrJoueur(), 3);
    EXPECT_EQ(ctrl.getPlateau(), &p);
    EXPECT_EQ(ctrl.getJoueurs(0), &j1);
    EXPECT_EQ(ctrl.getJoueurs(1), &j2);
    EXPECT_EQ(ctrl.getJoueurs(2), &j3);
}