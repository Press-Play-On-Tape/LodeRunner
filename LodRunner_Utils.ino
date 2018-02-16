#include "src/utils/Arduboy2Ext.h"
#include <ArduboyTones.h>

uint8_t getNearestX(int8_t margin = 5) {

  return (player.x - level.xOffset + margin) / GRID_SIZE;
  
}

uint8_t getNearestY(int8_t margin = 5) {

  return (player.y - level.yOffset + margin) / GRID_SIZE;
  
}

LevelElement getLevelData(uint8_t x, uint8_t y) {

  if ((x / 2) >= width || y >= height) return LevelElement::Brick;

  if (x % 2 == 0) {

    return static_cast<LevelElement>(levelData[x / 2][y] >> 4); 

  }
  else {

    return static_cast<LevelElement>(levelData[x / 2][y] & 0x0F); 

  }
      
}

void setLevelData(uint8_t x, uint8_t y, LevelElement levelElement) {

  if (x % 2 == 0) {

    levelData[x / 2][y] = (levelData[x / 2][y] & 0x0f) | ((uint8_t)levelElement << 4); 

  }
  else {

    levelData[x / 2][y] = (levelData[x / 2][y] & 0xf0) | (uint8_t)levelElement; 
    
  }
      
}


boolean inCellX() {

  return ((player.x - level.xOffset) % GRID_SIZE == 0);

}

boolean inCellX(uint8_t margin) {

  uint8_t rem = (player.x - level.xOffset) % GRID_SIZE;
  return (rem > (GRID_SIZE / 2) ? GRID_SIZE - rem : rem) <= margin;

}

boolean inCellY() {

  return ((player.y - level.yOffset) % GRID_SIZE == 0);

}

boolean inCellY(uint8_t margin) {

  uint8_t rem = (player.y - level.yOffset) % GRID_SIZE;

  return ((rem > (GRID_SIZE / 2) ? GRID_SIZE - rem : rem) <= margin);

}