#include <stdlib.h> // Pour rand() et srand()
#include <time.h>   // Pour time()
#include <locale.h> // Pour setlocale
#include <ncurses.h> // Pour ncurses
#include "fonctions.h"

#define MAX_MURS 300 // Augmenter la limite pour plus de murs
#define LSCORE 18  /*à définir dans fonctions.h*/
#define HSCORE 5 
#define NB_POMMES 20 // Nombre de pommes à afficher

typedef struct {
    int x, y;
} Mur;

typedef struct {
    int x, y;
} Pomme;

void reinitialiserJeu(typeElement *player1, typeElement *player2, Pomme *pommes, int *scoreROUGE, int *scoreBLEU, WINDOW *boite, Mur *murs, int nbMurs) {
    // Réinitialiser les scores
    *scoreROUGE = 0;
    *scoreBLEU = 0;

    // Réinitialiser les positions des joueurs
    player1->x = 2;
    player1->y = 2;
    player2->x = 10;
    player2->y = 15;

    // Réinitialiser les pommes
    int pommeCount = 0;
    while (pommeCount < NB_POMMES) {
        int x = rand() % (LARGEUR - 3) + 1; // Générer une coordonnée x aléatoire
        int y = rand() % (HAUTEUR - 2) + 1; // Générer une coordonnée y aléatoire

        // Vérifier que la pomme ne se superpose pas avec les murs ou les joueurs
        bool collision = false;
        for (int i = 0; i < nbMurs; i++) {
            if (murs[i].x == x && murs[i].y == y) {
                collision = true;
                break;
            }
        }
        if (player1->x == x && player1->y == y) collision = true;
        if (player2->x == x && player2->y == y) collision = true;

        // Si pas de collision, ajouter la pomme
        if (!collision) {
            pommes[pommeCount] = (Pomme){x, y};
            pommeCount++;
        }
    }

    // Effacer et redessiner le labyrinthe
    werase(boite);
    box(boite, ACS_VLINE, ACS_HLINE);
    for (int i = 0; i < nbMurs; i++) {
        mvwaddch(boite, murs[i].y, murs[i].x, '\u25AA\uFE0F');
    }
    for (int i = 0; i < NB_POMMES; i++) {
        mvwaddch(boite, pommes[i].y, pommes[i].x, '🍏'); // Utiliser un symbole de pomme
    }
    mvwprintw(boite, player1->y, player1->x, "%lc", player1->symbole);
    mvwprintw(boite, player2->y, player2->x, "%lc", player2->symbole);
    wrefresh(boite);
}

