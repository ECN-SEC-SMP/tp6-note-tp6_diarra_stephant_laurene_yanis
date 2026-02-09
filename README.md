# TP6 - Otrio

## Liste des participants

- André-Louis STEPHANT
- Diarra DIOP
- Laurène BERNIER
- Yanis COUSSEAU     

## Sommaire
- [Bot Yanis](#implémentation-du-bot-yanis)
- [Case AL](#case-andré-louis)
- [Cercle AL](#cercle-andré-louis)
- [Controleur Diarra](#controleur-diarra)
- [Coup Diarra](#coup-diarra)
- [Joueur Laurène](#joueur-laurène)
- [JoueurHumain Laurène](#joueurhumain-laurène)
- [Plateau André-Louis](#plateau-andré-louis)



# Implémentation du Bot Yanis

## Introduction

Pour la version 3 du projet, nous devions développer un bot capable de jouer automatiquement au jeu Otrio. Le cahier des charges demandait que le bot puisse détecter les dangers immédiats, parer les menaces adverses, et planifier au moins 3 coups en avance pour gagner.

Notre bot fonctionne selon une stratégie à trois niveaux de priorité : d'abord se défendre, ensuite chercher à gagner, et enfin jouer un coup stratégique par défaut.

L'idée était de suivre un genre d'algoritgme minimax, cependant par soucis de simplicité, nous n'avons pas anticipé les mouvements adverses.

## Architecture générale

### Héritage et polymorphisme

Le bot hérite de la classe abstraite `Joueur`, ce qui permet de l'utiliser de manière interchangeable avec un joueur humain dans le contrôleur de jeu. La méthode `Jouer()` est redéfinie pour implémenter l'intelligence artificielle.

```cpp
class Bot : public Joueur {
public:
    Coup Jouer() override;
    // ...
};
```

### Structure PlanificationVictoire

Pour gérer la planification des coups, nous avons créé une structure qui contient :
- La séquence de coups à jouer
- Le nombre de coups nécessaires (profondeur)
- Un score pour comparer différentes stratégies

```cpp
struct PlanificationVictoire {
    std::vector<Coup> coups;
    int profondeur;
    double score;
};
```

## Stratégie du bot

### Priorité 1 : Défense

Le bot commence toujours par vérifier s'il y a des menaces immédiates. Il analyse :
- Les empilements adverses (2 cercles de même couleur sur une case)
- Les alignements adverses sur les lignes, colonnes et diagonales

Si une menace est détectée, le bot calcule immédiatement une parade en bloquant la case critique. Cette défense est prioritaire sur toute autre stratégie.

### Priorité 2 : Planification offensive

Si aucune menace n'est détectée, le bot cherche comment gagner en maximum 3 coups. Il évalue toutes les possibilités :

1. **Alignements de cercles identiques** : 3 petits, 3 moyens ou 3 grands alignés
2. **Alignements ordonnés P-M-G** : petit, moyen, grand dans l'ordre
3. **Empilements** : petit, moyen et grand sur la même case

Pour chaque possibilité, le bot calcule :
- Combien de cercles sont déjà posés
- Combien de coups il faut encore jouer
- Un score pour comparer les différentes options

Le bot choisit ensuite la stratégie avec le meilleur score et joue le premier coup de la séquence planifiée.

### Priorité 3 : Coup par défaut

Si aucune stratégie de victoire n'est trouvée, le bot essaie de jouer au centre du plateau (case 2,2), ou sinon sur n'importe quelle case libre.

## Système de scoring

Pour comparer les différentes planifications, nous avons mis en place un système de scores heuristiques :

| Type de victoire | Score de base | Modificateur |
|-----------------|---------------|--------------|
| Alignement identique | 100 | -10 par coup + 5 par cercle posé |
| Alignement P-M-G | 95 | -10 par coup + 8 par cercle posé |
| Empilement | 105 | -10 par coup + 6 par cercle posé |

Les empilements ont un score de base plus élevé car ils sont plus rares et difficiles à bloquer. Le système pénalise les stratégies qui nécessitent beaucoup de coups et favorise celles où on a déjà avancé.

**Exemple** : Si on a déjà 2 petits cercles alignés, gagner en ajoutant le 3ème donne un score de : 100 - 10 + 10 = 100 points.

## Algorithmes principaux

### Détection de menaces

Pour détecter une menace, on parcourt toutes les configurations gagnantes possibles (lignes, colonnes, diagonales, empilements) et on compte les cercles adverses. Si on trouve 2 cercles de la même couleur adverse qui peuvent gagner au prochain coup, on retourne un coup de parade.

```cpp
Coup Bot::analyserAlignement(const std::vector<Case*>& cases) {
    // Compter les cercles de chaque couleur et taille
    // Si un adversaire a 2 cercles identiques alignés
    // -> Retourner un coup pour bloquer
}
```

### Planification d'alignements identiques

Cette fonction cherche s'il est possible d'aligner 3 cercles de même taille. Pour chaque taille (petit, moyen, grand), on compte combien on en a déjà posés dans l'alignement considéré. Si on peut compléter en 3 coups maximum et qu'on possède les cercles nécessaires, on construit la séquence de coups.

### Planification d'alignements ordonnés

Pour les alignements P-M-G, on vérifie quelles tailles sont déjà présentes et on identifie celles qui manquent. On construit ensuite une séquence de coups pour placer les tailles manquantes sur des cases vides de l'alignement.

**Point important** : On doit faire attention à ne pas confondre alignement et empilement. Pour un alignement, chaque cercle doit être sur une case différente, alors que pour un empilement les 3 cercles sont sur la même case.

### Planification d'empilements

Pour chaque case du plateau, on compte combien de cercles de notre couleur sont déjà empilés. Si on peut compléter l'empilement en 3 coups ou moins, on crée la planification correspondante.

## Complexité et performance

L'algorithme du bot a une complexité constante O(1) car :
- On analyse toujours le même nombre de positions (9 cases × 8 alignements)
- Pas de récursion ni de boucles dépendant de l'état du jeu
- Environ 108 opérations par tour au maximum

En pratique, le bot répond en moins d'1 milliseconde, ce qui est imperceptible pour l'utilisateur.

## Difficultés rencontrées

### Confusion entre alignement et empilement

Au début, notre fonction de planification d'alignements P-M-G plaçait les cercles sur des cases déjà occupées par nos propres cercles, créant des empilements au lieu d'alignements. Nous avons dû ajouter une vérification pour s'assurer qu'on utilise des cases différentes pour chaque cercle de l'alignement.

### Gestion des cercles disponibles

La fonction `possedeCercle()` doit vérifier dans la zone de réserve du joueur (selon sa couleur) s'il reste des cercles de la taille demandée. Nous avons dû bien gérer les coordonnées de chaque zone de réserve selon la couleur du bot.

### Choix de la meilleure stratégie

Quand plusieurs stratégies sont possibles avec des scores proches, le bot doit faire un choix cohérent. Notre système de scoring permet de toujours privilégier les victoires rapides et les positions avancées.

## Tests et validation

Nous avons créé une batterie de tests avec Google Test pour valider le comportement du bot :

- **Tests de victoire immédiate** : Vérifier que le bot gagne quand c'est possible en 1 coup
- **Tests de défense** : Vérifier que le bot bloque les menaces adverses
- **Tests de planification** : Vérifier que le bot planifie correctement sur 2-3 coups
- **Tests de cas limites** : Plateau complexe, ressources épuisées, etc.

Au total, 17 tests ont été implémentés et tous passent avec succès.

## Case André-Louis
```cpp
// Constructeurs
Case::Case()

Case::Case(int Pos_X, int Pos_Y)

// Destructeurs
Case::~Case()

// Affichage des cases, en fonction de leur position
void Case::AffichageCase(int Pos_X, int Pos_Y)
```
## Cercle André-Louis
```cpp
// Constructeurs 
Cercle::Cercle()

Cercle::Cercle(TailleCercle taille, CouleurCercle couleur)

// Affichage d'un cercle aux coordonnées données, en fonction de sa taille et de sa couleur
void Cercle::AffichageCercle(int Pos_X, int Pos_Y)
```

## Controleur Diarra
#### Role général
La classe Controleur joue le rôle d’orchestrateur de la partie.
Elle assure la coordination entre: le plateau, les joueurs, la gestion des tours, la détection des conditions de victoire.
Elle constitue le cœur de la logique de jeu.
```cpp
class Controleur {
    private:
    int nbrJoueur;
    Plateau *plateau;
    int joueurCouant;
    Joueur * joueurs[ 4 ];
    bool partieTerminee;
    public:
    Controleur();
    Controleur(int nbrJoueurs, Plateau* plateau, Joueur* joueurs[]);
    int getNbrJoueur()const;
    Plateau* getPlateau() const;
    int getJoueurCourant() const;
    Joueur* getJoueurs(int i) const;
    void setNbrJoueur(int nbrJoueurs);
    void setPlateau(Plateau* plateau);
    void setJoueurCourant(int joueurCourant);
/**
 * @brief gère le déroulement de la partie boucle prinicpale de la partie appelle un premier joueur,
* appèle gérerTour() tant que la partie n'est pas terminée, qui vérifie s'il y a victoire après chaque tour et appelle le joueur suivant
 */
    void runPartie();
/**
 * @brief Sélectionne le joueur suivant
 */
    void nextJoueur();
/**
 * @brief récupére l'action du joueur courant valide l'action via le plateau met à jour * l'état de la partie vérifie la condition de fin de partie passe au joueur suivant
 */
    void gererTour();
/**
 * @brief Vérifie via le plateau si le coup proposé par le joueur est valide .Si le coup est valide, le coup est joué sur le plateau sinon on demande au joueur de rejouer
 * @param joueur 
 */
    bool jouerCoup(Joueur* joueur); //gestion du coup joué par le joueur
    ~Controleur()= default; // Ne delete pas plateau ni joueurs : ils ne sont pas possédés ici.
};
```
Le contrôleur ne contient aucune logique de règles métier.
Il délègue les règles de placement → Plateau, la décision du coup → Joueur, l'affichage → Plateau. Pour cette raison, le traitement des 3 conditions de victoires ont été délégué au Plateau qui a accés au plateau, aux cases le constituant, ce qui facilite l'accés aux cercles.
Cela respecte le principe de séparation des responsabilités.

#### Tests unitaires
Le contrôleur a été testé avec GoogleTest sur :
- La rotation correcte des joueurs
- Le comportement en cas de trop de joueurs
- La limitation à 3 tentatives
- La gestion correcte des cas sans joueur
- La détection de victoire et arrêt de partie
#### Points forts de l’implémentation
- Architecture claire
- Bonne séparation logique
- Gestion des erreurs simple et robuste
- Tests unitaires fonctionnels

## Coup Diarra
La classe Coup a été ajoutée lors de l’implémentation de la classe Controleur.
En effet, lors de la conception du contrôleur, il est apparu plus propre et plus cohérent de représenter un coup de manière structurée plutôt que de manipuler séparément :
- une case d’origine,
- un cercle,
- une case cible.
La classe Coup encapsule ainsi toutes les informations nécessaires à l’exécution d’un déplacement.
```cpp
class Coup {
private:
    Case *origine;
    Cercle *cercle;
    Case *caseCible;
public:
    Coup();
    Coup(Case* origine, Cercle* cercle, Case* caseCible);
    Case* getOrigine();
    Cercle* getCercle();
    Case* getCaseCible();
};
```
Un objet Coup représente une action complète effectuée par un joueur :
- origine : la case depuis laquelle le cercle est déplacé
- cercle : le cercle concerné par le déplacement
- caseCible : la case vers laquelle le cercle est déplacé


Cette structure permet au contrôleur de manipuler un coup comme une entité unique.
Le contrôleur :
* Demande au joueur de proposer un coup via joueur->Jouer()
* Reçoit un objet Coup
* Transmet cet objet à plateau->placerCercle(coup)
* Vérifie la validité et exécute le déplacement

Ainsi, la classe Coup agit comme un intermédiaire entre : la décision du joueur et l’exécution par le plateau

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
```cpp
//Constructeurs
Plateau::Plateau()

// Destructeur
Plateau::~Plateau()

// Affichage du plateau (génération des cases et des cercles)
Plateau::Affichage()

// Vérification des conditions de victoire
Plateau::victoire(CouleurCercle couleur)

// Placer un cercle de son choix sur une case définie
Plateau::placerCercle(Cercle *cercle, Case *cible)

// Victoire : Empilement des trois cercles sur une même case
Plateau::victoireEmpilement(CouleurCercle couleur)

// Victoire : alignement de 3 cercles identiques
Plateau::victoireAlignementIdentique(CouleurCercle couleur)

// Victoire : alignement de 3 cercles en fonction de leur taille (P-M-G ou G-M-P)
Plateau::victoireAlignementOrdonnee(CouleurCercle couleur)
```

## Conclusion

Ce projet nous aura permis de mettre en application une grande partie des connaissances vues en cours, ainsi que dans les différents TP.

Des notions variées ont été abordées, avec pour thème central la gestion et l'utilisation des classes. Nous avons également mis en oeuvre des notions d'héritages, de tests unitaires (SEC1), de documentation doxygen, ainsi que des notions de vecteurs et d'arrays.

Certains imprévus n'ont pas pu permettre de rendre le projet à temps pour le 1/02/2026. Néanmoins, nous sommes parvenus à produire une solution fonctionnelle du cahier des charges.

Ce travail nous sera utile pour la suite de notre formation, notamment dans les futurs modules demandant d'utiliser le langage C++.


