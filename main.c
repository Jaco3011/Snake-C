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
int main(){
	bool main_loop = true ;
	while (main_loop){
		
	}
	return 0;
}