int main(int argc, char** argv) {
    typeElement player1, player2;
    WINDOW *boite;

    // Labyrinthe défini avec un tableau de murs
    Mur murs[] = {
        // Intérieur
        // petits mur haut gauche
        {10, 3}, {10, 4},
        {20, 1}, {20, 2},
        // mur vertical milieu
        {30, 1}, {30, 2}, {30, 3}, {30, 4}, {30, 5}, {30, 6},
        // mur horizontal droite
        {31, 3}, {32, 3}, {33, 3}, {34, 3}, {35, 3}, {36, 3}, {37, 3}, {38, 3}, {39, 3}, {40, 3}, {41, 3}, {42, 3}, {43, 3}, {44, 3},
        // mur vertical droite
        {44, 4}, {44, 5}, {44, 6}, {44, 7}, {44, 8}, {44, 12}, {44, 13}, {44, 14},
        {44, 15}, {44,  16}, {44, 17}, {44, 18}, {44, 19}, {44, 20},
        // tkt
        {43, 20}, {42, 20}, {41, 20}, {40, 20}, {39, 20}, {38, 20}, {37, 20}, {36, 20}, {35, 20}, {34, 20}, {33, 20}, {32, 20}, {31, 20}, {30, 20},
        {30, 19}, {30, 18}, {30, 17}, {30, 16}, {30, 15}, {30, 14},
        // 
        {35, 10}, {36, 10}, {37, 10}, {38, 10}, {39, 10}, {40, 10}, {41, 10}, {42, 10}, {43, 10}, {44, 10},
        // 
        {1, 5}, {2, 5}, {3, 5}, {4, 5}, {5, 5}, {6, 5}, {7, 5}, {8, 5}, {9, 5}, {10, 5}, {11, 5}, {12, 5}, {13, 5}, {14, 5}, {15, 5}, {16, 5}, {17, 5}, {18, 5}, {19, 5}, {20, 5},
        // 
        {1, 10}, {2, 10}, {3, 10}, {4, 10}, {5, 10}, {6, 10}, {7, 10}, {8, 10}, {9, 10}, {10, 10}, {11, 10}, {12, 10}, {13, 10}, {14, 10}, {15, 10}, {16, 10}, {17, 10}, {18, 10}, {19, 10}, {20, 10},
        // 
        {20, 21}, {20, 21}, {20, 20}, {20, 19}, {20, 18}, {20, 17}, {20, 16}, {20, 15}, {20, 14}, {20, 13},
        // 
        {1, 18}, {2, 18}, {3, 18}, {4, 18}, {5, 18}, {6, 18}, {7, 18}, {8, 18}, {9, 18}, {10, 18},
        // 
        {0, 14}, {1, 14}, {2, 14}, {3, 14}, {4, 14}, {5, 14}, {6, 14}, {7, 14}, {8, 14}, {9, 14}, {10, 14},
    };
    int nbMurs = sizeof(murs) / sizeof(Mur); // Nombre de murs définis dans le tableau

    setlocale(LC_ALL, ""); // Compatibilité d'affichage unicode sous Linux
    initscr(); // Initialise la structure WINDOW et autres paramètres

    player1.symbole = 0x1F466; // Joueur 1
    player1.x = 2;
    player1.y = 2;

    player2.symbole = 0x1F47D; // Joueur 2
    player2.x = 10;
    player2.y = 15;

    boite = subwin(stdscr, HAUTEUR, LARGEUR, 1, 1); // Boîte positionnée en 1,1 avec comme dimension LARGEURxHAUTEUR
    box(boite, ACS_VLINE, ACS_HLINE); // Dessiner le contour de la boîte

    int touche, scoreROUGE = 0, scoreBLEU = 0;
    WINDOW *boitescore;

    boitescore = subwin(stdscr, HSCORE, LSCORE, 1, 55);
    box(boitescore, ACS_VLINE, ACS_HLINE);
    mvwprintw(boitescore, 1, 1, "Score alien: %d", scoreROUGE);
    mvwprintw(boitescore, 2, 1, "Score humain: %d", scoreBLEU);
    wrefresh(boitescore);

    wrefresh(boite); // Mettre à jour l'affichage de la boîte

    mvwprintw(boite, player1.y, player1.x, "%lc", player1.symbole); // Afficher le joueur 1
    mvwprintw(boite, player2.y, player2.x, "%lc", player2.symbole); // Afficher le joueur 2

    // Initialiser le générateur de nombres aléatoires
    srand(time(NULL));

    // Créer un tableau pour les pommes
    Pomme pommes[NB_POMMES];
    int pommeCount = 0;

    while (pommeCount < NB_POMMES) {
        int x = rand() % (LARGEUR - 3) + 1; // Générer une coordonnée x aléatoire
        int y = rand() % (HAUTEUR - 2) + 1; // Générer une coordonnée y aléatoire

        // Vérifier que la pomme ne se superpose pas avec les murs ou les joueurs
        bool collision = false;
        for (int i = 0; i < nbMurs; i++) {
            if (murs[i].x == x && murs[i].y == y) {
                collision = true;
                break;
            }
        }
        if (player1.x == x && player1.y == y) collision = true;
        if (player2.x == x && player2.y == y) collision = true;

        // Si pas de collision, ajouter la pomme
        if (!collision) {
            pommes[pommeCount] = (Pomme){x, y};
            pommeCount++;
        }
    }

    // Afficher les pommes dans la boîte
    for (int i = 0; i < NB_POMMES; i++) {
        mvwaddch(boite, pommes[i].y, pommes[i].x, '🍏'); // Utiliser un symbole de pomme
    }

    curs_set(0); // Curseur invisible
    noecho(); // Pas d'écho de la touche appuyée

    nodelay(stdscr, TRUE); // Ne pas bloquer sur getch()
    do {
        touche = getch(); // Récupérer la valeur de la touche appuyée

        // Créer des copies pour tester les déplacements
        typeElement temp1 = player1;
        typeElement temp2 = player2;
        switch (touche) {
            // Joueur 1
            case 'q': bouger(&temp1, GAUCHE, boite); break;
            case 'd': bouger(&temp1, DROITE, boite); break;
            case 'z': bouger(&temp1, HAUT, boite); break;
            case 's': bouger(&temp1, BAS, boite); break;
            // Joueur 2
            case '1': bouger(&temp2, GAUCHE, boite); break;
            case '3': bouger(&temp2, DROITE, boite); break;
            case '5': bouger(&temp2, HAUT, boite); break;
            case '2': bouger(&temp2, BAS, boite); break;
        }

        // Empêcher les collisions avec les murs
        bool collisionTemp1 = false, collisionTemp2 = false;
        for (int i = 0; i < nbMurs; i++) {
            if (temp1.x == murs[i].x && temp1.y == murs[i].y) collisionTemp1 = true;
            if (temp2.x == murs[i].x && temp2.y == murs[i].y) collisionTemp2 = true;
        }

        // Gérer les collisions entre les joueurs
        if (temp1.x == player2.x && temp1.y == player2.y) collisionTemp1 = true;
        if (temp2.x == player1.x && temp2.y == player1.y) collisionTemp2 = true;

        // Appliquer les déplacements uniquement si pas de collision
        if (!collisionTemp1) player1 = temp1;
        if (!collisionTemp2) player2 = temp2;

        // Effacer et redessiner les joueurs
        werase(boite);
        box(boite, ACS_VLINE, ACS_HLINE);

        // Redessiner les murs
        for (int i = 0; i < nbMurs; i++) {
            mvwaddch(boite, murs[i].y, murs[i].x, '\u25AA\uFE0F');
        }

        // Redessiner les pommes
        for (int i = 0; i < NB_POMMES; i++) {
            mvwaddch(boite, pommes[i].y, pommes[i].x, '\U0001f451'); // Utiliser un symbole de pomme
        }

        // Vérifier si un joueur a collecté un item
        for (int i = 0; i < NB_POMMES; i++) {
            if (player1.x == pommes[i].x && player1.y == pommes[i].y || player1.x + 1 == pommes[i].x && player1.y == pommes[i].y || player1.x - 1 == pommes[i].x && player1.y == pommes[i].y) {
                scoreBLEU++; // Augmente le score du joueur bleu
                pommes[i].x = -1; // Retirer l'item
                pommes[i].y = -1;
            }
            if (player2.x == pommes[i].x && player2.y == pommes[i].y || player2.x + 1 == pommes[i].x && player2.y == pommes[i].y || player2.x - 1 == pommes[i].x && player2.y == pommes[i].y) {
                scoreROUGE++; // Augmente le score du joueur rouge
                pommes[i].x = -1; // Retirer l'item
                pommes[i].y = -1;
            }
        }

        // Mettre à jour l'affichage des scores
        mvwprintw(boitescore, 1, 1, "Score alien: %d", scoreROUGE);
        mvwprintw(boitescore, 2, 1, "Score humain: %d", scoreBLEU);
        wrefresh(boitescore);
        mvwprintw(boite, player1.y, player1.x, "%lc", player1.symbole);
        mvwprintw(boite, player2.y, player2.x, "%lc", player2.symbole);
        
        // Vérifier si un joueur a gagné
        if (scoreROUGE + scoreBLEU == NB_POMMES) {
            werase(boite);
            box(boite, ACS_VLINE, ACS_HLINE);
            if (scoreROUGE > scoreBLEU) {
                mvwprintw(boite, 10, 15, "L'alien a gagne!");
            } else if (scoreBLEU > scoreROUGE) {
                mvwprintw(boite, 10, 15, "L'humain a gagne!");
            } else {
                mvwprintw(boite, 10, 15, "Match nul!");
            }
            mvwprintw(boite, 12, 12, "Appuyez sur 'r' pour rejouer");
            mvwprintw(boite, 14, 14, "ou 'x' pour quitter");
            wrefresh(boite);

            // Attendre une entrée de l'utilisateur
            char choix;
            do {
                choix = getch();
            } while (choix != 'r' && choix != 'x');

            if (choix == 'r') {
                reinitialiserJeu(&player1, &player2, pommes, &scoreROUGE, &scoreBLEU, boite, murs, nbMurs);
            } else if (choix == 'x') {
                break; // Quitter le jeu
            }
        }

        refresh(); // Mise à jour de l'affichage
        wrefresh(boite);
    } while (touche != 'x');

    endwin(); // Remettre le terminal dans son état initial
    return (EXIT_SUCCESS);
}