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

void print_laby(char **lab,int sizeX,int sizeY)
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

char** alloc_2D_array(int sizex,int sizey)
{
    char**lab=(char**)malloc(sizex*sizeof(char*));
    int i;
    for (i=0;i<sizex;i++)
    {
        lab[i]=malloc(sizey*sizeof(char));
    }
    return lab;
}

char ** copy_2Dtab( char** dest,char** sourc,int sizex,int sizey)
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
    char **copy=laby;//copy of laby;
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
    char **copy=laby;//copy of laby;
    char temp=laby[value][0];
    int j;
    for(j=0;j<sizex;j++)
        laby[value][(sizex+j-1)%sizex]=copy[value][j];
    laby[value][sizex-1]=temp;
}


void rotation_column_down(char **laby,int value,int sizex,int sizey)
{
    char **copy=laby ;//copy oflaby;
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
    char **copy=laby;//copy of laby;
    char temp=laby[value][sizex-1];
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
    char** buff0=alloc_2D_array(2,2); //[4][4]//={{0,1,1,0},{0,1,1,0},{0,1,1,1},{1,1,0,0}};
    buff0[0][0]=1;
    buff0[0][1]=0;
    buff0[1][0]=0;
    buff0[1][1]=1;
    char **buff=alloc_2D_array(2,2);
    buff=copy_2Dtab(buff,buff0,2,2);
    /*int i,j;
    for (i=0;i<4;i++)
    {
        memcpy(buff[i],buff0[i],4);
    }*/
    //printf("%s",buff[4]);
    print_laby(buff,2,2);
    printf("\n");
    rotation_column_down(buff,0,2,2);
    print_laby(buff,2,2);
    printf("\n");
    rotation_column_down(buff,0,2,2);
    print_laby(buff,2,2);
    printf("\n");
    rotation_column_down(buff,0,2,2);
    print_laby(buff,2,2);
    printf("\n");
    rotation_column_down(buff,0,2,2);
    print_laby(buff,2,2);
    printf("\n");
    rotation_line_right(buff,1,2,2);
    print_laby(buff,2,2);
    printf("\n");
    rotation_line_right(buff,1,2,2);
    print_laby(buff,2,2);
    printf("\n");
    rotation_line_right(buff,1,2,2);
    print_laby(buff,2,2);
    printf("\n");
    rotation_line_right(buff,1,2,2);
    print_laby(buff,2,2);
    printf("\n");
    return 1;
}

/*buff0[0]={0,1,1,0};
    buff0[1]={0,1,1,0};
    buff0[2]={0,1,1,1};
    buff0[3]={1,1,0,0};
    buff0[0][0]=1;
    buff0[0][1]=1;
    buff0[1][0]=1;
    buff0[1][1]=1;*/
