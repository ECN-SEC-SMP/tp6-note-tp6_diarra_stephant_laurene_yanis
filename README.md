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

# Implémentation du Bot

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


