#include "pacmanField.h"

pacmanField::pacmanField(uint8_t width, uint8_t height)
{
	if (width > MAX_V_LINES || height > MAX_H_LINES){
		return;
	}
	x_tiles = width;
	y_tiles = height;
}

pacmanField::~pacmanField()
{
    //dtor
}

bool pacmanField::hasWall(uint8_t x, uint8_t y, utils::direction dir){
	
	uint16_t x_mask = 1 << (x_tiles - x - 1);
	uint16_t y_mask;

	if (y > 15){
		 y_mask = 1 << (y_tiles - y - 1);
	}
	else {
	 	y_mask = 1 << (y_tiles - y - 17);	
	}
	switch (dir){
	case utils::UP :
		return (h_walls[y] & x_mask); 
	case utils::DOWN :
		return (h_walls[y+1] & x_mask);
	case utils::LEFT :
		if ( y > 15 ){
			return v_walls1[x] & y_mask;
		}
		else {
			return v_walls0[x] & y_mask;
		}
	case utils::RIGHT :
		if (y> 15){
			return v_walls1[x+1] & y_mask ;	
		}
		else {
			return v_walls0[x+1] & y_mask;
		}
	}
}

void pacmanField::assignVWall(uint16_t wallDef0, uint16_t wallDef1, uint8_t col){
		v_walls0[col] = wallDef0; 
		v_walls1[col] = wallDef1;
}

void pacmanField::assignHWall(uint16_t wallDef, uint8_t row){
	h_walls[row] = wallDef;
}
// bool pacmanField::hasEastWall(uint8_t x, uint8_t y){

// }
//         bool hasSouthWall(uint8_t, uint8_t);
//         bool hasWestWall(uint8_t, uint8_t);
