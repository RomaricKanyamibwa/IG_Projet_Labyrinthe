#include <stdio.h>
#include <stdlib.h>
#include "Aetoile.h"


t_case Start;
t_pos Treasure;

int main()
{
    Treasure.x=3;
    Treasure.y=4;
    t_pos rnd={3,5};
    int d=estim_distance(rnd);
    printf("Dist :%d\n",d);

    return 1;
}

t_case nouvelle_case(t_case c,t_pos coord)
{
    t_case v;
    v.coord=coord;
    v.cost=c.cost+1;
    v.heuristic=v.cost+estim_distance(coord);
    v.coord_p=c.coord;
    return v;
}

int estim_distance(t_pos x_y)
{
    int d=0,dx,dy;
    dx=x_y.x-Treasure.x;
    if(dx<0) dx*=-1;
    dy=x_y.y-Treasure.y;
    if(dy<0) dy*=-1;
    d=dx+dy;
    return d;
}
