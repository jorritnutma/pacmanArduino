#include "pacmanField.h"

pacmanField::pacmanField(uint8_t width, uint8_t height, utils::position pm_start, utils::position monsters_start)
{
	if (width > MAX_V_LINES || height > MAX_H_LINES){
		return;
	}
	x_tiles = width;
	y_tiles = height;

	pm_start_pos = pm_start;
	monster_start_pos= monsters_start;
}

pacmanField::~pacmanField()
{
    //dtor
}

bool pacmanField::hasWall(uint8_t x, uint8_t y, int dir){
	
	uint16_t x_mask = 1 << (x_tiles - x - 1);
	uint16_t y_mask;

	if (y > 15){
	 	y_mask = 1 << (y_tiles - y - 17);	
	}
	else {
		y_mask = 1 << (y_tiles - y - 1);
	}
	switch (dir){
	case utils::UP :
		return (h_walls[y] & x_mask); 
	case utils::DOWN :
		return (h_walls[y+1] & x_mask);
	case utils::LEFT :
		if ( y > 15 ){
			return (v_walls1[x] & y_mask);
		}
		else {
			return (v_walls0[x] & y_mask);
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

bool pacmanField::hasSpecialDot(uint8_t x, uint8_t y){
    for(int i=0; i < sizeof(special_dots); i++){
        if (special_dots[i].x == x && special_dots[i].y == y){
            return true;
        }
    }
    return false;
}

void pacmanField::specialDotEaten(uint8_t x, uint8_t y){
    for(int i=0; i < sizeof(special_dots); i++){
        if (special_dots[i].x == x && special_dots[i].y == y){
            special_dots[i] = {255, 255};
            return;
        }
    }
}

bool pacmanField::hasDot(uint8_t x, uint8_t y){
    uint16_t mask = 1 << x;
    return dots[y] & mask;
}

void pacmanField::eatDot(uint8_t x, uint8_t y){
    uint16_t mask = (1 << x);
    dots[y] &= ~mask;
}

pacmanField::dot pacmanField::getDotType(utils::position pos){
    if ( hasDot(pos.x, pos.y)){
        return dot::yes;
    }
    else if (hasSpecialDot(pos.x, pos.y)){
        return dot::special;
    }
    else{
        return dot::no;
    }
}

void pacmanField::assignDot(utils::position pos){
    uint16_t mask = 1 << pos.x;
    dots[pos.y] |= mask;
}

void pacmanField::assignSpecialDots(){

}

void pacmanField::assignVWall(uint16_t wallDef0, uint16_t wallDef1, uint8_t col){
	v_walls0[col] = wallDef0; 
	v_walls1[col] = wallDef1;
}

void pacmanField::assignHWall(uint16_t wallDef, uint8_t row){
	h_walls[row] = wallDef;
}
