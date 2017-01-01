//
// TEMPLATE
//
//
// Permet de jouer un seul tour (en ne faisant rien s'il commence ou en
// réceptionnant le coup de l'adversaire s'il ne commence pas)
// et termine le jeu.
// Ce programme vous sert de base pour construire votre propre programme



#include <stdio.h>
#include <stdlib.h>
#include "labyrinthAPI.h"
#include <unistd.h>
//#include "template.h"

//sizeY numero de lignes
//sizeX numero de colonnes


typedef struct t_data
{
    char** lab;
    char* map;
    int line;//coordones x du jouer (lignes)
    int column;//coordones y du jouer (colonnes)
    int energy;
    int line_treas;
    int column_treas;
}t_data;


extern int debug;	/* hack to enable debug messages */
void print_laby(t_data data,int sizeX,int sizeY);


char ** init_lab(char*labdata,int sizex,int sizey)
{
    char**lab=(char**)calloc(sizex,sizeof(char*));
    int i,j;
    for (i=0;i<sizex;i++)
    {
        lab[i]=calloc(sizey,sizeof(char));
    }
    for (i=0;i<sizex;i++)
    {
        for (j=0;j<sizey;j++)
        lab[i][j]=labdata[i*sizey+j];
    }
    return lab;
}

char** alloc_2D_array(int sizex,int sizey)
{
    char**lab=(char**)calloc(sizex,sizeof(char*));
    int i;
    for (i=0;i<sizex;i++)
    {
        lab[i]=calloc(sizey,sizeof(char));
    }
    return lab;
}




t_data init_data(char*labdata,int sizex,int sizey,int player)
{

    t_data data;
    data.lab=init_lab(labdata,sizey,sizex);
    data.line=sizey/2;
    data.energy=player;
    if(player)
        data.column=sizex-1;
    else
        data.column=0;
    data.column_treas=sizex/2;
    data.line_treas=sizey/2;
    return data;
}





