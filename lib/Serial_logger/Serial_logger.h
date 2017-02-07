#ifndef _SERIAL_LOGGER
#define _SERIAL_LOGGER

class Serial_logger{

    public:
        Serial_logger();

        void print(char* msg);
        void print(int);
        void println(char*);
        void println(uint8_t);
};

#endif //_SERIAL_LOGGER