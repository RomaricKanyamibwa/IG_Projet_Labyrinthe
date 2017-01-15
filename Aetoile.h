#ifndef AETOILE_H_INCLUDED
#define AETOILE_H_INCLUDED

#include "labyrinthAPI.h"

/**Structure pour A* **/

typedef struct t_pos
{
    int line;
    int column;
}t_pos;//structure de  coordonee


typedef struct t_case
{
    t_pos pos;//les coordonees de la case
    int cost;//cout pour se rendre du depart à cette case
    int heuristic;//estimation du cout total ( cost+ l'estimation de distance restante)
    t_pos pos_p;//noeud precedent

}t_case;

typedef struct t_List
{
    int size_list;//taille de la liste
    t_case parent_case;//case courante
    struct t_List* next_case;//case suivante

}t_List;//la structure de la Closed/Open list

typedef t_List* ptr_List;

/** Fonction pour le A* **/

t_typeMove* listmoves(t_pos* path,int size_path,int line,int column);//cette fonction retourne la liste de mouvements à faire pour faire le chemin path
t_typeMove get_move(t_pos Start,t_pos End,int line,int column);//Le mouvement à effectuer
ptr_List get_closedList(int line,int column,t_pos start,t_pos treasure,char** tab,int* found_path);//Cette fonction construit la closedList
void set_start(t_pos start,t_pos Treasure);//position du debut
void set_treasure(t_pos treas);//definition de la position du tresor
int estim_distance(t_pos x_y,t_pos Treasure);//estimation de la distance entre la case x_y et le tresor
t_case nouvelle_case(t_case c,t_pos pos,t_pos Treasure);//creation de la nouvelle case à ajouter dans la liste
ptr_List addElemList(ptr_List list,t_case c);//ajout d'une case à la liste
int search(ptr_List list,t_case value);//recherche si value dans list
ptr_List deleteElemList(ptr_List list,t_case c);//suppression de la case c
int comp_case(t_case c1,t_case c2);//comparaison de deux cases,on renvoi 1 si c1=c2 0 sinon
t_case min_case(ptr_List list);//min case de la list
int comp_2case(t_case c1,t_case c2);//2eme fonction de comparaison des cases
t_pos* create_path(ptr_List list,int* size_path);//reconstituer le chemin ,size_path est l taille du chemin
ptr_List add_neighbor(ptr_List list,ptr_List list2,t_case c,t_pos Treasure,int sizeX,int sizeY,char** lab);//les voisins de c
void print_list(ptr_List list,char** lab);//fonction d'affichage d'une list
int get_sizeList(ptr_List list);//taille d'une list
int search_path(t_pos* path,t_pos x_y,int size);//recherche si x_y est dans le path (renvoie 1 si x_y dans le path 0 sinon)
//ptr_List set_sizeList(ptr_List list);//definit la taille de la liste
#endif // AETOILE_H_INCLUDED
