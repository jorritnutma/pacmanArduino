#ifndef _PACMANRENDERER
#define _PACMANRENDERER

#include <utils.h>
#include "ILI9481_driver.h"
#include "Driver.h"
#include <pacmanField.h>


class pacman_renderer
{
     

private:
    const static uint8_t static_tile_size = 40;
	uint8_t tileSize;
    ILI9481_driver* tft;
    int pacman_color = 0xFFE0;
    char pm_borders[static_tile_size >> 1];
    uint16_t pm_x, pm_y;
    int calculateTileSize(int,int);
   	void fillCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, int16_t delta, uint16_t color);

public :

    //pacmanRenderer(int, int, pacmanField*);
    pacman_renderer(int, int, Driver*, pacmanField*);\
	int getTileSize(){return tileSize;}
	void fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
    void drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
    utils::position drawPacmanPreCalc(utils::direction dir);
	void clearScreen(int color){tft->LCD_Clear(color);}
	void clearScreen(){tft->LCD_Clear(colors::BLACK);}
	void drawPixelTest();
    
    void draw_pm_border(utils::direction);
	//utils::position drawPacman( uint16_t, uint16_t, utils::direction dir);
    utils::position drawPacman( utils::position, utils::direction);
    void drawPacmanInit(uint16_t r);
    


};

#endif
