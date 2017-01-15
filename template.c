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
                printf("Linerotate left\n");
                //print_laby(*data,sizeX,sizeY);
                printf("\n");
                rotation_line_left(data->lab,move->value,sizeX,sizeY);
                //print_laby(*data,sizeX,sizeY);
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
                printf("Linerotate right \n");
                //print_laby(*data,sizeX,sizeY);
                printf("\n");
                rotation_line_right(data->lab,move->value,sizeX,sizeY);
                //print_laby(*data,sizeX,sizeY);
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
                printf("Columnrotate up\n");
                //print_laby(*data,sizeX,sizeY);
                printf("\n");
                rotation_column_up(data->lab,move->value,sizeX,sizeY);
                //print_laby(*data,sizeX,sizeY);
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
                //print_laby(*data,sizeX,sizeY);
                printf("\n");
                rotation_column_down(data->lab,move->value,sizeX,sizeY);
                //print_laby(*data,sizeX,sizeY);
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
    //printf("Enter a number from 0 to 8:");
    //scanf("%d",&alea);
    switch(alea)
    {
    case 0://line rotation to the left

            if(move.value==data->line)
                data->column=(sizeX+data->column-1)%sizeX;
            printf("Linerotate left\n");
            printf("\n");
            rotation_line_left(data->lab,move.value,sizeX,sizeY);
            break;
    case 1://line rotation to the right

            if(move.value==data->line)
                data->column=(data->column+1)%sizeX;
            if(move.value==data->line_treas)
                data->column_treas=(data->column_treas+1)%sizeX;
            printf("Linerotate right \n");
            printf("\n");
            rotation_line_right(data->lab,move.value,sizeX,sizeY);
            break;
    case 2://column rotation up
            if(move.value==data->column)
                data->line=(sizeY+data->line-1)%sizeY;
            if(move.value==data->column_treas)
                data->line_treas=(sizeY+data->line_treas-1)%sizeY;
            printf("Columnrotate up\n");
            printf("\n");
            rotation_column_up(data->lab,move.value,sizeX,sizeY);
            break;
    case 3://column rotation down
            if(move.value==data->column)
                data->line=(sizeY+data->line+1)%sizeY;
             if(move.value==data->column_treas)
                data->line_treas=(sizeY+data->line_treas+1)%sizeY;
            printf("Columnrotate down\n");
            printf("\n");
            rotation_column_down(data->lab,move.value,sizeX,sizeY);
            break;
    default : printf(" ");
    }

    return;

}

t_typeMove* tab_moves(t_data data,t_pos start,t_pos treasure,int line,int column,int* found_path,int* path_index)
{

    t_pos* path;
    ptr_List closedList;
    t_typeMove* getmoves;
    t_typeMove* sendmoves;
    int size_path=0,i;
    int sizeX=column,sizeY=line;

    *path_index=0;
    start.line=data.line;
    start.column=data.column;
    treasure.line=data.line_treas;
    treasure.column=data.column_treas;
    //print_laby(tab,column,line);
    //printf("\n0");
    printf("\n");
    print_laby2(data,sizeX,sizeY);
    printf("\nMyLine=%d et MyColumn=%d\n",data.line,data.column);//data.line est le numero de la ligne et data.column est le numero de la colonne
    printf("\nTreasure MyLine=%d et MyColumn=%d\n",data.line_treas,data.column_treas);
    closedList=get_closedList(line,column,start,treasure,data.lab,found_path);
    //print_list(closedList,data.lab);
    path=create_path(closedList,&size_path);
    printf("SizeX:%d SizeY:%d\n",sizeX,sizeY);
    printf("Test\n\n");
    getmoves=listmoves(path,size_path,line,column);
    sendmoves=calloc(size_path,sizeof(t_typeMove));
    printLabyrinth();
    //printf("\n");
    for(i=0;i<size_path;i++)
    {
        if(getmoves[i]!=-1)
        {
            sendmoves[*path_index]=getmoves[i];
            //printf("Move %d:%d \n,",path_index+1,getmoves[i]);
            *path_index++;
        }
    }
    free(closedList);

    return sendmoves;
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
    int alea,jouer=0,path_index=0;
    int column;
    int line;
    int found_path=0,i;
    int size_path=0;
    t_pos start,treasure;
    t_pos* path;
    ptr_List closedList;
    t_typeMove* getmoves;
    t_typeMove* sendmoves;
    debug=1;
	//int rotate=0;

	/* connection to the server */
	connectToServer( "pc4023.polytech.upmc.fr", 1234, "Paola");
	//connectToServer( "localhost", 1234, "prog_template");


	/* wait for a game, and retrieve informations about it */
    waitForLabyrinth( "PLAY_RANDOM timeout=100 rotation=False", labName, &sizeX, &sizeY);
	labData = (char*) malloc( sizeX * sizeY );
	player = getLabyrinth( labData);
	data=init_data(labData,sizeX,sizeY,player);
	data.map=labData;
    start.line=data.line;
    start.column=data.column;
    treasure.line=data.line_treas;
    treasure.column=data.column_treas;
    line=sizeY;
    column=sizeX;
    //print_laby(tab,column,line);
    //printf("\n0");
    printf("\n");
    print_laby2(data,sizeX,sizeY);
    printf("\nMyLine=%d et MyColumn=%d\n",data.line,data.column);//data.line est le numero de la ligne et data.column est le numero de la colonne
    printf("\nTreasure MyLine=%d et MyColumn=%d\n",data.line_treas,data.column_treas);
    closedList=get_closedList(line,column,start,treasure,data.lab,&found_path);
    //print_list(closedList,data.lab);
    path=create_path(closedList,&size_path);
    printf("SizeX:%d SizeY:%d\n",sizeX,sizeY);
    printf("Test\n\n");
    getmoves=listmoves(path,size_path,line,column);
    sendmoves=calloc(size_path,sizeof(t_typeMove));
    printLabyrinth();
    //printf("\n");
    for(i=0;i<size_path;i++)
    {
        if(getmoves[i]!=-1)
        {
            sendmoves[path_index]=getmoves[i];
            //printf("Move %d:%d \n,",path_index+1,getmoves[i]);
            path_index++;
        }
    }
    //return 1;
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
                return 1;
            }
            //playMove( &lab, move);
            }
        else
          {
            do{

            alea=move_player(&data,&move,labData,&jouer,sizeX,sizeY,sendmoves[i++]);

            }while(!jouer);
            printf("\n");
            print_laby2(data,sizeX,sizeY);
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

