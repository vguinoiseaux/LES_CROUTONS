#include "fonctions.h"

/*
 *  fonction.c
 */

void bouger(typeElement *e, directions sens,WINDOW *boite)
{
   
    mvwprintw(boite,e->y, e->x," ");  // on efface l'element en x,y
    switch (sens)
    {
        case HAUT: 
            if (e->y>1){
                e->y=e->y-1;
            }
            break;
        case BAS: 
            if (e->y<HAUTEUR-2){
                e->y=e->y+1;
            }
            break;
        case GAUCHE: 
            if (e->x>1){
                e->x=e->x-2;
            }
            break;
        case DROITE: 
            if (e->x<LARGEUR-4){    //-1 car bord gauche prend un emplacement, -1 car bord droite prend un emplacement, et -1 avant bord droite sinonon ne peut pas alle a droite
                e->x=e->x+2;
            }
            break;
    }
    
    mvwprintw(boite,e->y, e->x,"%lc",e->symbole);// on affiche l'element en x,y
}