char ** update_lab( char**lab,char*labdata,int sizex,int sizey)
{
    int i,j;
    for (i=0;i<sizey;i++)
    {
        for (j=0;j<sizex;j++)
        lab[i][j]=labdata[i*sizex+j];
    }
    return lab;
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


int move_player(t_data* data,t_move* move,char *labData,int *jouer ,int sizeX,int sizeY)
{

    int alea=rand()%8;
    int rotate=0;
    switch(alea)
    {
    case 0://line rotation to the left
        if(data->energy>=5)
            {
                move->value=rand()%sizeY;
                if(move->value==data->line)
                    data->line=(sizeY+data->line-1)%sizeY;
                data->energy-=5;
                printf("Linerotate left\n");
                print_laby(*data,sizeX,sizeY);
                printf("\n");
                rotation_line_left(data->lab,move->value,sizeX,sizeY);
                print_laby(*data,sizeX,sizeY);
                rotate++;
                *jouer=1;
            }break;
    case 1://line rotation to the right
            if(data->energy>=5)
            {
                move->value=rand()%sizeY;
                if(move->value==data->line)
                    data->line=(data->line+1)%sizeY;
                data->energy-=5;
                printf("Linerotate right \n");
                print_laby(*data,sizeX,sizeY);
                printf("\n");
                rotation_line_right(data->lab,move->value,sizeX,sizeY);
                print_laby(*data,sizeX,sizeY);
                rotate++;
                *jouer=1;
            }break;
    case 2://column rotation up
            if(data->energy>=5)
            {
                move->value=rand()%sizeX;
                if(move->value==data->column)
                    data->column=(sizeX+data->column-1)%sizeX;
                data->energy-=5;
                printf("Columnrotate up\n");
                print_laby(*data,sizeX,sizeY);
                printf("\n");
                rotation_column_up(data->lab,move->value,sizeX,sizeY);
                print_laby(*data,sizeX,sizeY);
                rotate++;
                *jouer=1;
            }break;
    case 3://column rotation down
            if(data->energy>=5)
            {
                move->value=rand()%sizeX;
                if(move->value==data->column)
                    data->column=(sizeX+data->column+1)%sizeX;
                data->energy-=5;
                printf("Columnrotate down\n");
                print_laby(*data,sizeX,sizeY);
                printf("\n");
                rotation_column_down(data->lab,move->value,sizeX,sizeY);
                print_laby(*data,sizeX,sizeY);
                rotate++;
                *jouer=1;
            }break;

    case 4 ://Up movemnt
        //if ((data->line-1)<0) casexy=sizeY-1;
        //else casxy=data->line-1;
         if (!data->lab[(sizeY+data->line-1)%sizeY][data->column])
            {
                data->line=(sizeY+data->line-1)%sizeY;
                data->energy++;
                *jouer=1;
            }break;

    case 5 ://down movement
        if (!data->lab[(data->line+1)%sizeY][data->column])
            {
                data->line=(data->line+1)%sizeY;
                data->energy++;
                *jouer=1;
            }break;
    case 6 ://movement to the left
        if (!data->lab[data->line][(sizeX+data->column-1)%sizeX])
            {
                data->column=(sizeX+data->column-1)%sizeX;
                data->energy++;
                *jouer=1;
            }break;
    case 7 ://movement to the right
        if (!data->lab[data->line][(data->column+1)%sizeX])
            {
                data->column=(data->column+1)%sizeX;
                data->energy++;
                *jouer=1;
            }break;
    default : printf(" ");
    }

    return alea;
}


void print_laby(t_data data,int sizeX,int sizeY)
{
    int i,j;
    for(i=0;i<sizeY;i++)
        {
            printf("\n");
            for(j=0;j<sizeX;j++)
            {
                printf("%d ",data.lab[i][j]);
            }
        }
}


int main()
{
	char labName[]="Victory";					/* name of the labyrinth */
	char* labData;						/* data of the labyrinth */
	t_return_code ret = MOVE_OK;		/* indicates the status of the previous move */
	t_move move;
	t_data data;						/* a move */
	int player;
	int sizeX,sizeY;//sizeY numero de lignes et sizeX numero de colonnes
    int alea,jouer=0;
    debug=2;
	//int rotate=0;

	/* connection to the server */
	connectToServer( "pc4001.polytech.upmc.fr", 1234, "Paola");
	//connectToServer( "localhost", 1234, "prog_template");


	/* wait for a game, and retrieve informations about it */
	waitForLabyrinth( "PLAY_RANDOM rotation=False timeout=1000 tot=25", labName, &sizeX, &sizeY);
	labData = (char*) malloc( sizeX * sizeY );
	player = getLabyrinth( labData);
	data=init_data(labData,sizeX,sizeY,player);
	data.map=labData;

    //printf("\n");
     do{
        /* display the labyrinth */
        printLabyrinth();

        if (player==1)	/* The opponent plays */
          {
            ret = getMove( &move);
            //playMove( &lab, move);
            }
        else
          {
            do{

            alea=move_player(&data,&move,labData,&jouer,sizeX,sizeY);

            }while(!jouer);
            printf("\n");
            print_laby(data,sizeX,sizeY);
            printf("\nMyLine=%d et MyColYumn=%d\n",data.line,data.column);//data.line est le numero de la ligne et data.column est le numero de la colonne
            printf("SizeX:%d SizeY:%d Move=%d Value=%d\n",sizeX,sizeY,alea,move.value);
            move.type=alea;
            ret = sendMove(move);
            jouer=0;
          }
          if ((player ==1 && ret == MOVE_WIN) || (player==0 && ret == MOVE_LOSE))
          printf("I lose the game\n");
          player=!player;
        }while(ret== MOVE_OK);

	/* we do not forget to free the allocated array */
	free(labData);

	/* end the connection, because we are polite */
	closeConnection();

	return EXIT_SUCCESS;
}

