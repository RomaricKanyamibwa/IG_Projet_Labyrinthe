#ifndef AETOILE_H_INCLUDED
#define AETOILE_H_INCLUDED

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

}t_List;

typedef t_List* ptr_List;

void set_start(t_pos start);//position du debut
void set_treasure(t_pos treas);//definition de la position du tresor
int estim_distance(t_pos x_y);//estimation de la distance entre la case x_y et le tresor
t_case nouvelle_case(t_case c,t_pos pos);//creation de la nouvelle case à ajouter dans la liste
ptr_List addElemList(ptr_List list,t_case c);//ajout d'une case à la liste
ptr_List push(ptr_List list,t_case c);//ajout d'une case au debut de la liste
int search(ptr_List list,t_case value);//recherche si value dans list
ptr_List deleteElemList(ptr_List list,t_case c);//suppression de la case c
ptr_List pop(ptr_List list);//on enleve le premier element de la liste
ptr_List copyList(ptr_List list);//on fait une copie de la liste list
t_case copyCase(t_case c);//copy de la case "c"
int comp_case(t_case c1,t_case c2);//comparaison de deux cases,on renvoi 1 si c1=c2 0 sinon
t_case min_case(ptr_List list);//min case de la list
int comp_2case(t_case c1,t_case c2);//
ptr_List create_path(ptr_List list);//reconstituer le chemin
ptr_List add_neighbor(ptr_List list,ptr_List list2,t_case c,int sizeX,int sizeY);//les voisins de c
void print_list(ptr_List list);//fonction d'affichage d'une list
int get_sizeList(ptr_List list);//taille d'une list
//ptr_List set_sizeList(ptr_List list);//definit la taille de la liste
#endif // AETOILE_H_INCLUDED
