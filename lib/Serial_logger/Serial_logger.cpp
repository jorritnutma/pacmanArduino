#include "Arduino.h"
#include "Serial_logger.h"

Serial_logger::Serial_logger(){
    Serial.begin(9600);
}

void Serial_logger::print(char* msg){
    Serial.print(msg);
}

void Serial_logger::print(int msg){
    Serial.print(msg);
}

void Serial_logger::println(char* msg){
    Serial.println(msg);
}

void Serial_logger::println(int msg){
    Serial.println(msg);
}