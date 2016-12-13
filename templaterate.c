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

void init_lab(char**lab,int sizex,int sizey)//initialisation data.lab
{
  lab=(char**)malloc(sizeof(char*)*sizex);
  int i;
  for (i=0;i<sizex;i++)
    {
      lab[i]=(char*)calloc(sizey,sizeof(char));
    }
}
char ** copie_lab(char **lab,char*labdata,int sizex,int sizey)//copie labData dans data.lab
{int i,j;
    for (i=0;i<sizex;i++)
    {
        for (j=0;j<sizey;j++)
        lab[i][j]=labdata[i*sizey+j];
    }
    return lab;
}
t_data init_data(char*labdata,int sizex,int sizey,int player)//initialisation structure data
{

    t_data data;
    init_lab(data.lab,sizey,sizex);//initialisation data.lab
    copie_lab(data.lab,labdata,sizey,sizex);//data.lab=labData
    data.energy=player;
    data.posx=sizey/2;//position player
    if(player)
        data.posy=sizex-1;
    else
        data.posy=0;
    data.posy_treas=sizex/2;//position tresor
    data.posx_treas=sizey/2;
    return data;
}

void bouger_alea(t_data *data,char* labData,t_move *move,int sizeX,int sizeY)
{
    int alea=rand()%8;//type de mouvement
    int jouer=0;//possibilite mouvement
        do{
        switch(alea)
        {
            case 0://case de 0 a 3 pour rotation
                if(data->energy>=5)
                {
                    move->value=rand()%sizeY;
                    if(move->value==data->posx)
                    data->posx=(sizeY+data->posx-1)%sizeY;
                    data->energy-=5;
                    jouer=1;
                }break;
            case 1:
                if(data->energy>=5)
                {
                    move->value=rand()%sizeY;
                    if(move->value==data->posx)
                    data->posx=(data->posx+1)%sizeY;
                    data->energy-=5;
                    jouer=1;
                }break;
            case 2:
                if(data->energy>=5)
                {
                    move->value=rand()%sizeX;
                    if(move->value==data->posy)
                    data->posy=(sizeX+data->posy-1)%sizeX;
                    data->energy-=5;
                    jouer=1;
                }break;
            case 3:
                if(data->energy>=5)
                {
                    move->value=rand()%sizeX;
                    if(move->value==data->posy)
                    data->posy=(sizeX+data->posy-1)%sizeX;
                    data->energy-=5;
                    jouer=1;
                }break;

                case 4 : //case de 4 a 7 pour mouvement classique
                //if ((data->posx-1)<0) casexy=sizeY-1;
                //else casxy=data->posx-1;
                if (!data->lab[(sizeY+data->posx-1)%sizeY][data->posy])
                {
                    data->posx=(sizeY+data->posx-1)%sizeY;
                    data->energy++;
                    jouer=1;
                }break;

            case 5 :
                if (!data->lab[(data->posx+1)%sizeY][data->posy])
                {
                    data->posx=(data->posx+1)%sizeY;
                    data->energy++;
                    jouer=1;
                }break;
            case 6 :
                if (!data->lab[data->posx][(sizeX+data->posy-1)%sizeX])
                {
                    data->posy=(sizeX+data->posy-1)%sizeX;
                    data->energy++;
                    jouer=1;
                }break;
            case 7 :
                if (!data->lab[data->posx][(data->posy+1)%sizeX])
                {
                    data->posy=(data->posy+1)%sizeX;
                    data->energy++;
                    jouer=1;
                }break;
            default : printf(" ");
        }
        alea=rand()%8;//ancien mouvement non possible
    }while(!jouer);
    if(alea>-1 && alea<4)//mise a jour data->lab si rotation
    {
        copie_lab(data->lab,labData,sizeY,sizeX);
    }
    jouer=0;
    printf(" SizeY:%d Move=%d\n",sizeY,alea);//mouvement effectué
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
	int i,j;

	/* connection to the server */
	connectToServer( "pc4023.polytech.upmc.fr", 1234, "Paola");
	//connectToServer( "localhost", 1234, "prog_template");


	/* wait for a game, and retrieve informations about it */
	waitForLabyrinth( "DO_NOTHING timeout=1000 tot=25", labName, &sizeX, &sizeY);
	labData = (char*) malloc( sizeX * sizeY );
	player = getLabyrinth( labData);
	//data=init_data(labData,sizeX,sizeY,player);

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
	    bouger_alea(&data,labData,&move,sizeX,sizeY);//mouvement aleatoire
	    printf("\nX=%d et Y=%d\n",data.posx,data.posy);//position du player

            ret = sendMove(move);
            //check data.lab bien mis a jour
            for(i=0;i<sizeY;i++)
                {printf("\n");
                for(j=0;j<sizeX;j++)
                {
                    printf("%d ",data.lab[i][j]);
                }
                }

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


