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


int main()
{
	char labName[50];					/* name of the labyrinth */
	char* labData;						/* data of the labyrinth */
	t_return_code ret = MOVE_OK;		/* indicates the status of the previous move */
	t_move move;						/* a move */
	int player;
	int sizeX,sizeY;

	/* connection to the server */
	connectToServer( "pc4022.polytech.upmc.fr", 1234, "Paola");
	//connectToServer( "localhost", 1234, "prog_template");


	/* wait for a game, and retrieve informations about it */
	waitForLabyrinth( "DO_NOTHING timeout=1000 tot=25", labName, &sizeX, &sizeY);
	labData = (char*) malloc( sizeX * sizeY );
	player = getLabyrinth( labData);



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
            //recupere le mouvement du player
            printf("ROTATE_LINE_LEFT = 0    ROTATE_LINE_RIGHT = 1,\nROTATE_COLUMN_UP = 2    ROTATE_COLUMN_DOWN = 3,\nMOVE_UP = 4    MOVE_DOWN = 5,\nMOVE_LEFT = 6   MOVE_RIGHT = 7  DO_NOTHING = 8\n");
            printf("Rotation possible uniquement si energie >=5\n\n");
            printf("Indiquez le type de mouvement:");
            scanf("%u",&move.type);

            if(move.type<4)//si rotation
                {
                    printf("indiquez la ligne ou colonne à modifier : ");
                    scanf("%d",&move.value);
                }
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


