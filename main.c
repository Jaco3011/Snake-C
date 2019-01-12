#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "ncurses.h"
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
	output.tiles=(struct tile**) malloc(x*y*sizeof(struct tile*));
	for (int i=0; i<x; i++){
        output.tiles[i]=(struct tile*) malloc(y * sizeof(struct tile));
	};
	for (int i=0; i<x; i++){
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
void chhead(struct map*mapp, enum direction d){
mapp->tiles[mapp->headx][mapp->heady].dr=d;
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
    raw();
    initscr();
    noecho();
    keypad(stdscr, true);
	int width = COLS ;
	int height = LINES ;
	const int initial_length = 3 ;
	//const
	bool main_loop = true ;
	bool run = true;
	time_t then=time(NULL);
	const double tickle_interval=0.5 ;
	struct map themap=initmap(width,height,initial_length);
	char mychar;
	enum direction nx ;
	while (main_loop){
        mychar=getch();
        //! obsługa znaku wejścia
        switch (mychar){
            case 'w':
            nx = up; break;
            case 'a':
            nx = left; break;
            case 's':
            nx = down; break;
            case 'd':
            nx = right; break;
            default: //nic
            ;
        }
        chhead(&themap, nx);
		if (run){
            if(difftime(time(NULL),then)>=tickle_interval){
                then=time(NULL);
                run=tickle(&themap);
                for (int i=0; i<height;i++){
                    for (int j=0;j<width;j++){
                        switch (themap.tiles[i][j].tl){
                        case 0: addch(' '); break;
                        case 1:
                        case 3:
                            switch (themap.tiles[i][j].dr){
                            case 0: addch('^'); break;
                            case 1: addch('>'); break;
                            case 2: addch('V'); break;
                            case 3: addch('<');
                            }
                        break;
                        case 2: addch('O'); break;
                        }
                    }
                    addch('\n');
                }
            }
		}else{
            //!menu
		}
		//main_loop=false ; //!do usunięcia
		refresh();
		move(0,0);
	}
	for(int i=0; i<themap.mapsizex; i++){
        free(themap.tiles[i]);
    };
    endwin();
	return 0;
}
