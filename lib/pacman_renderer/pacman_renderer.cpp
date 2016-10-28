#include <pacman_renderer.h>
#include <ILI9481_driver.h>
#include <Wire.h>
// pacman_renderer::pacman_renderer(int width, int length, pacmanField* field){
//         tileSize = 1;
// }

pacman_renderer::pacman_renderer(int width, int length){
    tileSize = 2;
    tft = new ILI9481_driver();
}

int pacman_renderer::calculateTileSize(int width, int length){

}

utils::position pacman_renderer::drawPacman(utils::position pos, utils::direction dir){
    //tft->fillCircle(100,100, 50, YELLOW);
    utils::position retVal = {0,0};
    return retVal;
}

