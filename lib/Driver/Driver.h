#ifndef _DRIVER
#define _DRIVER
#include "Arduino.h"

class Driver {
    private :
        const uint16_t length;
        const uint16_t width;
    
    public :
        Driver(uint16_t length, uint16_t width);
        uint16_t getLength(){return length;}
        uint16_t getWidth(){return width;}
    };

#endif //_DRIVER