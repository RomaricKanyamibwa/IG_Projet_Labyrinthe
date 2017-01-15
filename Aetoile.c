#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "array_mod.h"
#include "Aetoile.h"

t_case Start;
t_pos Treasure;



t_typeMove* listmoves(t_pos* path,int size_path,int line,int column)
{
        //if(size_path<1) return NULL;
        t_typeMove* listMoves=(t_typeMove*)calloc(size_path,sizeof(t_typeMove));
        if(listMoves == NULL)
        {
            fprintf(stderr, "Unable to allocate memory for new listmove\n");
            exit(-1);
        }
        int i=0,j=size_path;
        for(i=size_path;i>0;i--)
        {

            listMoves[i-1]=get_move(path[i-2],path[j-1],line,column);
            if(listMoves[i-1]!=-1) j=i-1;
            else j=j;
            if(i!=size_path)
            {
                if(listMoves[i]==MOVE_DOWN&&listMoves[i-1]==MOVE_UP) {listMoves[i-1]=-1;listMoves[i]=-1;}
                if(listMoves[i]==MOVE_UP&&listMoves[i-1]==MOVE_DOWN) {listMoves[i-1]=-1;listMoves[i]=-1;}
                if(listMoves[i]==MOVE_LEFT&&listMoves[i-1]==MOVE_RIGHT) {listMoves[i-1]=-1;listMoves[i]=-1;}
                if(listMoves[i]==MOVE_RIGHT&&listMoves[i-1]==MOVE_LEFT) {listMoves[i-1]=-1;listMoves[i]=-1;}
            }

        }
        listMoves[0]=-1;
        /*for(i=0;i<size_path;i++)
        {
            if(listMoves[i]==MOVE_DOWN)printf("Down\n");
            else if(listMoves[i]==MOVE_LEFT)printf("Left\n");
                else if(listMoves[i]==MOVE_RIGHT)printf("Right\n");
                    else if(listMoves[i]==MOVE_UP)printf("UP\n");
                        //else printf("Ignore\n");
        }*/
        return listMoves;
}

t_typeMove get_move(t_pos Start,t_pos End,int line,int column)
{
    if(Start.column-End.column==1&&Start.line-End.line==0) return MOVE_LEFT;
    if(Start.column-End.column==-1&&Start.line-End.line==0) return MOVE_RIGHT;
    if(Start.line-End.line==1&&Start.column-End.column==0) return MOVE_UP;
    if(Start.line-End.line==-1&&Start.column-End.column==0) return MOVE_DOWN;
    if(Start.column-End.column==-(column-1)&&Start.line-End.line==0) return MOVE_LEFT;
    if(Start.column-End.column==(column-1)&&Start.line-End.line==0) return MOVE_RIGHT;
    if(Start.line-End.line==-(line-1)&&Start.column-End.column==0) return MOVE_UP;
    if(Start.line-End.line==(line-1)&&Start.column-End.column==0) return MOVE_DOWN;
    return -1;
}



ptr_List get_closedList(int line,int column,t_pos start,t_pos treasure,char** tab,int* found_path)
{
    set_start(start,treasure);
    set_treasure(treasure);
    ptr_List closedList=NULL;
    ptr_List openList=calloc(1,sizeof(t_List));
    if(openList == NULL)
    {
        fprintf(stderr, "Unable to allocate memory for new list\n");
        exit(-1);
    }
    openList->size_list=1;
    openList->parent_case=Start;
    openList->next_case=NULL;
    //print_list(openList,tab);
    t_case c=openList->parent_case;
    while(openList!=NULL)
    {
        c=min_case(openList);
        openList=deleteElemList(openList,c);
        closedList=addElemList(closedList,c);
        if(c.pos.line==Treasure.line && c.pos.column==Treasure.column)
        {
            *found_path=1;
            free(openList);
            return closedList;
        }else
        {
            openList=add_neighbor(openList,closedList,c,Treasure,column,line,tab);

        }

    }
    free(openList);
    return closedList;

}


