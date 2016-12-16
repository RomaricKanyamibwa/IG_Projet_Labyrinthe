#include<stdio.h>
#include<stdlib.h>


/*typedef struct t_data
{
    char** lab;
    char* map;
    int line;//coordones x du jouer (lignes)
    int column;//coordones y du jouer (colonnes)
    int energy;
    int line_treas;
    int column_treas;
}t_data;
*/

void print_laby(char lab[4][4],int sizeX,int sizeY)
{
    int i,j;
    for(i=0;i<sizeY;i++)
        {
            printf("\n");
            for(j=0;j<sizeX;j++)
            {
                printf("%d ",lab[i][j]);
            }
        }
}



void rotation_column_up(char laby[4][4],int value,int sizex,int sizey)
{
    char copy[4][4];//=laby;
    memcpy(copy,laby, sizeof(char)*16);
    char temp=laby[0][value];
    int j;
    for(j=0;j<sizey;j++)
        laby[(sizey+j-1)%sizey][value]=copy[j][value];
    laby[sizey-1][value]=temp;
}

//sizeY numero de lignes
//sizeX numero de colonnes
void rotation_line_left(char laby[4][4],int value,int sizex,int sizey)
{
    char copy[4][4];//=laby;
    char temp=laby[value][0];
    memcpy(copy,laby, sizeof(char)*16);
    int j;
    for(j=0;j<sizex;j++)
        laby[value][(sizex+j-1)%sizex]=copy[value][j];
    laby[value][sizex-1]=temp;
}


void rotation_column_down(char laby[4][4],int value,int sizex,int sizey)
{
    char copy[4][4];//=laby;
    memcpy(copy,laby, sizeof(char)*16);
    char temp=laby[sizey-1][value];
    int j;
    for(j=0;j<sizey;j++)
        laby[(sizey+j+1)%sizey][value]=copy[j][value];
    laby[0][value]=temp;
}

//sizeY numero de lignes
//sizeX numero de colonnes
void rotation_line_right(char laby[4][4],int value,int sizex,int sizey)
{
    char copy[4][4];//=laby;
    char temp=laby[value][sizex-1];
    memcpy(copy,laby, sizeof(char)*16);
    int j;
    for(j=0;j<sizex;j++)
        laby[value][(sizex+j+1)%sizex]=copy[value][j];
    laby[value][0]=temp;
}


int main()
{
    //FILE* f=fopen("laby.txt","r" );
    //fprintf(f, "This is testing for fprintf...\n");
    //fputs("This is testing for fputs...\n", f);
    //char* buff=malloc(sizeof(char)*2);
    //char* tab=malloc(sizeof(char)*17*17);
    char buff[4][4]={{0,1,1,0},{0,1,1,0},{0,1,1,1},{1,1,0,0}};
    //printf("%s",buff[4]);
    print_laby(buff,4,4);
    printf("\n");
    rotation_column_up(buff,0,4,4);
    print_laby(buff,4,4);
    printf("\n");
    rotation_column_up(buff,0,4,4);
    print_laby(buff,4,4);
    printf("\n");
    rotation_column_up(buff,0,4,4);
    print_laby(buff,4,4);
    printf("\n");
    rotation_column_up(buff,0,4,4);
    print_laby(buff,4,4);
    printf("\n");
    rotation_line_left(buff,1,4,4);
    print_laby(buff,4,4);
    printf("\n");
    rotation_line_left(buff,1,4,4);
    print_laby(buff,4,4);
    printf("\n");
    rotation_line_left(buff,1,4,4);
    print_laby(buff,4,4);
    printf("\n");
    return 1;
}
