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
    driver = new ILI9481_pacman();
    pm_pos = {1,1};
    pm_dir = utils::DOWN;
}

pacman::~pacman()
{
    //dtor
}

bool pacman::updateGame(){
	pm_pos = render->drawPacman(pm_dir);

	logger.print("x: ");
	logger.println(pm_pos.x);
	logger.print("y: ");
	logger.println(pm_pos.y);
	
	if(pm_pos.x < 1 && pm_pos.y < 10 ){
		pm_dir = utils::DOWN;
  	}
  	else if (pm_pos.x < 6 && pm_pos.y > 9 ){
		pm_dir = utils::RIGHT;
  	}
  	else if (pm_pos.x > 5 && pm_pos.y > 0){
		pm_dir = utils::UP;
  	}
  	else if (pm_pos.x > 1 && pm_pos.y < 1){
		pm_dir = utils::LEFT;
  	}
  	
    return true;
}

void setup(){
   logger = Serial_logger();
}

void pacman::pm_border_test(){
    render->draw_pm_border(utils::LEFT);
}

void pacman::clearScreen(){
    render->clearScreen(colors::RED);
}

pacmanField* pacman::loadField(){

}

pacmanField* pacman::genTestField(uint8_t width, uint8_t height){
	pacmanField* field = new pacmanField(width, height);

	field->assignHWall(0b1111111111111111, 0);
	field->assignHWall(0b1111000011111101, 1);

	field->assignVWall(0b0000111100001111, 0b0000111100001111, 0);
	field->assignVWall(0b1111000011110000, 0b1111000011110001, 1);

	logger.println(field->hasWall(0,0, utils::LEFT)); //0
	logger.println(field->hasWall(0,31, utils::LEFT)); //1
	logger.println(field->hasWall(0,31, utils::RIGHT)); //1

	logger.println("Start for loop");
	for (uint8_t i = 0; i < 32; i++){
		logger.println(field->hasWall(0,i, utils::RIGHT)); 
	}
	logger.println("I wanna know!");
	logger.println(field->hasWall(0,3, utils::RIGHT)); // 1
	logger.println(field->hasWall(1,3, utils::LEFT)); // 1

	logger.println(field->hasWall(0,0, utils::UP)); // 1
	logger.println(field->hasWall(15,0, utils::UP)); // 1
	logger.println(field->hasWall(7,0, utils::UP)); // 1
	
	logger.println(field->hasWall(5,0, utils::DOWN)); //0
	logger.println(field->hasWall(5,1, utils::UP)); //0

	// field->assignTile(0,0, new Tile(0));
	// field->assignTile(1,0, new Tile(1));
	// field->assignTile(0,1, new Tile(1));
	// field->assignTile(1,1, new Tile(4));
 //    logger.println("Inquiring field data");
 //    logger.println(field->getTile(1,0)->getTileProp());
 //    logger.println(field->getTile(0,0)->hasNorthWall());
 //    logger.println(field->getTile(1,0)->hasNorthWall());
	// logger.println(field->getTile(1,0)->hasEastWall());
	// logger.println(field->getTile(1,0)->hasSouthWall());
	// logger.println(field->getTile(1,0)->hasWestWall());
	// logger.println(field->getTile(1,1)->hasWestWall());
	// logger.println(field->getTile(1,1)->hasSouthWall());
}


void loop() {
		
	pacman p;
    p.clearScreen();
	pacman_renderer* render = new pacman_renderer(p.getDriver(), p.genTestField(16,32));
	p.setRenderer(render);
    logger.println("Renderer added");
    

    //ILI9481_driver* d = p.getDriver();


	while( p.updateGame()){
        
		delay(100);
	}


    while(1){}
	
}