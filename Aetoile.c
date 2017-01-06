#include <stdio.h>
#include <stdlib.h>
#include "Aetoile.h"
#include <time.h>

t_case Start;
t_pos Treasure;

char** alloc_2D_array(int sizex,int sizey)
{
    char**lab=(char**)calloc(sizey,sizeof(char*));
    int i;
    for (i=0;i<sizey;i++)
    {
        lab[i]=calloc(sizex,sizeof(char));
    }
    return lab;
}

char** create_table(int line,int column)
{
    char** tab=alloc_2D_array(column,line);
    int i,j,k;
    time_t t;
    /* Intializes random number generator */
    srand((unsigned) time(&t));
    for(k=0;k<200;k++)
    {
        i=rand()%line;
        j=rand()%column;
        if(i!=7&&j!=10)tab[i][j]=1;
    }

    return tab;
}

void print_laby(char** tab,int sizeX,int sizeY)
{
    int i,j;
    for(i=0;i<sizeY;i++)
        {
            printf("\n");
            for(j=0;j<sizeX;j++)
            {
                printf("%d ",tab[i][j]);
            }
        }
}

int main()
{
    /*Treasure.line=3;
    Treasure.column=4;
    t_pos rnd={3,5};
    int d=estim_distance(rnd);
    printf("Dist :%d\n",d);*/
    //int cnt=0;
    t_pos start={0,0};
    t_pos treasure={7,10};
    int column=15;
    int line=20;
    char** tab=create_table(line,column);
    set_start(start,treasure);
    set_treasure(treasure);
    ptr_List closedList=NULL;
    ptr_List openList=malloc(sizeof(t_List));
    ptr_List path;
    openList->size_list=1;
    openList->parent_case=Start;
    openList->next_case=NULL;
    t_case c=openList->parent_case;

    while(openList!=NULL)
    {
        //printf("openListcreate:\n");
        //print_list(openList);
        //cnt++;
        c=min_case(openList);
        //printf("Heuristique openList:%d\n",openList->parent_case.heuristic);
        openList=deleteElemList(openList,c);
        //if(openList==NULL) printf("Open NULL\n");
        closedList=addElemList(closedList,c);
        //if(closedList!=NULL)printf("Closed not Null %d",closedList->parent_case.cost+3);
        if(c.pos.line==Treasure.line && c.pos.column==Treasure.column)
        {
            printf("YEAH PATH");
            //path=create_path(closedList);
            printf("YEAH PATH");
            break;
        }else
        {
            //sizeY numero de lignes
            //sizeX numero de colonnes
            openList=add_neighbor(openList,closedList,c,Treasure,column,line,tab);
            //printf("size open: %d\n",openList->size_list);
            //printf("vois1: %d\n",openList->parent_case.pos.line);
            //if(cnt>50)break;
        }

    }
    printf("\n");
    print_laby(tab,column,line);
    printf("\n");
    //set_sizeList(openList);
    printf("\nOpenList\n");
    print_list(openList,tab);
    //openList=deleteElemList(openList,openList->next_case->parent_case);
    //openList->size_list=get_sizeList(openList);
    printf("\n");
    printf("\nClosedList\n");
    print_list(closedList,tab);
    printf("\n");
    printf("\nPath\n");
    print_list(path,tab);
    free(path);
    free(openList);
    free(closedList);
    return 1;
}
/**
    ROTATE_LINE_LEFT = 	0,
	ROTATE_LINE_RIGHT = 1,
	ROTATE_COLUMN_UP = 2,
	ROTATE_COLUMN_DOWN = 3,
	MOVE_UP = 4,
	MOVE_DOWN = 5,
	MOVE_LEFT = 6,
	MOVE_RIGHT = 7,
	DO_NOTHING = 8**/
