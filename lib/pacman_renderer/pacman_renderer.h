#ifndef _PACMANRENDERER
#define _PACMANRENDERER

#include <pacman_utils.h>
#include "ILI9481_driver.h"
//#include <pacmanField.h>

//#define BLACK   0x0000
//#define BLUE    0x001F
//#define RED     0xF800
//#define GREEN   0x07E0
//#define CYAN    0x07FF
//#define MAGENTA 0xF81F
//#define YELLOW  0xFFE0
//#define WHITE   0xFFFF

class pacman_renderer
{
private:
	int tileSize;
    ILI9481_driver* tft;

    int calculateTileSize(int,int);

public :

    //pacmanRenderer(int, int, pacmanField*);
    pacman_renderer(int, int);\
	int getTileSize(){return tileSize;}
	int color = ILI9341_BLACK;
	//void drawLine(){tft->drawLine(50,50,70, 70, 0x001F);}
	//void drawCircle(){tft->drawCircle(20,20, 10, 0x001F);}
	void clearScreen(int color){tft->LCD_Clear(color);}
	void clearScreen(){tft->LCD_Clear(ILI9341_BLACK);}
	utils::position drawPacman( utils::position pos, utils::direction dir);


};

#endif
