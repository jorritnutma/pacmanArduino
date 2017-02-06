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
    pm_pos = {1,1};
    pm_dir = utils::DOWN;
}

pacman::~pacman()
{
    //dtor
}

bool pacman::updateGame(){
    //render->clearScreen();
    //render->drawPacman(pmpos, utils::DOWN);
    //render->fillCircle(50, 50, 20, colors::GREEN);    
	render->drawPacmanPreCalc(utils::RIGHT);
	pm_pos = render->drawPacman(pm_dir);
	if (pm_pos.y == 5)
	{
		pm_dir = utils::UP;
		logger.println("turning upwards");
	}
	else if(pm_pos.y == 1){
		pm_dir = utils::DOWN;
		logger.println("turning downwards");
	}

    // render->drawCircle(pm_pos.x, pm_pos.y, 20, colors::GREEN);
    // render->drawCircle(320, 100, 30, colors::GREEN);
    
    return true;
}

void setup(){
   logger = Serial_logger();
}

void pacman::pm_border_test(){
    render->draw_pm_border(utils::LEFT);
    render->drawPacmanPreCalc(utils::RIGHT);
}

void pacman::clearScreen(){
    render->clearScreen();
}

pacmanField* pacman::loadField(){

}

void pacman::init(){
	render->drawPacmanInit(19);
}

void loop() {
		
	pacman p;

	p.setRenderer(new pacman_renderer(0,0, p.getDriver(), p.loadField()));
    logger.println("Renderer added");
    p.clearScreen();
    p.init();
    ILI9481_driver* d = p.getDriver();

    uint16_t i;

	for(i=1; i < 480; i += 20){

	  d-> Rectf(60, i, 50, 20, colors::GREEN);
	}
	for(i=1; i < 480; i += 20){

	  d-> Rectf_imp(120, i, 50, 20, colors::BLUE);
	}

	p.pm_border_test();

	while( p.updateGame()){
        
		delay(50);
	}


    while(1){}
	// Serial.println("Hello world");
	// FooObject.firstFooMethod();
	//delay(1000);
	// FooObject.secondFooMethod();
	// delay(1000);

}