//sizeY numero de lignes
//sizeX numero de colonnes
ptr_List add_neighbor(ptr_List list,ptr_List list2,t_case c,t_pos Treasure,int sizeX,int sizeY,char** lab)
{
    t_pos n_down={(c.pos.line+1)%sizeY,c.pos.column};//voisin bas
    t_pos n_up={(c.pos.line-1+sizeY)%sizeY,c.pos.column};//voisin haut
    t_pos n_right={c.pos.line,(c.pos.column+1)%sizeX};//voisin droite
    t_pos n_left={c.pos.line,(c.pos.column-1+sizeX)%sizeX};//voisin gauche
    t_case n=nouvelle_case(c,n_down,Treasure);
    if(!search(list,n)&&!search(list2,n)&&!lab[(c.pos.line+1)%sizeY][c.pos.column])list=addElemList(list,n);
    n=nouvelle_case(c,n_right,Treasure);
    if(!search(list,n)&&!search(list2,n)&&!lab[c.pos.line][(c.pos.column+1)%sizeX])list=addElemList(list,n);
    n=nouvelle_case(c,n_left,Treasure);
    if(!search(list,n)&&!search(list2,n)&&!lab[c.pos.line][(c.pos.column-1+sizeX)%sizeX])list=addElemList(list,n);
    n=nouvelle_case(c,n_up,Treasure);
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


t_pos* create_path(ptr_List list,int* size_path)
{
    if(list==NULL) return NULL;
    ptr_List prec=list;
    ptr_List tmp=list->next_case;
    t_pos* path;
    if(tmp!=NULL) path=calloc(tmp->size_list+1,sizeof(t_pos));
    else path=malloc(sizeof(t_pos)*1);
    if(path == NULL)
    {
        fprintf(stderr, "Unable to allocate memory for new path\n");
        exit(-1);
    }
    int i=0;
    tmp=list->next_case;
    while(tmp!=NULL)
    {
        if(!search_path(path,tmp->parent_case.pos_p,i+1)||(tmp->parent_case.pos_p.column==list->parent_case.pos.column&&tmp->parent_case.pos_p.line==list->parent_case.pos.line))
            path[i++]=tmp->parent_case.pos_p;
        prec=tmp;
        tmp=tmp->next_case;
    }
    path[i]=prec->parent_case.pos;
    *size_path=i+1;
    return path;

}

int search_path(t_pos* path,t_pos x_y,int size)
{
    int i;
    for(i=0;i<size;i++)
        if(path[i].column==x_y.column&&path[i].line==x_y.line) return 1;
    return 0;
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
}
void set_treasure(t_pos treas)
{
    Treasure=treas;
}

t_case nouvelle_case(t_case c,t_pos pos,t_pos Treasure)
{
    t_case v;
    v.pos=pos;
    v.cost=c.cost+1;
    v.heuristic=v.cost+estim_distance(pos,Treasure);
    v.pos_p=c.pos;
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
        fprintf(stderr, "AddElementError:Unable to allocate memory for new List\n");
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
  if (currP == NULL)
    return NULL;

  if (comp_case(currP->parent_case,value))
   {
    ptr_List tempNextP;
    tempNextP = currP->next_case;

    free(currP);

    return tempNextP;
  }

  currP->next_case = deleteElemList(currP->next_case, value);
  if(currP!=NULL) currP->size_list=get_sizeList(currP);

  return currP;
}


int comp_case(t_case c1,t_case c2)
{
    if (c1.pos.line==c2.pos.line && c1.pos.column==c2.pos.column)
        return 1
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
    if(tmp == NULL)
    {
        fprintf(stderr, "Getsize:Unable to allocate memory for new list\n");
        exit(-1);
    }
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

void print_list(ptr_List list,char** lab)
{
    ptr_List tmp=malloc(sizeof(list));
    if(tmp == NULL)
    {
        fprintf(stderr, "PrintListError:Unable to allocate memory for new list\n");
        exit(-1);
    }
    int i=1;
    tmp=list;
    while(tmp!=NULL)
    {
        printf("CASE:%d ,%d:Size %d: (x:%d,y:%d),(xp:%d,yp:%d),cost:%d heur:%d\n",lab[tmp->parent_case.pos.line][tmp->parent_case.pos.column],i++,tmp->size_list,tmp->parent_case.pos.column,tmp->parent_case.pos.line,tmp->parent_case.pos_p.column,tmp->parent_case.pos_p.line,tmp->parent_case.cost,tmp->parent_case.heuristic);
        tmp=tmp->next_case;
        //i++;
    }
    tmp=NULL;
    free(tmp);
}
