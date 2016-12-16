#ifndef TEMPLATE_H_INCLUDED
#define TEMPLATE_H_INCLUDED

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

#endif // TEMPLATE_H_INCLUDED
