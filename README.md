# TP6 - Otrio

## Liste des participants

- André-Louis STEPHANT
- Diarra DIOP
- Laurène BERNIER
- Yanis COUSSEAU     

## Sommaire
- [Bot xx](#bot-xx)
- [Case xx](#case-xx)
- [Cercle xx](#cercle-xx)
- [Controleur xx](#controleur-xx)
- [Coup xx](#coup-xx)
- [Joueur Laurène](#joueur-laurène)
- [JoueurHumain Laurène](#joueurhumain-laurène)
- [Plateau André-Louis](#plateau-andré-louis)

## Bot xx

## Case xx

## Cercle xx

## Controleur xx

## Coup xx

## Joueur Laurène
```cpp
// Constructeurs
Joueur(Plateau* plateau, CouleurCercle c, int id);

// Destructeur
virtual ~Joueur() = default;

// Méthode virtuel Jouer à définir dans JoueurHumain et dans Bot
virtual Coup Jouer()=0; //propose un coup

// Getters
CouleurCercle getCouleur() const;
int getIdJoueur()const ;
```



## JoueurHumain Laurène
```cpp
// Définition de la fonction virtuelle
Coup Jouer() override;
 
// Constructeur
JoueurHumain( Plateau *p, CouleurCercle c,int id);

// Destructeur
~JoueurHumain() = default;
```
## Plateau André-Louis


