#ifndef FONCTIONS_H
#define FONCTIONS_H

/*
 *  fonction.h
 */

#include <wchar.h>
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <wchar.h>
#include <wctype.h>
#include <locale.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif
#define LARGEUR 50
#define HAUTEUR 23
    typedef enum {HAUT, BAS, GAUCHE, DROITE} directions;
    typedef struct{
        int x;
        int y;
        wchar_t symbole;
    }typeElement;
    
    void bouger(typeElement *e, directions sens,WINDOW *boite);
    


#ifdef __cplusplus
}
#endif

#endif