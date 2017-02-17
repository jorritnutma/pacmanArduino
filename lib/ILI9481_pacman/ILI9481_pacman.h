#ifndef ILI9481_PACMAN_H
#define ILI9481_PACMAN_H

#include "renderer_elem_pm.h"
#include "ILI9481_driver.h"
#include "utils.h"

class ILI9481_pacman : public ILI9481_driver{

private:
	const static int MAX_TILE_SIZE = 40;
	uint16_t pm_borders[MAX_TILE_SIZE >> 1];

public:
	ILI9481_pacman();
	void drawPacmanInit(renderer_elem_pm*);
	void drawPacman(renderer_elem_pm* pm_prop, utils::direction dir, uint16_t);

};

#endif // ILI9481_PACMAN_LIB_H
