#ifndef _PACMANRENDERER
#define _PACMANRENDERER

#include <utils.h>
#include "ILI9481_pacman.h"
#include "Driver.h"
#include "pacmanField.h"
#include "renderer_elem_pm.h"
#include "renderer_elem_monster.h"
#include "renderer_elem.h"

class pacman_renderer
{

private:
    
	uint16_t tileSize;
    ILI9481_pacman* tft;
    uint16_t pm_x, pm_y; //These are still used by the precalc renderingfunction. TODO: remove!
    uint16_t bg_color;
    renderer_elem_pm* pm_prop;
    renderer_elem_monster* monster_prop[pacmanField::MAX_NUMBER_MONSTERS];
    renderer_elem* dot_prop;
    renderer_elem* special_dot_prop;
    uint8_t wall_width;
    uint8_t calculateTileSize(uint16_t,uint16_t);
    utils::position determineNewFieldPos(utils::direction, renderer_elem*);
    
public :
    pacman_renderer(Driver*, pacmanField*);
	uint16_t getTileSize(){return tileSize;}
    void clearScreen(int color){tft->LCD_Clear(color);}
    void clearScreen(){tft->LCD_Clear(colors::BLACK);}
    void drawDots(pacmanField* field);
    utils::position drawPacman(utils::direction);
    utils::position drawMonster(utils::direction, pacmanField::dot dotType);
    void drawWalls(pacmanField*);
    void checkBorders(pacmanField* field);
    
    //MORE OR LESS OBSOLETE STUFF
    void drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
    void draw_pm_border(utils::direction);
};

#endif
