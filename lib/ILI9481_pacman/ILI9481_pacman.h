#ifndef ILI9481_PACMAN_H
#define ILI9481_PACMAN_H

#include "renderer_elem_pm.h"
#include "renderer_elem_wall.h"
#include "renderer_elem_monster.h"
#include "ILI9481_driver.h"
#include "utils.h"

class ILI9481_pacman : public ILI9481_driver{

private:
	const static int MAX_TILE_SIZE = 40;
	uint8_t pm_borders[MAX_TILE_SIZE >> 1];
	uint8_t monster_border_left[MAX_TILE_SIZE >> 1];
	uint8_t monster_border_right[MAX_TILE_SIZE >> 1];
public:
	ILI9481_pacman();
	void drawPacmanInit(renderer_elem_pm*);
	void drawPacman(renderer_elem_pm* pm_prop, utils::direction dir, uint16_t);

	void drawMonsterInit(renderer_elem_monster*);
	void drawMonster(renderer_elem_monster*, utils::direction dir, uint16_t bg_color);
	
	void cleanUpMovingElem(renderer_elem*, utils::direction, uint16_t bg_color);

	void drawVertWall(renderer_elem_wall*, uint8_t tileSize, uint8_t wall_width);
	void drawHorWall(renderer_elem_wall*, uint8_t tileSize, uint8_t wall_width);

};

#endif // ILI9481_PACMAN_LIB_H

