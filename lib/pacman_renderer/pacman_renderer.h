#ifndef _PACMANRENDERER
#define _PACMANRENDERER

#include <utils.h>
#include "ILI9481_driver.h"
#include "Driver.h"
#include <pacmanField.h>


class pacman_renderer
{
private:
	int tileSize;
    ILI9481_driver* tft;
    int pacman_color = 0xFFE0;

    int calculateTileSize(int,int);
   	void fillCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, int16_t delta, uint16_t color);

public :

    //pacmanRenderer(int, int, pacmanField*);
    pacman_renderer(int, int, Driver*, pacmanField*);\
	int getTileSize(){return tileSize;}
	void fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);

	void clearScreen(int color){tft->LCD_Clear(color);}
	void clearScreen(){tft->LCD_Clear(colors::BLACK);}
	void drawPixelTest();
	//utils::position drawPacman( uint16_t, uint16_t, utils::direction dir);
    utils::position drawPacman( utils::position, utils::direction);
    


};

#endif
