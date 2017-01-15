#include <stdio.h>
#include <stdlib.h>
#include "array_mod.h"
#include <time.h>



char** alloc_2D_array(int sizex,int sizey)
{
    char**lab=(char**)calloc(sizey,sizeof(char*));
    if(lab == NULL)
    {
        fprintf(stderr, "Unable to allocate memory for new 2D array\n");
        exit(-1);
    }
    int i;
    for (i=0;i<sizey;i++)
    {
        lab[i]=calloc(sizex,sizeof(char));
        if(lab[i] == NULL)
    {
        fprintf(stderr, "Unable to allocate memory for new 2D array\n");
        exit(-1);
    }
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
    tab[10][7]=0;
    tab[10][0]=0;

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
                if(i==10&&j==7)printf(" @");
                else if(tab[i][j]==8)printf(" *");
                    else printf(" %d",tab[i][j]);
            }
        }
        //printf("\nEndPrint\n");
}

void change_tab(char** tab,t_pos* tab_cases,int size)
{
       int i;
    for(i=0;i<size;i++)
        {
           printf("Debug size:%d ,i:%d line:%d column:%d\n",size,i,tab_cases[i].line,tab_cases[i].column);
            if(tab_cases==NULL)printf("NULL");
                if(tab[tab_cases[i].line][tab_cases[i].column]!=1)tab[tab_cases[i].line][tab_cases[i].column]=8;
        }

}


char ** init_lab(char*labdata,int sizex,int sizey)
{
    char**lab=(char**)calloc(sizey,sizeof(char*));
    int i,j;
    for (i=0;i<sizey;i++)
    {
        lab[i]=calloc(sizex,sizeof(char));
    }
    for (i=0;i<sizey;i++)
    {
        for (j=0;j<sizex;j++)
        lab[i][j]=labdata[i*sizex+j];
    }
    return lab;
}

t_data init_data(char*labdata,int sizex,int sizey,int player)
{

    t_data data;
    data.lab=init_lab(labdata,sizex,sizey);
    data.line=sizey/2;
    if(player)data.energy=player+1;
    else data.energy=player;
    if(player)
        data.column=sizex-1;
    else
        data.column=0;
    data.column_treas=sizex/2;
    data.line_treas=sizey/2;
    return data;
}


char ** copy_2Dtab( char**dest,char**sourc,int sizex,int sizey)
{
    int i,j;
    for (i=0;i<sizey;i++)
    {
        for (j=0;j<sizex;j++)
        dest[i][j]=sourc[i][j];
    }
    return dest;
}

void rotation_column_up(char **laby,int value,int sizex,int sizey)
{
    char **copy=alloc_2D_array(sizex,sizey);//copy of laby;
    copy_2Dtab(copy,laby,sizex,sizey);
    char temp=laby[0][value];
    int j;
    for(j=0;j<sizey;j++)
        laby[(sizey+j-1)%sizey][value]=copy[j][value];
    laby[sizey-1][value]=temp;
}

//sizeY numero de lignes
//sizeX numero de colonnes
void rotation_line_left(char **laby,int value,int sizex,int sizey)
{
    char **copy=alloc_2D_array(sizex,sizey);//copy of laby;
    copy_2Dtab(copy,laby,sizex,sizey);
    char temp=laby[value][0];
    int j;
    for(j=0;j<sizex;j++)
        laby[value][(sizex+j-1)%sizex]=copy[value][j];
    laby[value][sizex-1]=temp;
}


void rotation_column_down(char **laby,int value,int sizex,int sizey)
{
    char **copy=alloc_2D_array(sizex,sizey);//copy of laby;
    copy_2Dtab(copy,laby,sizex,sizey);
    char temp=laby[sizey-1][value];
    int j;
    for(j=0;j<sizey;j++)
        laby[(sizey+j+1)%sizey][value]=copy[j][value];
    laby[0][value]=temp;
}

//sizeY numero de lignes
//sizeX numero de colonnes
void rotation_line_right(char **laby,int value,int sizex,int sizey)
{
    char **copy=alloc_2D_array(sizex,sizey);//copy of laby;
    copy_2Dtab(copy,laby,sizex,sizey);
    char temp=laby[value][sizex-1];
    int j;
    for(j=0;j<sizex;j++)
        laby[value][(sizex+j+1)%sizex]=copy[value][j];
    laby[value][0]=temp;
}


