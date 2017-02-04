#include "utils.h"
#include "ILI9481_driver.h"
#include "pacman.h"
#include "pacman_renderer.h"
#include "pacmanField.h"
#include "Arduino.h"
#include <Wire.h>
#include "Serial_logger.h"

Serial_logger logger;

pacman::pacman()
{
    driver = new ILI9481_driver();
    pm_pos = {20,20};
}

pacman::~pacman()
{
    //dtor
}

bool pacman::updateGame(){
    //render->clearScreen();
    render->fillCircle(50, 50, 20, colors::GREEN);
    utils::position pmpos = {150, 200};
    
    render->drawPacman(pm_pos, utils::DOWN);
    
    //pm_pos.y < 460 ? pm_pos.y +=5 : pm_pos.y = 0;

    //render->drawPacman(pmpos, utils::DOWN);
    //render->fillCircle(50, 50, 20, colors::GREEN);    
    //render->drawPacman(pm_pos, utils::DOWN);
    // render->drawCircle(pm_pos.x, pm_pos.y, 20, colors::GREEN);
    // render->drawCircle(320, 100, 30, colors::GREEN);
    if (pm_pos.y < 460){
        pm_pos.y +=40;
    }
    else {
        pm_border_test();
        pm_pos.y = 0;
        return false;
    }
    return true;
}

void setup(){
   logger = Serial_logger();
}

void pacman::pm_border_test(){
    render->draw_pm_border(utils::RIGHT);
}

void pacman::clearScreen(){
    render->clearScreen();
}

pacmanField* pacman::loadField(){

}

void pacman::init(){
	render->drawPacmanInit(20);
}

void loop() {
		
	pacman p;

	p.setRenderer(new pacman_renderer(0,0, p.getDriver(), p.loadField()));
    logger.println("setRenderer added");
    p.clearScreen();

	while( p.updateGame()){
        
		//delay(1000);

	}

    while(1){}
	// Serial.println("Hello world");
	// FooObject.firstFooMethod();
	//delay(1000);
	// FooObject.secondFooMethod();
	// delay(1000);

}