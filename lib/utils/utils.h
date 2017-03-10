#ifndef _UTILS
#define _UTILS

#include "Arduino.h"
namespace colors {
	
const uint16_t BLACK       (0x0000);      /*   0,   0,   0 */	
const uint16_t NAVY        (0x000F);      /*   0,   0, 128 */
const uint16_t DARKGREEN   (0x03E0);      /*   0, 128,   0 */
const uint16_t DARKCYAN    (0x03EF);      /*   0, 128, 128 */
const uint16_t MAROON      (0x7800);      /* 128,   0,   0 */
const uint16_t PURPLE      (0x780F);      /* 128,   0, 128 */
const uint16_t OLIVE       (0x7BE0);      /* 128, 128,   0 */
const uint16_t LIGHTGREY   (0xC618);      /* 192, 192, 192 */
const uint16_t DARKGREY    (0x7BEF);      /* 128, 128, 128 */
const uint16_t BLUE        (0x001F);      /*   0,   0, 255 */
const uint16_t GREEN 	   (0x07E0);      /*   0, 255,   0 */
const uint16_t CYAN        (0x07FF);      /*   0, 255, 255 */
const uint16_t RED         (0xF800);      /* 255,   0,   0 */
const uint16_t MAGENTA     (0xF81F);      /* 255,   0, 255 */
const uint16_t YELLOW      (0xFFE0);      /* 255, 255,   0 */ 
const uint16_t WHITE       (0xFFFF);      /* 255, 255, 255 */
const uint16_t ORANGE      (0xFD20);      /* 255, 165,   0 */
const uint16_t GREENYELLOW (0xAFE5);      /* 173, 255,  47 */
const uint16_t PINK        (0xF81F);
}


class utils
{
public:

	struct position
	 {
        uint16_t x;
        uint16_t y;
	 };
	
	enum direction 
	{
		UP,
		LEFT,
		RIGHT,
        DOWN
	};
	
	// enum colors
	// {
	// 	 BLACK		 =0x0000,      /*   0,   0,   0 */
	// 	 NAVY        =0x000F,      /*   0,   0, 128 */
	// 	 DARKGREEN   =0x03E0,      /*   0, 128,   0 */
	// 	 DARKCYAN    =0x03EF,      /*   0, 128, 128 */
	// 	 MAROON      =0x7800,      /* 128,   0,   0 */
	// 	 PURPLE      =0x780F,      /* 128,   0, 128 */
	// 	 OLIVE       =0x7BE0,      /* 128, 128,   0 */
	// 	 LIGHTGREY   =0xC618,      /* 192, 192, 192 */
	// 	 DARKGREY    =0x7BEF,      /* 128, 128, 128 */
	// 	 BLUE        =0x001F,      /*   0,   0, 255 */
	// 	 GREEN       =0x07E0,      /*   0, 255,   0 */
	// 	 CYAN        =0x07FF,      /*   0, 255, 255 */
	// 	 RED         =0xF800,      /* 255,   0,   0 */
	// 	 MAGENTA     =0xF81F,      /* 255,   0, 255 */
	// 	 YELLOW      =0xFFE0,      /* 255, 255,   0 */
	// 	 WHITE       =0xFFFF,      /* 255, 255, 255 */
	// 	 ORANGE      =0xFD20,      /* 255, 165,   0 */
	// 	 GREENYELLOW =0xAFE5,      /* 173, 255,  47 */
	// 	 PINK        =0xF81F		
	// }
};

#endif //_UTILS
