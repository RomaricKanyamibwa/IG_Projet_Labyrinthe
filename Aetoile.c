#include <stdio.h>
#include <stdlib.h>
#include "Aetoile.h"


t_case Start;
t_pos Treasure;

int main()
{
    /*Treasure.x=3;
    Treasure.y=4;
    t_pos rnd={3,5};
    int d=estim_distance(rnd);
    printf("Dist :%d\n",d);*/
    ptr_List closedList=NULL;
    ptr_List openList;
    openList->size_list=1;
    openList->parent_case=Start;
    openList->next_case=NULL;


    return 1;
}


void set_start(t_pos start)
{
    Start.pos=start;
    Start.cost=0;
    Start.heuristic=estim_distance(start);
    Start.pos_p.x=-1;
    Start.pos_p.y=-1;
}
void set_treasure(t_pos treas)
{
    Treasure=treas;
}

t_case nouvelle_case(t_case c,t_pos pos)
{
    t_case v;
    v.pos=pos;
    v.cost=c.cost+1;
    v.heuristic=v.cost+estim_distance(pos);
    v.pos_p=c.pos;
    return v;
}

int estim_distance(t_pos x_y)
{
    int d=0,dx,dy;
    dx=x_y.x-Treasure.x;
    if(dx<0) dx*=-1;
    dy=x_y.y-Treasure.y;
    if(dy<0) dy*=-1;
    d=dx+dy;
    return d;
}

ptr_List addElemList(ptr_List list,t_case c)
{
    //create new node
    ptr_List newList = (t_List*)malloc(sizeof(t_List));

    if(newList == NULL)
    {
        fprintf(stderr, "Unable to allocate memory for new node\n");
        exit(-1);
    }
    newList->size_list=1;
    newList->parent_case = c;
    newList->next_case = NULL;  // Change 1

    if(list==NULL)
    {
        list=newList;
        return list;
    }

    //check for first insertion
    if(list->next_case == NULL)
    {
        list->next_case = newList;
        printf("added at beginning\n");
    }
    else
    {
        //else loop through the list and find the last
        //node, insert next to it
        ptr_List current = list;
        while (current->next_case != NULL)
        {
            current = current->next_case;
        }
        current->next_case = newList;
        printf("added later\n");
    }
    return list;
}

