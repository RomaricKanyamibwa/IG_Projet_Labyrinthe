#ifndef ARRAY_MOD_H_INCLUDED
#define ARRAY_MOD_H_INCLUDED

#include "template.h"
#include "labyrinthAPI.h"


char ** init_lab(char*labdata,int sizex,int sizey);
char** alloc_2D_array(int sizex,int sizey);
t_data init_data(char*labdata,int sizex,int sizey,int player);
char ** copy_2Dtab( char**dest,char**sourc,int sizex,int sizey);
void rotation_column_up(char **laby,int value,int sizex,int sizey);
void rotation_line_left(char **laby,int value,int sizex,int sizey);
void rotation_column_down(char **laby,int value,int sizex,int sizey);
void rotation_line_right(char **laby,int value,int sizex,int sizey);
void update_lab(t_move move,t_data* data,int sizeX,int sizeY);
char** create_table(int line,int column);
void print_laby(char** tab,int sizeX,int sizeY);
void change_tab(char** tab,t_pos* tab_cases,int size);



#endif // ARRAY_MOD_H_INCLUDED
