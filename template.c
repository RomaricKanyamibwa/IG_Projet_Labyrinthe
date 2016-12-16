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

//sizeY numero de lignes
//sizeX numero de colonnes

extern int debug;	/* hack to enable debug messages */



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



char ** init_lab(char*labdata,int sizex,int sizey)
{
    char**lab=(char**)malloc(sizeof(char*)*sizex);
    int i,j;
    debug=1;
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

//sizeY numero de lignes
//sizeX numero de colonnes
void rotation_column(char** laby,int value,int sizex,int sizey)
{
    char** copy=laby;
    char temp=laby[0][value];
    int j;
    for(j=0;j<sizex;j++)
        laby[(sizey+j+1)%sizey][value]=copy[j][value];
    laby[sizey-1][value]=temp;
}

//sizeY numero de lignes
//sizeX numero de colonnes
void rotation_line_left(char** laby,int value,int sizex,int sizey)
{
    char** copy=laby;
    char temp=laby[value][0];
    int j;
    for(j=0;j<sizex;j++)
        laby[value][(sizex+j+1)%sizex]=copy[value][j];
    laby[value][sizex-1]=temp;
}

int move_player(t_data* data,t_move* move,char *labData,int *jouer ,int sizeX,int sizeY)
{

    int alea=rand()%8;
    int rotate=0;
    switch(alea)
    {
    case 0:
        if(data->energy>=5)
            {
                move->value=rand()%sizeY;
                if(move->value==data->line)
                    data->line=(sizeY+data->line-1)%sizeY;
                data->energy-=5;
                //rotation_line(data->lab,+1,move->value,sizeX,sizeY);
                rotate++;
                *jouer=1;
            }break;
    case 1:
            if(data->energy>=5)
            {
                move->value=rand()%sizeY;
                if(move->value==data->line)
                    data->line=(data->line+1)%sizeY;
                data->energy-=5;
                rotate++;
                *jouer=1;
            }break;
    case 2:
            if(data->energy>=5)
            {
                move->value=rand()%sizeX;
                if(move->value==data->column)
                    data->column=(sizeX+data->column-1)%sizeX;
                data->energy-=5;
                rotate++;
                *jouer=1;
            }break;
    case 3:
            if(data->energy>=5)
            {
                move->value=rand()%sizeX;
                if(move->value==data->column)
                    data->column=(sizeX+data->column-1)%sizeX;
                data->energy-=5;
                rotate++;
                *jouer=1;
            }break;

    case 4 :
        //if ((data->line-1)<0) casexy=sizeY-1;
        //else casxy=data->line-1;
         if (!data->lab[(sizeY+data->line-1)%sizeY][data->column])
            {
                data->line=(sizeY+data->line-1)%sizeY;
                data->energy++;
                *jouer=1;
            }break;

    case 5 :
        if (!data->lab[(data->line+1)%sizeY][data->column])
            {
                data->line=(data->line+1)%sizeY;
                data->energy++;
                *jouer=1;
            }break;
    case 6 :
        if (!data->lab[data->line][(sizeX+data->column-1)%sizeX])
            {
                data->column=(sizeX+data->column-1)%sizeX;
                data->energy++;
                *jouer=1;
            }break;
    case 7 :
        if (!data->lab[data->line][(data->column+1)%sizeX])
            {
                data->column=(data->column+1)%sizeX;
                data->energy++;
                *jouer=1;
            }break;
    default : printf(" ");
    }

    if(rotate)
        {
            rotate--;
            data->lab=update_lab(data->lab,labData,sizeX,sizeY);
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
	char labName[50];					/* name of the labyrinth */
	char* labData;						/* data of the labyrinth */
	t_return_code ret = MOVE_OK;		/* indicates the status of the previous move */
	t_move move;
	t_data data;						/* a move */
	int player;
	int sizeX,sizeY;//sizeY numero de lignes et sizeX numero de colonnes
    int alea,jouer=0;
	//int rotate=0;

	/* connection to the server */
	connectToServer( "pc4023.polytech.upmc.fr", 1234, "Paola");
	//connectToServer( "localhost", 1234, "prog_template");


	/* wait for a game, and retrieve informations about it */
	waitForLabyrinth( "DO_NOTHING timeout=1000 tot=25", labName, &sizeX, &sizeY);
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
            data.map=labData;
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

