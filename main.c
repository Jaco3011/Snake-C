#include <stdio.h>
#include <stdbool.h>
enum direction{
	up = 0,
	right = 1,
	down = 2,
	left = 3
};
enum tile_content{
	empty = 0,
	snake = 1,
	food = 2
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
	for (int i=0; i<x; i++){
		for (int j=0; j<y; j++){
			output.tiles[i][j]=zerotile ;
		};
	};
	output.mapsizex=x;
	output.mapsizey=y;
	//todo
	return output;
}
int main(){
	const int width = 40 ;
	const int height = 20 ; //tymczasowo sta³e
	const int initial_length = 3 ;
	bool main_loop = true ;
	bool run = false ;
	struct map themap=initmap(width,height,initial_length);
	while (main_loop){
		//printf
	}
	return 0;
}
