#ifndef TEMPLATE_H_INCLUDED
#define TEMPLATE_H_INCLUDED

#include "Aetoile.h"

typedef struct t_data
{
    char** lab;
    char* map;
    int line;//coordones x du jouer (lignes)
    int column;//coordones y du jouer (colonnes)
    int energy;
    int line_treas;
    int column_treas;
}t_data;

t_case Start;// Position du depart
t_pos Treasure;// Coordonnees du Tresor

void update_lab(t_move move,t_data* data,int sizeX,int sizeY);// Fonction de mise à jour du labyrinthe
int move_player(t_data* data,t_move* move,char *labData,int *jouer ,int sizeX,int sizeY,t_typeMove move_to_do);//Fonction de deplacement avec rand
//t_typeMove get_move(t_pos Start,t_pos End,int line,int column);

#endif // TEMPLATE_H_INCLUDED
