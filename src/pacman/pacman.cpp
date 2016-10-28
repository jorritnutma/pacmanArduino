#include "pacman_utils.h"
#include "pacman.h"
#include "pacman_renderer.h"
#include "Arduino.h"
#include <Wire.h>

pacman::pacman()
{
    render = new pacman_renderer(0,0);// new pacmanField());
}

pacman::~pacman()
{
    //dtor
}

void pacman::updateGame(){
    utils::position pmpos = {0,0};
    utils::direction pmdir = utils::UP;
    //render->drawPacman(pmpos, pmdir);
}

void setup(){
	
}

void loop() {
	
	//Serial.println("Hello world");
	//Serial.println("Were're started!");
	
	pacman p;
	//p.updateGame();

	pacman_renderer* r = p.getRenderer();
	
	while(1){
		r->clearScreen(ILI9341_YELLOW);
		delay(1000);
		r->clearScreen(ILI9341_BLUE);
		delay(1000);
	}	
	// Serial.println("Hello world");
	// FooObject.firstFooMethod();
	//delay(1000);
	// FooObject.secondFooMethod();
	// delay(1000);
	return 0;
}