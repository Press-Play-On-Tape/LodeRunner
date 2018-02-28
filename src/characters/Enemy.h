#pragma once

#include "../utils/Arduboy2Ext.h"
#include "../utils/Utils.h"
#include "../utils/Enums.h"

class Enemy {
/*

*/
  public: 

    Enemy() {};
  
    uint8_t getId();
    uint16_t getX();
    uint16_t getY();
    int8_t getXDelta();
    int8_t getYDelta();
    int8_t getXFuturePosition();
    int8_t getYFuturePosition();
    bool getEnabled();
    uint8_t getHasGold();
    PlayerStance getPlayerStance();
    EscapeHole getEscapeHole();
    
    void setid(uint8_t val);
    void setX(uint16_t val);
    void setY(uint16_t val);
    void setXDelta(int8_t val);
    void setYDelta(int8_t val);
    void setXFuturePosition(int8_t val);
    void setYFuturePosition(int8_t val);
    void setEnabled(bool val);
    void setHasGold(uint8_t val);
    void setPlayerStance(const PlayerStance val);
    void setEscapeHole(const EscapeHole val);

  private:

  uint8_t _id;
  uint16_t _x;
  uint16_t _y;
  int8_t _xDelta;
  int8_t _yDelta;
  bool _enabled;
  uint8_t _hasGold;
  int8_t _xFuturePosition;
  int8_t _yFuturePosition;

  PlayerStance stance;
  EscapeHole _escapeHole;

};

//--------------------------------------------------------------------------------------------------------------------------

uint8_t Enemy::getId() {
  return _id;
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
  return _xDelta;
}

int8_t Enemy::getYFuturePosition() {
  return _yDelta;
}

bool Enemy::getEnabled() {
  return _enabled;
}

uint8_t Enemy::gatHasGold() {
  return _men;
}

PlayerStance Enemy::getEnemyStance() {
  return _stance;
}

EscapeHole Enemy::getEscapeHole() {
  return _escapeHole;
}
    
void Enemy::setId(uint8_t val) {
  _id = val;
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
  _xFuturePosition = val;
}

void Enemy::setYFuturePosition(int8_t val) {
  _yFuturePosition = val;
}

void Enemy::setEnabled(bool val) {
  _enabled = val;
}

void Enemy::setHasGold(uint8_t val) {
  _hasGold = val;
}

void Enemy::setEnemyStance(const PlayerStance val) {
  _stance = val;
}

void Enemy::setEscapeHole(const EscapeHole val) {
  _escapeHole = val;
}
