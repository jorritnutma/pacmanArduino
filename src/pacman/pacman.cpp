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
    pm_pos = {0,0};
    pm_dir = utils::DOWN;
}

pacman::~pacman()
{
    //dtor
}

bool pacman::updateGame(){
	pm_pos = render->drawPacman(pm_dir);

	if (monster_pos[0].x != monster_prev_pos[0].x || monster_pos[0].y != monster_prev_pos[0].y){
		monster_dir[0] = moveElementRandom(monster_pos[0], monster_dir[0]);
	}
	monster_prev_pos[0] = monster_pos[0];
	monster_pos[0] = render->drawMonster(monster_dir[0]);
	

	logger.print("x: ");
	logger.println(pm_pos.x);
	logger.print("y: ");
	logger.println(pm_pos.y);
	logger.println(pm_dir);
	
	if(pm_pos.x < 1 && pm_pos.y < 14 ){
		pm_dir = utils::DOWN;
  	}
  	else if (pm_pos.x < 9 && pm_pos.y > 13 ){
		pm_dir = utils::RIGHT;
  	}
  	else if (pm_pos.x > 8 && pm_pos.y > 0){
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
    render->clearScreen();
}

pacmanField* pacman::loadField(){

}

utils::direction pacman::moveElementRandom(utils::position pos, utils::direction dir){

	utils::direction options[4]={0,0,0,0};
	uint8_t num_option=0;

	for (uint8_t i = 0; i < 4; i++){
		if ( i != 3 - dir && !field->hasWall(pos.x, pos.y, i) ){
			options[num_option] = i;
			num_option++;
		}
	}
	if ( num_option == 0) {
		return 3 - dir;
	}
	return options[random(num_option)];
}

pacmanField* pacman::genTestField(uint8_t width, uint8_t height){
	utils::position m_pos = {4,6};
    utils::position pm_pos = {0,0};
	pacmanField* field = new pacmanField(width, height, pm_pos, m_pos);
					//	 10       1
	field->assignHWall(0b1111111111, 0);
	field->assignHWall(0b0111111110, 1);
	field->assignHWall(0b0011111100, 2);
	field->assignHWall(0b0111111100, 3);
	field->assignHWall(0b0100111100, 4);
	field->assignHWall(0b0100111100, 5);
	field->assignHWall(0b0100100100, 6);
	field->assignHWall(0b0110001110, 7);
	field->assignHWall(0b0100001100, 8);
	field->assignHWall(0b0100111100, 9);
	field->assignHWall(0b0100111100, 10);
	field->assignHWall(0b0100111100, 11);
	field->assignHWall(0b0100111100, 12);
	field->assignHWall(0b0100111100, 13);
	field->assignHWall(0b0111111110, 14);
	field->assignHWall(0b0100111100, 15);
	
					//   15            1
	field->assignVWall(0b111111111111111, 0, 0);
	field->assignVWall(0b011111111111110, 0, 1);
	field->assignVWall(0b011100001111000, 0, 2);
	field->assignVWall(0b011100001111000, 0, 3);
	field->assignVWall(0b011100111111000, 0, 4);
	field->assignVWall(0b011100101111000, 0, 5);
	field->assignVWall(0b011100000111000, 0, 6);
	field->assignVWall(0b011100001111000, 0, 7);
	field->assignVWall(0b011100001111000, 0, 8);
	field->assignVWall(0b011111111111110, 0, 9);

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

	return field;
}


void loop() {
		
	pacman p;
    p.clearScreen();

    pacmanField* f = p.genTestField(10,15);
	
	p.setField(f);
	pacman_renderer* render = new pacman_renderer(p.getDriver(), p.getField() );
	p.setRenderer(render);
    logger.println("Renderer added");
    

    //ILI9481_driver* d = p.getDriver();


	while( p.updateGame()){
        
		delay(100);
	}


    while(1){}
	
}