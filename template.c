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



extern int debug;	/* hack to enable debug messages */

typedef struct t_data
{
    char** lab;
    int posx;
    int posy;
    int energy;
    int posx_treas;
    int posy_treas;
}t_data;

char ** init_lab(char*labdata,int sizex,int sizey)
{
    char**lab=(char**)malloc(sizeof(char*)*sizex);
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
t_data init_data(char*labdata,int sizex,int sizey,int player)
{

    t_data data;
    data.lab=init_lab(labdata,sizey,sizex);
    data.posx=sizey/2;
    data.energy=player;
    if(player)
        data.posy=sizex-1;
    else
        data.posy=0;
    data.posy_treas=sizex/2;
    data.posx_treas=sizey/2;
    return data;
}

int main()
{
	char labName[50];					/* name of the labyrinth */
	char* labData;						/* data of the labyrinth */
	t_return_code ret = MOVE_OK;		/* indicates the status of the previous move */
	t_move move;
	t_data data;						/* a move */
	int player;
	int sizeX,sizeY;
	int alea,jouer=0,energy;

	/* connection to the server */
	connectToServer( "pc4023.polytech.upmc.fr", 1234, "Paola");
	//connectToServer( "localhost", 1234, "prog_template");


	/* wait for a game, and retrieve informations about it */
	waitForLabyrinth( "DO_NOTHING timeout=1000 tot=25", labName, &sizeX, &sizeY);
	labData = (char*) malloc( sizeX * sizeY );
	player = getLabyrinth( labData);
	energy=player;
	data=init_data(labData,sizeX,sizeY,player);

    printf("\n");
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
            alea=rand()%9;
            if (alea<4 && energy>=5)
                {
                    move.value=rand()%4;
                    jouer=1;
                }

            switch(alea)
            {
            case 0:
                if(energy>=5)
                    {
                    move.value=rand()%4;
                        if(move.value==data.posx)
                            data.posx=(data.posx-1)%sizeY;
                    jouer=1;
                    }break;
            case 1:
                            if(energy>=5)
                    {
                    move.value=rand()%4;
                        if(move.value==data.posx)
                            data.posx=(data.posx+1)%sizeY;
                    jouer=1;
                    }break;
            case 2:
                            if(energy>=5)
                    {
                    move.value=rand()%4;
                        if(move.value==data.posy)
                            data.posy=(data.posy-1)%sizeX;
                    jouer=1;
                    }break;
            case 3:
                            if(energy>=5)
                    {
                    move.value=rand()%4;
                        if(move.value==data.posy)
                            data.posy=(data.posy-1)%sizeX;
                    jouer=1;
                    }break;

            case 4 :
                 if (!data.lab[(data.posx-1)%sizeY][data.posy])
                    {data.posx=(data.posx-1)%sizeY;
                    jouer=1;
                    }break;

            case 5 :
            if (!data.lab[(data.posx+1)%sizeY][data.posy])
                    {data.posx=(data.posx+1)%sizeY;
                    jouer=1;
                    }break;
            case 6 :if (!data.lab[data.posx][(data.posy-1)%sizeX])
                    {data.posy=(data.posy-1)%sizeX;
                    jouer=1;
                    }break;
            case 7 :if (!data.lab[data.posx][(data.posy+1)%sizeX])
                    {
                        data.posy=(data.posy+1)%sizeX;
                        jouer=1;
                    }break;
            default : printf(" ");
            }
            }while(!jouer);
            printf("\nMove=%d\n",alea);
            move.type=alea;
            ret = sendMove(move);
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

