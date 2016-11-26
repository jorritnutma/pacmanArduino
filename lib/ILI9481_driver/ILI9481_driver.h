#ifndef ILI9481_driver_H_INCLUDED
#define ILI9481_driver_H_INCLUDED

//#include <utils.h>
#include <Arduino.h>
#include "Driver.h"
//#include <pin_magic.h>

//Technical support:goodtft@163.com
// Breakout/Arduino UNO pin usage:
// LCD Data Bit :   7   6   5   4   3   2   1   0
// Uno dig. pin :   7   6   5   4   3   2   9   8
// Uno port/pin : PD7 PD6 PD5 PD4 PD3 PD2 PB1 PB0
// Mega dig. pin:  29  28  27  26  25  24  23  22
#define LCD_RD   A0
#define LCD_WR   A1
#define LCD_RS   A2
#define LCD_CS   A3
#define LCD_REST A4
#define WR_MASK B00000010
#define RS_MASK B00000100


class ILI9481_driver : public Driver {

public :

    ILI9481_driver();

    void drawPixel(int16_t x, int16_t y, uint16_t color);

    void Lcd_Init(void);

    void H_line(unsigned int x, unsigned int y, unsigned int l, unsigned int c);
    void V_line(unsigned int x, unsigned int y, unsigned int l, unsigned int c);

    void Rect(unsigned int x,unsigned int y,unsigned int w,unsigned int h,unsigned int c);
    void Rectf(unsigned int x,unsigned int y,unsigned int w,unsigned int h,unsigned int c);
    void LCD_Clear(unsigned int j);
    int RGB(int r,int g,int b) {return r << 16 | g << 8 | b;}

    int getScreenWidth(){return width;}
    int getScreenLength(){return length;}

private:
    int width, length;

    void Lcd_Write_Bus(unsigned char d);

    void Lcd_Write_Com(unsigned char VH);

    void Lcd_Write_Data(unsigned char VH);

    void Lcd_Write_Com_Data(unsigned char com,unsigned char dat);

    void Address_set(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2);
//
//               // These items may have previously been defined as macros
//           // in pin_magic.h.  If not, function versions are declared:
//#ifndef write8
//        void write8(uint8_t value),
//#endif
//#ifndef setWriteDir
//           setWriteDir(void),
//#endif
//#ifndef setReadDir
//           setReadDir(void),
//#endif
//#ifndef writeRegister8
//           writeRegister8(uint8_t a, uint8_t d),
//#endif
//#ifndef writeRegister16
//           writeRegister16(uint16_t a, uint16_t d),
//#endif
//    writeRegister24(uint8_t a, uint32_t d),
//    writeRegister32(uint8_t a, uint32_t d),
//#ifndef writeRegisterPair
//           writeRegisterPair(uint8_t aH, uint8_t aL, uint16_t d),
//#endif
//           setLR(void),
//           flood(uint16_t color, uint32_t len);
//  uint8_t  driver;
//
//#ifndef read8
//  uint8_t  read8fn(void);
//  #define  read8isFunctionalized
//#endif
//
//#ifndef USE_ADAFRUIT_SHIELD_PINOUT
//
//  #ifdef __AVR__
//    volatile uint8_t *csPort    , *cdPort    , *wrPort    , *rdPort;
//	uint8_t           csPinSet  ,  cdPinSet  ,  wrPinSet  ,  rdPinSet  ,
//					  csPinUnset,  cdPinUnset,  wrPinUnset,  rdPinUnset,
//					  _reset;
//  #endif
//  #if defined(__SAM3X8E__)
//    Pio *csPort    , *cdPort    , *wrPort    , *rdPort;
//	uint32_t          csPinSet  ,  cdPinSet  ,  wrPinSet  ,  rdPinSet  ,
//					  csPinUnset,  cdPinUnset,  wrPinUnset,  rdPinUnset,
//					  _reset;
//  #endif
//
//#endif
};


#endif // ILI9481_driver_H_INCLUDED
