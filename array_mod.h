#ifndef ARRAY_MOD_H_INCLUDED
#define ARRAY_MOD_H_INCLUDED

#include "template.h"
#include "labyrinthAPI.h"

/**Fonctions utilisées pour la creation et l'initialisation de la structure de données qui garde tous les informations du jeu**/
char ** init_lab(char*labdata,int sizex,int sizey);//cettte fonction creé un tableau de dimension à partir les données de labdata
char** alloc_2D_array(int sizex,int sizey);//fonction d'allocation de memoire pour un tableau de deux dimensions
t_data init_data(char*labdata,int sizex,int sizey,int player);//fonction d'initialisation d'une variable de tupe t_data
char ** copy_2Dtab( char**dest,char**sourc,int sizex,int sizey);//cette fonction return une copie d'un tableau de 2 dimensions

/**Ces fonction mes à jour le tableau quand un jouer se deplace ou fait une rotation**/
void rotation_column_up(char **laby,int value,int sizex,int sizey);
void rotation_line_left(char **laby,int value,int sizex,int sizey);
void rotation_column_down(char **laby,int value,int sizex,int sizey);
void rotation_line_right(char **laby,int value,int sizex,int sizey);
void update_lab(t_move move,t_data* data,int sizeX,int sizeY);

/**Fonction utiliser pour deboger le programme**/
char** create_table(int line,int column);//cette fonction crée un labyrinthe alleaoire
void print_laby(char** tab,int sizeX,int sizeY);//fonction d'affichage du labyrinthe
void change_tab(char** tab,t_pos* tab_cases,int size);//cette fonction modifie



#endif // ARRAY_MOD_H_INCLUDED
