#include <stdio.h>
#include <stdlib.h>
#include "Aetoile.h"


t_case Start;
t_pos Treasure;

int main()
{
    /*Treasure.line=3;
    Treasure.column=4;
    t_pos rnd={3,5};
    int d=estim_distance(rnd);
    printf("Dist :%d\n",d);*/
    t_pos start={0,0};
    t_pos Treasure={10,11};
    set_start(start);
    set_treasure(Treasure);
    ptr_List closedList=NULL;
    ptr_List openList=malloc(sizeof(t_List));
    ptr_List path;
    openList->size_list=1;
    openList->parent_case=Start;
    openList->next_case=NULL;
    t_case c=openList->parent_case;

    while(openList)
    {
        c=min_case(openList);
        //printf("Heuristique openList:%d\n",openList->parent_case.heuristic);
        openList=deleteElemList(openList,c);
        //if(openList==NULL) printf("Open NULL\n");
        closedList=addElemList(closedList,c);
        //if(closedList!=NULL)printf("Closed not Null %d",closedList->parent_case.cost+3);
        if(c.pos.line==Treasure.line && c.pos.column==Treasure.column)
        {
            path=create_path(closedList);
        }else
        {
            openList=add_neighbor(openList,closedList,c,100,100);
            printf("size open: %d\n",openList->size_list);
            printf("vois1: %d\n",openList->parent_case.pos.line);
            //break;
        }


    }


    return 1;
}


ptr_List add_neighbor(ptr_List list,ptr_List list2,t_case c,int sizeX,int sizeY)
{
    t_pos n_down={(c.pos.line+1)%sizeY,c.pos.column};
    t_pos n_up={(c.pos.line-1+sizeY)%sizeY,c.pos.column};
    t_pos n_right={c.pos.line,(c.pos.column+1)%sizeX};
    t_pos n_left={c.pos.line,(c.pos.column-1+sizeX)%sizeX};
    t_case n=nouvelle_case(c,n_down);
    if(!search(list,n)&&!search(list2,n))list=addElemList(list,n);
    n=nouvelle_case(c,n_right);
    if(!search(list,n)&&!search(list2,n))list=addElemList(list,n);
    n=nouvelle_case(c,n_left);
    if(!search(list,n)&&!search(list2,n))list=addElemList(list,n);
    n=nouvelle_case(c,n_up);
    if(!search(list,n)&&!search(list2,n))list=addElemList(list,n);

    return list;
}

int search(ptr_List list,t_case value)
{
  if (list == NULL)
    return 0;

  if (comp_case(list->parent_case,value))
   {
    return 1;
  }
  return search(list->next_case,value);
}


ptr_List create_path(ptr_List list)
{
    ptr_List tmp=malloc(sizeof(t_List));


    return tmp;

}

t_case min_case(ptr_List list)
{
    t_case min=list->parent_case;
    ptr_List tmp=list->next_case;
    while(tmp!=NULL)
    {
        if (min.heuristic>=tmp->parent_case.heuristic)
            min=tmp->parent_case;
        tmp=tmp->next_case;
    }
    return min;
}

void set_start(t_pos start)
{
    Start.pos=start;
    Start.cost=0;
    Start.heuristic=estim_distance(start);
    Start.pos_p.line=-1;
    Start.pos_p.column=-1;
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
    dx=x_y.line-Treasure.line;
    if(dx<0) dx*=-1;
    dy=x_y.column-Treasure.column;
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
        list->size_list++;
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
            current->size_list++;
            current = current->next_case;
        }
        current->next_case = newList;
        printf("added later\n");
    }
    return list;
}

ptr_List deleteElemList(ptr_List currP, t_case value)
{
  /* See if we are at end of list. */
  if (currP == NULL)
    return NULL;

  /*
   * Check to see if current node is one
   * to be deleted.
   */
  if (comp_case(currP->parent_case,value))
   {
    ptr_List tempNextP;

    /* Save the next pointer in the node. */
    tempNextP = currP->next_case;

    /* Deallocate the node. */
    free(currP);

    /*
     * Return the NEW pointer to where we
     * were called from.  I.e., the pointer
     * the previous call will use to "skip
     * over" the removed node.
     */
    return tempNextP;
  }

  /*
   * Check the rest of the list, fixing the next
   * pointer in case the next node is the one
   * removed.
   */
  currP->next_case = deleteElemList(currP->next_case, value);


  /*
   * Return the pointer to where we were called
   * from.  Since we did not remove this node it
   * will be the same.
   */
  return currP;
}


int comp_case(t_case c1,t_case c2)
{
    if (c1.cost==c2.cost && c1.heuristic==c2.heuristic && c1.pos.line==c2.pos.line && c1.pos.column==c2.pos.column
    && c1.pos_p.line==c2.pos_p.line && c1.pos_p.column==c2.pos_p.column )
        return 1;
    return 0;
}

int comp_2case(t_case c1,t_case c2)
{
    if ( c1.heuristic==c2.heuristic  )
        return 0;
    if ( c1.heuristic<c2.heuristic  )
        return 1;
    return -1;
}
