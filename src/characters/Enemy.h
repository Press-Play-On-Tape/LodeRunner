#pragma once

#include "../utils/Arduboy2Ext.h"
#include "../utils/Utils.h"
#include "../utils/Enums.h"

class Enemy {

  public: 

    Enemy() {};
  
    uint8_t getId();
    uint16_t getX();
    uint16_t getY();
    int8_t getXDelta();
    int8_t getYDelta();
    int8_t getXFuturePosition();
    int8_t getYFuturePosition();
    uint8_t getXRebirth();
    uint8_t getYRebirth();
    bool getEnabled();
    uint8_t getHasGold();
    PlayerStance getStance();
    EscapeHole getEscapeHole();
    
    void setId(uint8_t val);
    void setX(uint16_t val);
    void setY(uint16_t val);
    void setXDelta(int8_t val);
    void setYDelta(int8_t val);
    void setXFuturePosition(int8_t val);
    void setYFuturePosition(int8_t val);
    void setXRebirth(uint8_t val);
    void setYRebirth(uint8_t val);
    void setEnabled(bool val);
    void setHasGold(uint8_t val);
    void setStance(const PlayerStance val);
    void setEscapeHole(const EscapeHole val);

  private:

  uint8_t _flags;           // bits 0 - 3 enemy id, bits 4 enabled
  uint8_t _futurePosition;  // bits 0 - 3 X, bits 4 - 7 Y
  uint16_t _x;
  uint16_t _y;
  int8_t _xDelta;
  int8_t _yDelta;
  uint8_t _hasGold;
  uint8_t _xRebirth;
  uint8_t _yRebirth;

  PlayerStance _stance;
  EscapeHole _escapeHole;

};

//--------------------------------------------------------------------------------------------------------------------------

uint8_t Enemy::getId() {
  return (_flags & 0x0f);
}

uint16_t Enemy::getX() {
  return _x;
}

uint16_t Enemy::getY() {
  return _y;
}

int8_t Enemy::getXDelta() {
  return _xDelta;
}

int8_t Enemy::getYDelta() {
  return _yDelta;
}

int8_t Enemy::getXFuturePosition() {
  return (_futurePosition & 0x0f);
}

int8_t Enemy::getYFuturePosition() {
  return (_futurePosition & 0xF0) >> 4;
}

uint8_t Enemy::getXRebirth() {
  return _xRebirth;
}

uint8_t Enemy::getYRebirth() {
  return _yRebirth;
}
bool Enemy::getEnabled() {
  return (_flags & 0x10) == 0x10;
}

uint8_t Enemy::getHasGold() {
  return _hasGold;
}

PlayerStance Enemy::getStance() {
  return _stance;
}

EscapeHole Enemy::getEscapeHole() {
  return _escapeHole;
}
    
void Enemy::setId(uint8_t val) {
  _flags = (_flags & 0xf0) | val;
}
    
void Enemy::setX(uint16_t val) {
  _x = val;
}

void Enemy::setY(uint16_t val) {
  _y = val;
}

void Enemy::setXDelta(int8_t val) {
  _xDelta = val;
}

void Enemy::setYDelta(int8_t val) {
  _yDelta = val;
}

void Enemy::setXFuturePosition(int8_t val) {
  _futurePosition = (_futurePosition & 0xf0) | val;
}

void Enemy::setYFuturePosition(int8_t val) {
  _futurePosition = (_futurePosition & 0x0f) | (val << 4);
}

void Enemy::setXRebirth(uint8_t val) {
  _xRebirth = val;
}

void Enemy::setYRebirth(uint8_t val) {
  _yRebirth = val;
}

void Enemy::setEnabled(bool val) {
  _flags = (_flags | (val ? 0x10 : 0x00));
}

void Enemy::setHasGold(uint8_t val) {
  _hasGold = val;
}

void Enemy::setStance(const PlayerStance val) {
  _stance = val;
}

void Enemy::setEscapeHole(const EscapeHole val) {
  _escapeHole = val;
}
