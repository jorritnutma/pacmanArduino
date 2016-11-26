#include "utils.h"
#include "ILI9481_driver.h"
#include "pacman.h"
#include "pacman_renderer.h"
#include "pacmanField.h"
#include "Arduino.h"
#include <Wire.h>

pacman::pacman()
{
    driver = new ILI9481_driver();
    pm_pos = {20,20};
}

pacman::~pacman()
{
    //dtor
}

void pacman::updateGame(){
    //render->clearScreen();
    //render->fillCircle(50, 50, 20, colors::GREEN);
    utils::position pmpos = {150, 200};
    
    render->drawPacman(pm_pos, utils::DOWN);
    
    pm_pos.y < 460 ? pm_pos.y +=5 : pm_pos.y = 0;

    //render->drawPacman(pmpos, utils::DOWN);
    pmpos.x = 200;
    pmpos.y = 200;
    //render->drawPacman(pmpos, utils::LEFT);
}

void setup(){

}

pacmanField* pacman::loadField(){

}

void loop() {
		
	pacman p;

	p.setRenderer(new pacman_renderer(0,0, p.getDriver(), p.loadField()));
	while(1){
		p.updateGame();
		//delay(1000);

	}	
	// Serial.println("Hello world");
	// FooObject.firstFooMethod();
	//delay(1000);
	// FooObject.secondFooMethod();
	// delay(1000);

}