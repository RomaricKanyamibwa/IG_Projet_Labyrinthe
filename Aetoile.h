#ifndef AETOILE_H_INCLUDED
#define AETOILE_H_INCLUDED

typedef struct t_pos
{
    int x;
    int y;
}t_pos;//structure de  coordonee

typedef struct t_case
{
    t_pos coord;//les coordonees de la case
    int cost;//cout pour se rendre du depart à cette case
    int heuristic;//estimation du cout total ( cost+ l'estimation de distance restante)
    t_pos coord_p;//noeud precedent

}t_case;

typedef struct t_List
{
    int size_list;//taille de la liste
    t_case parent_case;//case courante
    struct t_List* next_case;//case suivante

}t_List;

typedef t_List* ptr_List;

int estim_distance(t_pos x_y);//estimation de la distance entre la case x_y et le tresor
t_case nouvell_case(t_case c,t_pos coord);//creation de la nouvelle case à ajouter dans la liste
void addElemList(ptr_List list,t_case c);//ajout d'une case à la liste
void push(ptr_List list,t_case c);//ajout d'une case au debut de la liste
int search(ptr_List list,t_case c);//indice de la case c si elle existe dans la case
void deleteElemList(ptr_List list,t_case c);//suppression de la case c
void pop(ptr_List list);//on enleve le premier element de la liste
ptr_List copyList(ptr_List list);//on fait une copie de la liste list
t_case copyCase(t_case c);//copy de la case "c"

#endif // AETOILE_H_INCLUDED
