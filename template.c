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
#include "Aetoile.h"
#include <time.h>
#include "template.h"
#include "array_mod.h"


extern int debug;	/* hack to enable debug messages */
t_case Start;// Position du depart
t_pos Treasure;// Coordonnees du Tresor

int move_player(t_data* data,t_move* move,char *labData,int *jouer ,int sizeX,int sizeY,t_typeMove move_to_do)
{

    int alea=move_to_do;//rand()%9;
    //printf("Enter a number from 0 to 8:");
    //scanf("%d",&alea);
    int rotate=0;
    switch(alea)
    {
    case 0://line rotation to the left
        if(data->energy>=5)
            {
                move->value=rand()%sizeY;
                //printf("Enter a number from 0 to %d:",sizeY-1);
                //scanf("%d",&move->value);
                if(move->value==data->line)
                    data->column=(sizeX+data->column-1)%sizeX;
                if(move->value==data->line_treas)
                    data->column_treas=(sizeX+data->column_treas-1)%sizeX;
                data->energy-=5;
                rotation_line_left(data->lab,move->value,sizeX,sizeY);
                rotate++;
                *jouer=1;
            }break;
    case 1://line rotation to the right
            if(data->energy>=5)
            {
                move->value=rand()%sizeY;
                //printf("Enter a number from 0 to %d:",sizeY-1);
                //scanf("%d",&move->value);
                if(move->value==data->line)
                    data->column=(data->column+1)%sizeX;
                if(move->value==data->line_treas)
                    data->column_treas=(data->column_treas+1)%sizeX;
                data->energy-=5;
                rotation_line_right(data->lab,move->value,sizeX,sizeY);
                rotate++;
                *jouer=1;
            }break;
    case 2://column rotation up
            if(data->energy>=5)
            {
                move->value=rand()%sizeX;
                //printf("Enter a number from 0 to %d:",sizeX-1);
                //scanf("%d",&move->value);
                if(move->value==data->column)
                    data->line=(sizeY+data->line-1)%sizeY;
                if(move->value==data->column_treas)
                    data->line_treas=(sizeY+data->line_treas-1)%sizeY;
                data->energy-=5;
                rotation_column_up(data->lab,move->value,sizeX,sizeY);
                rotate++;
                *jouer=1;
            }break;
    case 3://column rotation down
            if(data->energy>=5)
            {
                move->value=rand()%sizeX;
                //printf("Enter a number from 0 to %d:",sizeX-1);
                //scanf("%d",&move->value);
                if(move->value==data->column)
                    data->line=(sizeY+data->line+1)%sizeY;
                if(move->value==data->column_treas)
                    data->line_treas=(sizeY+data->line_treas+1)%sizeY;
                data->energy-=5;
                printf("Columnrotate down\n");
                rotation_column_down(data->lab,move->value,sizeX,sizeY);
                rotate++;
                *jouer=1;
            }break;

    case 4 ://move up
         if (!data->lab[(sizeY+data->line-1)%sizeY][data->column])
            {
                data->line=(sizeY+data->line-1)%sizeY;
                data->energy++;
                *jouer=1;
            }break;

    case 5 ://move down
        if (!data->lab[(data->line+1)%sizeY][data->column])
            {
                data->line=(data->line+1)%sizeY;
                data->energy++;
                *jouer=1;
            }break;
    case 6 ://move left
        if (!data->lab[data->line][(sizeX+data->column-1)%sizeX])
            {
                data->column=(sizeX+data->column-1)%sizeX;
                data->energy++;
                *jouer=1;
            }break;
    case 7 ://move rigth
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


void print_laby2(t_data data,int sizeX,int sizeY)
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

void update_lab(t_move move,t_data* data,int sizeX,int sizeY)
{
    int alea=move.type;
    switch(alea)
    {
    case 0://line rotation to the left

            if(move.value==data->line)
                data->column=(sizeX+data->column-1)%sizeX;
            rotation_line_left(data->lab,move.value,sizeX,sizeY);
            break;
    case 1://line rotation to the right

            if(move.value==data->line)
                data->column=(data->column+1)%sizeX;
            if(move.value==data->line_treas)
                data->column_treas=(data->column_treas+1)%sizeX;
            rotation_line_right(data->lab,move.value,sizeX,sizeY);
            break;
    case 2://column rotation up
            if(move.value==data->column)
                data->line=(sizeY+data->line-1)%sizeY;
            if(move.value==data->column_treas)
                data->line_treas=(sizeY+data->line_treas-1)%sizeY;
            rotation_column_up(data->lab,move.value,sizeX,sizeY);
            break;
    case 3://column rotation down
            if(move.value==data->column)
                data->line=(sizeY+data->line+1)%sizeY;
             if(move.value==data->column_treas)
                data->line_treas=(sizeY+data->line_treas+1)%sizeY;
            rotation_column_down(data->lab,move.value,sizeX,sizeY);
            break;
    default : printf(" ");
    }

    return;

}

t_typeMove* tab_moves(t_data data,t_pos start,t_pos treasure,int line,int column,int* found_path,int* path_index)
{
/** Declaration des Variables**/
    t_pos* path;
    ptr_List closedList;
    t_typeMove* getmoves;
    t_typeMove* sendmoves;
    int size_path=0,i;
/**Initialization des variables**/
    *path_index=0;
    start.line=data.line;
    start.column=data.column;
    treasure.line=data.line_treas;
    treasure.column=data.column_treas;
/**Implementation du Algorithme Astar**/
    closedList=get_closedList(line,column,start,treasure,data.lab,found_path);
    path=create_path(closedList,&size_path);

    getmoves=listmoves(path,size_path,line,column);
    sendmoves=calloc(size_path,sizeof(t_typeMove));
    for(i=0;i<size_path;i++)
    {
        if(getmoves[i]!=-1)
        {
            sendmoves[*path_index]=getmoves[i];
            *path_index=*path_index+1;
        }
    }
    free(closedList);
    return sendmoves;
}

int main()
{
/**Delaration des variables**/
	char labName[]="Victory";					/* name of the labyrinth */
	char* labData;						/* data of the labyrinth */
	t_return_code ret = MOVE_OK;		/* indicates the status of the previous move */
	t_move move;
	t_data data;						/* a move */
	int player;
	int sizeX,sizeY;//sizeY numero de lignes et sizeX numero de colonnes
    int alea,jouer=0,path_index=0;
    int column;
    int line;
    int found_path=0,i;
    t_pos start,treasure;
    t_typeMove* sendmoves;
    debug=1;

	/* connection to the server */
	connectToServer( "pc4023.polytech.upmc.fr", 1234, "Paola");
	//connectToServer( "localhost", 1234, "prog_template");


	/* wait for a game, and retrieve informations about it */
    waitForLabyrinth( "ASTAR timeout=100 rotation=True", labName, &sizeX, &sizeY);
	labData = (char*) malloc( sizeX * sizeY );
	player = getLabyrinth( labData);
/**Initialisation de la structure Data**/
	data=init_data(labData,sizeX,sizeY,player);
	data.map=labData;
/**Liste de mouvement à effectuer pour arriver au tresor**/
    start.line=data.line;
    start.column=data.column;
    treasure.line=data.line_treas;
    treasure.column=data.column_treas;
    line=sizeY;
    column=sizeX;
	sendmoves=tab_moves(data,start,treasure,line,column,&found_path,&path_index);
    i=0;
    do{
        /* display the labyrinth */
        printLabyrinth();

        if (player==1)	/* The opponent plays */
          {
                ret = getMove( &move);
                update_lab(move,&data,sizeX,sizeY);
                if(move.type<4)
                {
                    i=0;
                    sendmoves=tab_moves(data,start,treasure,line,column,&found_path,&path_index);
                }
            }
        else
          {
            do{
                if(path_index<=0)alea=move_player(&data,&move,labData,&jouer,sizeX,sizeY,rand()%9);
                else if(path_index>=i)alea=move_player(&data,&move,labData,&jouer,sizeX,sizeY,sendmoves[i]);
                    else alea=move_player(&data,&move,labData,&jouer,sizeX,sizeY,rand()%9);
                i=i+1;
                //else alea=move_player(&data,&move,labData,&jouer,sizeX,sizeY,rand()%9);

            }while(!jouer);
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
	free(sendmoves);
	/* end the connection, because we are polite */
	closeConnection();

	return EXIT_SUCCESS;
}

