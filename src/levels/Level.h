#pragma once

#include "../utils/Arduboy2Ext.h"
#include "../utils/Utils.h"
#include "../utils/Enums.h"

class Level {

  public: 

    Level(){};
        
    LevelElement getLevelData(const uint8_t x, const uint8_t y);
    void loadLevel(Player *player, Enemy enemies[]);

    uint8_t getHeight();
    uint8_t getWidth();
    int16_t getXOffset();
    int16_t getYOffset();
    int8_t getXOffsetDelta();
    int8_t getYOffsetDelta();
    LevelPoint getReentryPoint(const uint8_t index);
    
    void setLevelData(const uint8_t x, const uint8_t y, const LevelElement levelElement);
    void setXOffset(int16_t val);
    void setYOffset(int16_t val);
    void setXOffsetDelta(int8_t val);
    void setYOffsetDelta(int8_t val);

  private:

    static const uint8_t _width = 14;
    static const uint8_t _height = 11;

    int16_t _xOffset;
    int16_t _yOffset;
    int8_t _xOffsetDelta;
    int8_t _yOffsetDelta;
    uint8_t _levelData[_width][_height];

    uint8_t _levelLadderElementCount;
    LevelPoint _levelLadder[10];
    LevelPoint _reentryPoint[4];

};

//--------------------------------------------------------------------------------------------------------------------------

uint8_t Level::getWidth() {
    return _width;
}

uint8_t Level::getHeight() {
    return _height;
}

int16_t Level::getXOffset() {
    return _xOffset;
}

int16_t Level::getYOffset() {
    return _yOffset;
}

int8_t Level::getXOffsetDelta() {
    return _xOffsetDelta;
}

int8_t Level::getYOffsetDelta() {
    return _yOffsetDelta;
}

void Level::setXOffset(int16_t val) {
    _xOffset = val;
}

void Level::setYOffset(int16_t val) {
    _yOffset = val;
}

void Level::setXOffsetDelta(int8_t val) {
    _xOffsetDelta = val;
}

void Level::setYOffsetDelta(int8_t val) {
    _yOffsetDelta = val;
}

LevelPoint Level::getReentryPoint(const uint8_t index) {

  return _reentryPoint[index];
}


// -----------------------------------------------------------------------------------------------
//  Load level data ..
//
void Level::loadLevel(Player *player, Enemy enemies[]) {

  uint8_t dataOffset = 0;


  // Load player starting position ..
  
  _xOffset = pgm_read_word_near(&Level1[dataOffset++]);         dataOffset++;
  _xOffsetDelta = pgm_read_byte(&Level1[dataOffset++]);
  _yOffset = pgm_read_word_near(&Level1[dataOffset++]);         dataOffset++;
  _yOffsetDelta = pgm_read_byte(&Level1[dataOffset++]);


  // Load player starting position ..

  player->x = pgm_read_byte(&Level1[dataOffset++]);
  player->y = pgm_read_byte(&Level1[dataOffset++]);


  // Load enemies ..

  uint8_t numberOfEnemies = pgm_read_byte(&Level1[dataOffset++]);

  for (uint8_t x = 0; x < NUMBER_OF_ENEMIES; x++) {

    if (x  < numberOfEnemies) {

      enemies[x].x = pgm_read_byte(&Level1[dataOffset++]);
      enemies[x].y = pgm_read_byte(&Level1[dataOffset++]);
      enemies[x].enabled = true;

    }
    else {

      enemies[x].enabled = false;

    }

  }


  // Load re-entry points ..

  for (uint8_t x = 0; x < 4; x++) {

    _reentryPoint[x].x = pgm_read_byte(&Level1[dataOffset++]);
    _reentryPoint[x].y = pgm_read_byte(&Level1[dataOffset++]);

  }


  // Load level ladder points ..

  _levelLadderElementCount = pgm_read_byte(&Level1[dataOffset++]);

  for (uint8_t x = 0; x < _levelLadderElementCount; x++) {

    _levelLadder[x].x = pgm_read_byte(&Level1[dataOffset++]);
    _levelLadder[x].y = pgm_read_byte(&Level1[dataOffset++]);

  }



  // Load level data ..

  for (uint8_t y = 0; y < _height; y++) {

    for (uint8_t x = 0; x < _width; x++) {

      _levelData[x][y] = pgm_read_byte(&Level1[(y * _width) + x + dataOffset]);

    }

  }

}


// -----------------------------------------------------------------------------------------------
//  Get level element at position x and y ..
//
LevelElement Level::getLevelData(const uint8_t x, const uint8_t y) {

  if ((x / 2) >= _width || y >= _height) return LevelElement::Brick;

  if (x % 2 == 0) {

    return static_cast<LevelElement>(_levelData[x / 2][y] >> 4); 

  }
  else {

    return static_cast<LevelElement>(_levelData[x / 2][y] & 0x0F); 

  }

  return LevelElement::Brick;
      
}


// -----------------------------------------------------------------------------------------------
//  Set level element at position x and y ..
//
void Level::setLevelData(const uint8_t x, const uint8_t y, const LevelElement levelElement) {

  if (x % 2 == 0) {

    _levelData[x / 2][y] = (_levelData[x / 2][y] & 0x0f) | (static_cast<uint8_t>(levelElement) << 4); 

  }
  else {

    _levelData[x / 2][y] = (_levelData[x / 2][y] & 0xf0) | static_cast<uint8_t>(levelElement); 
    
  }
      
}