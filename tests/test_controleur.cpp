#include <gtest/gtest.h>
#include "Controleur.hpp"
#include "JoueurHumain.hpp"

class FakeJoueur : public Joueur
{
public:
    FakeJoueur(Plateau *p, CouleurCercle c, int id)
        : Joueur(p, c, id) {}

    Coup Jouer() override
    {
        compteur++;
        return Coup(); // coup par défaut, on ne l’utilise pas ici
    }
    int getCompteur() const { return compteur; }
    private:
    int compteur = 0;
};



TEST(ControleurTest, NextJoueurTourneEnRond)
{
    Plateau p;
    FakeJoueur j1(&p, CouleurCercle::rouge,1);
    FakeJoueur j2(&p, CouleurCercle::bleu,2);

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

    FakeJoueur j1(&p, CouleurCercle::rouge, 1);
    FakeJoueur j2(&p, CouleurCercle::bleu,2);
    FakeJoueur j3(&p, CouleurCercle::vert,3);
    FakeJoueur j4(&p, CouleurCercle::jaune,4);
    FakeJoueur j5(&p, CouleurCercle::rouge,5);
    Joueur* joueurs[5] = { &j1, &j2, &j3, &j4, &j5 };

    Controleur ctrl(5, &p, joueurs); // trop de joueurs

    EXPECT_EQ(ctrl.getNbrJoueur(), 0); 
}
TEST(ControleurTest, ConstructeurValide) {
    Plateau p;

    FakeJoueur j1(&p, CouleurCercle::rouge,1);
    FakeJoueur j2(&p, CouleurCercle::bleu,2);
    FakeJoueur j3(&p, CouleurCercle::vert,3);

    Joueur* joueurs[3] = { &j1, &j2, &j3 };

    Controleur c(3, &p, joueurs);

    EXPECT_EQ(c.getNbrJoueur(), 3);
    EXPECT_EQ(c.getPlateau(), &p);
    EXPECT_EQ(c.getJoueurs(0), &j1);
    EXPECT_EQ(c.getJoueurs(1), &j2);
    EXPECT_EQ(c.getJoueurs(2), &j3);
}
TEST(ControleurTest, NextJoueurAvecZeroJoueurNeCrashPas) {
    Controleur  c;  // constructeur par défaut → nbrJoueur = 0
    c.nextJoueur();
    EXPECT_EQ(c.getJoueurCourant(), 0);
}
TEST(ControleurTest, JouerCoupLimiteA3Tentatives) {
    Plateau p;  // placerCercle retourne toujours false avec le STUB dans PlacerCercle
    int id;
    
    FakeJoueur j(&p, CouleurCercle::rouge, id);
    Joueur* js[1] = { &j };

    Controleur C(1, &p, js);

    bool resultat = C.jouerCoup(&j);

    EXPECT_FALSE(resultat);
    EXPECT_EQ(j.getCompteur(), 3); // doit être appelé exactement 3 fois
}
