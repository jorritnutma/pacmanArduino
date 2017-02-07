#ifndef _PACMANRENDERER
#define _PACMANRENDERER

#include <utils.h>
#include "ILI9481_driver.h"
#include "Driver.h"
#include <pacmanField.h>
#include "renderer_elem_pm.h"

class pacman_renderer
{
     

private:
    const static uint8_t static_tile_size = 40;
	uint8_t tileSize;
    ILI9481_driver* tft;
    uint8_t pm_borders[static_tile_size >> 1];
    uint16_t pm_x, pm_y; //These are still used by the precalc renderingfunction. TODO: remove!
    uint16_t bg_color;
    renderer_elem_pm* pm_prop;   

    int calculateTileSize(int,int);

public :

    //pacmanRenderer(int, int, pacmanField*);
    pacman_renderer(int, int, Driver*, pacmanField*);
	int getTileSize(){return tileSize;}
    void drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
    utils::position drawPacmanPreCalc(utils::direction dir);
	void clearScreen(int color){tft->LCD_Clear(color);}
	void clearScreen(){tft->LCD_Clear(colors::BLACK);}
	void drawPixelTest();
    
    void draw_pm_border(utils::direction);
	//utils::position drawPacman( uint16_t, uint16_t, utils::direction dir);
    utils::position drawPacman(utils::direction);
    void drawPacmanInit();
    


};

#endif
