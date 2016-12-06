   printf("sizex= %d size y=%d\n",sizeX,sizeY);
    printf("Energy:%d\n",data.energy);
    printf("Posx:%d\n",data.posx);
    printf("Posy:%d\n",data.posy);
    printf("Posx_treasure:%d\n",data.posx_treas);
    printf("Posy_treasure:%d\n",data.posy_treas);
    int i,j;
    for(i=0;i<sizeY;i++)
        {printf("\n");
        for(j=0;j<sizeX;j++)
        {
            printf("%d ",data.lab[i][j]);
        }
        }