//sizeY numero de lignes
//sizeX numero de colonnes
ptr_List add_neighbor(ptr_List list,ptr_List list2,t_case c,t_pos Treasure,int sizeX,int sizeY,char** lab)
{
    t_pos n_down={(c.pos.line+1)%sizeY,c.pos.column};//voisin bas
    t_pos n_up={(c.pos.line-1+sizeY)%sizeY,c.pos.column};//voisin haut
    t_pos n_right={c.pos.line,(c.pos.column+1)%sizeX};//voisin droite
    t_pos n_left={c.pos.line,(c.pos.column-1+sizeX)%sizeX};//voisin gauche
    t_case n=nouvelle_case(c,n_down,Treasure,5);
    if(!search(list,n)&&!search(list2,n)&&!lab[(c.pos.line+1)%sizeY][c.pos.column])list=addElemList(list,n);
    n=nouvelle_case(c,n_right,Treasure,7);
    if(!search(list,n)&&!search(list2,n)&&!lab[c.pos.line][(c.pos.column+1)%sizeX])list=addElemList(list,n);
    n=nouvelle_case(c,n_left,Treasure,6);
    if(!search(list,n)&&!search(list2,n)&&!lab[c.pos.line][(c.pos.column-1+sizeX)%sizeX])list=addElemList(list,n);
    n=nouvelle_case(c,n_up,Treasure,4);
    if(!search(list,n)&&!search(list2,n)&&!lab[(c.pos.line-1+sizeY)%sizeY][c.pos.column])list=addElemList(list,n);

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
    if(list==NULL) return NULL;
    ptr_List tmp=list;
    ptr_List next=list->next_case;
    //ptr_List before=list;
    while(next!=NULL)
    {
        tmp=next;
        next=next->next_case;
    }
    if(list!=NULL)tmp->next_case=create_path(list->next_case);
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

void set_start(t_pos start,t_pos Treasure)
{
    Start.pos=start;
    Start.cost=0;
    Start.heuristic=estim_distance(start,Treasure);
    Start.pos_p.line=-1;
    Start.pos_p.column=-1;
    Start.move=8;
}
void set_treasure(t_pos treas)
{
    Treasure=treas;
}

t_case nouvelle_case(t_case c,t_pos pos,t_pos Treasure,t_typeMove move)
{
    t_case v;
    v.pos=pos;
    v.cost=c.cost+1;
    v.heuristic=v.cost+estim_distance(pos,Treasure);
    v.pos_p=c.pos;
    v.move=move;
    return v;
}

int estim_distance(t_pos x_y,t_pos Treasure)// estimation de la distance entre (x,y) et le tresor
{
    int d=0,dx,dy;
    dx=x_y.line-Treasure.line;
    if(dx<0) dx*=-1;
    dy=x_y.column-Treasure.column;
    if(dy<0) dy*=-1;
    d=dx+dy;//distance de manhattan
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
        //printf("added at beginning\n");
    }
    else
    {
        //else loop through the list and find the last
        //node, insert next to it
        ptr_List current = list;
        while (current->next_case != NULL)
        {
            current->size_list++;//=get_sizeList(current);
            //printf("size:%d\n",current->size_list);
            current = current->next_case;
        }
        current->next_case = newList;
        current->size_list++;//=newList->size_list+1;
        //printf("added later\n");
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
    //if(tempNextP!=NULL) tempNextP->size_list=get_sizeList(tempNextP);
    /* Deallocate the node. */
    free(currP);

    /*
     * Return the NEW pointer to where we
     * were called from.  I.e., the pointer
     * the previous call will use to "skip
     * over" the removed node.
     */
    //printf("delete\n");
    return tempNextP;
  }

  /*
   * Check the rest of the list, fixing the next
   * pointer in case the next node is the one
   * removed.
   */
  currP->next_case = deleteElemList(currP->next_case, value);
  if(currP!=NULL) currP->size_list=get_sizeList(currP);


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

int get_sizeList(ptr_List list)
{
    int size=0;
    if(list==NULL) return 0;
    ptr_List tmp=malloc(sizeof(list));
    tmp=list;
    while(tmp!=NULL)
    {
        size++;
        tmp=tmp->next_case;
    }
    tmp=NULL;
    free(tmp);
    return size;
}

/**ptr_List set_sizeList(ptr_List list)
{
    ptr_List tmp=malloc(sizeof(list));
    tmp=list;
    while(tmp!=NULL)
    {
        tmp->size_list=get_sizeList(tmp);
    }
    return list;
}**/

void print_list(ptr_List list,char** lab)
{
    ptr_List tmp=malloc(sizeof(list));
    int i=1;
    tmp=list;
    while(tmp!=NULL)
    {
        printf("CASE:%d ,%d:Size %d: (x:%d,y:%d),(xp:%d,yp:%d),cost:%d heur:%d,move:%d\n",lab[tmp->parent_case.pos.line][tmp->parent_case.pos.column],i++,tmp->size_list,tmp->parent_case.pos.column,tmp->parent_case.pos.line,tmp->parent_case.pos_p.line,tmp->parent_case.pos_p.column,tmp->parent_case.cost,tmp->parent_case.heuristic,tmp->parent_case.move);
        tmp=tmp->next_case;
        //i++;
    }
    tmp=NULL;
    free(tmp);
}
