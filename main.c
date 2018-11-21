#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
enum direction{
	up = 0,
	right = 1,
	down = 2,
	left = 3
};
enum tile_content{
	empty = 0,
	snake = 1,
	food = 2,
	fatsnake=3
};
struct tile{
	enum direction dr;
	enum tile_content tl;
};
struct map{
	int mapsizex;
	int mapsizey;
	struct tile ** tiles;
	int headx;
	int heady;
	int tailx;
	int taily;
};
struct map initmap(int x, int y, int l){
	struct tile zerotile;
	zerotile.dr=0 ;
	zerotile.tl=0 ;
	struct map output;
	output.tiles=/*(struct tile**)*/ calloc(x,sizeof(struct tile*));
	for (int i=0; i<x; i++){
        output.tiles[i]=calloc(y,sizeof(struct tile));
		for (int j=0; j<y; j++){
			output.tiles[i][j]=zerotile ;
		};
	};
	output.mapsizex=x;
	output.mapsizey=y;
	output.headx=x/2;
	output.heady=y/2;
	for(int i=0; i<l; i++){
        output.tiles[output.headx+i][output.heady].dr=left;
        output.tiles[output.headx+i][output.heady].tl=1;
	}
	output.tailx=output.headx+l-1;
	output.taily=output.heady;
	return output;
}
void increasex(int* x, struct map*mapp){
    if((*x)<((*mapp).mapsizex-1)){
        (*x)++;
    }else{
        (*x)=0;
    };
}
void increasey(int* y, struct map*mapp){
    if((*y)<((*mapp).mapsizey-1)){
        (*y)++;
    }else{
        (*y)=0;
    };
}
void decreasex(int* x , struct map*mapp){
    if(*x>0){
       (*x)--;
    }else{
       (*x)=(*mapp).mapsizex-1;
    };
}
void decreasey(int* y, struct map*mapp){
    if(*y>0){
        (*y)--;
    }else{
        (*y)=(*mapp).mapsizex-1;
    };
}
bool tickle (struct map*mapp){
    int xx=mapp->tailx;
    int yy=mapp->taily;
    if (mapp->tiles[xx][yy].tl==3){
        mapp->tiles[xx][yy].tl=1;
    } else {
        mapp->tiles[xx][yy].tl=0;
        switch (mapp->tiles[xx][yy].dr){
            case 0: decreasey(&(mapp->taily),mapp); break;
            case 1: increasex(&(mapp->tailx),mapp); break;
            case 2: increasey(&(mapp->taily),mapp); break;
            case 3: decreasex(&(mapp->tailx),mapp); break;
        };
    }
    xx=mapp->headx;
    yy=mapp->heady;
    switch (mapp->tiles[xx][yy].dr){
            case 0: decreasey(&yy,mapp); break;
            case 1: increasex(&xx,mapp); break;
            case 2: increasey(&yy,mapp); break;
            case 3: decreasex(&xx,mapp); break;
    };
    return (mapp->tiles[xx][yy].tl!=1 && mapp->tiles[xx][yy].tl!=3);
}
int main(){
	const int width = 78 ;
	const int height = 22 ; //tymczasowo stałe
	const int initial_length = 3 ;
	bool main_loop = true ;
	bool run = false ;
	struct map themap=initmap(width,height,initial_length);
	while (main_loop){
		if (run){
            run=tickle(&themap);
            //wyswietl
            if(!run){
            //!przegrałeś - komunikat
            }
		}else{
            //!menu
		}
		main_loop=false ; //do usunięcia
	}
	for(int i=0; i<themap.mapsizex; i++){
        free(themap.tiles[i]);
    };
    printf("THE END\n");
	return 0;
}
