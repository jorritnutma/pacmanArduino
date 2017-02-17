#ifndef _PACMANRENDERER
#define _PACMANRENDERER

#include <utils.h>
#include "ILI9481_pacman.h"
#include "Driver.h"
#include "pacmanField.h"
#include "renderer_elem_pm.h"

class pacman_renderer
{
     

private:
	uint8_t tileSize;
    ILI9481_pacman* tft;
    uint16_t pm_x, pm_y; //These are still used by the precalc renderingfunction. TODO: remove!
    uint16_t bg_color;
    renderer_elem_pm* pm_prop;   

    uint8_t calculateTileSize(int,int);

public :
    pacman_renderer(Driver*, pacmanField*);
	int getTileSize(){return tileSize;}
    void clearScreen(int color){tft->LCD_Clear(color);}
    void clearScreen(){tft->LCD_Clear(colors::BLACK);}
    utils::position drawPacman(utils::direction);

    //MORE OR LESS OBSOLETE STUFF
    //utils::position drawPacmanPreCalc(utils::direction dir);
    //void drawPixelTest();
    void drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
    void draw_pm_border(utils::direction);
};

#endif
