#pragma once

#include "../utils/Arduboy2Ext.h"
#include "../utils/Utils.h"
#include "../utils/Enums.h"

class Level {

  public: 

    Level(){};
        
    LevelElement getLevelData(const uint8_t x, const uint8_t y);
    void loadLevel();

    uint8_t getHeight();
    uint8_t getWidth();
    int16_t getXOffset();
    int16_t getYOffset();
    int8_t getXOffsetDelta();
    int8_t getYOffsetDelta();
    
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

void Level::loadLevel() {
      Serial.println("LoadLevel");
  for (uint8_t y = 0; y < _height; y++) {

    for (uint8_t x = 0; x < _width; x++) {

      _levelData[x][y] = pgm_read_byte(&Level1[(y * _width) + x]);

    }

  }

  for (uint8_t y = 0; y < _height; y++) {

    for (uint8_t x = 0; x < _width; x++) {

      Serial.print(_levelData[x][y]);
      Serial.print(" ");

    }
      Serial.println(" ");

  }

}

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

void Level::setLevelData(const uint8_t x, const uint8_t y, const LevelElement levelElement) {

  if (x % 2 == 0) {

    _levelData[x / 2][y] = (_levelData[x / 2][y] & 0x0f) | ((uint8_t)levelElement << 4); 

  }
  else {

    _levelData[x / 2][y] = (_levelData[x / 2][y] & 0xf0) | (uint8_t)levelElement; 
    
  }
      
}