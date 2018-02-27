#include "src/utils/Arduboy2Ext.h"
#include <ArduboyTones.h>

uint8_t getNearestX(int8_t margin) {

  return (player.x - level.getXOffset() + margin) / GRID_SIZE;
  
}

uint8_t getNearestY(int8_t margin) {

  return (player.y - level.getYOffset() + margin) / GRID_SIZE;
  
}

boolean inCellX() {

  return ((player.x - level.getXOffset()) % GRID_SIZE == 0);

}

boolean inCellX(uint8_t margin) {

  uint8_t rem = (player.x - level.getXOffset()) % GRID_SIZE;
  return (rem > (GRID_SIZE / 2) ? GRID_SIZE - rem : rem) <= margin;

}

boolean inCellY() {

  return ((player.y - level.getYOffset()) % GRID_SIZE == 0);

}

boolean inCellY(uint8_t margin) {

  uint8_t rem = (player.y - level.getYOffset()) % GRID_SIZE;

  return ((rem > (GRID_SIZE / 2) ? GRID_SIZE - rem : rem) <= margin);

}


PlayerStance getNextStance(PlayerStance stance) {

  switch (stance) {

    case PlayerStance::Swinging_Left4:        return PlayerStance::Swinging_Left1;
    case PlayerStance::Swinging_Left3:        return PlayerStance::Swinging_Left4;
    case PlayerStance::Swinging_Left2:        return PlayerStance::Swinging_Left3;
    case PlayerStance::Swinging_Left1:        return PlayerStance::Swinging_Left2;
    case PlayerStance::Climbing_Down2:        return PlayerStance::Climbing_Down1;
    case PlayerStance::Climbing_Down1:        return PlayerStance::Climbing_Down2;
    case PlayerStance::Running_Left4:         return PlayerStance::Running_Left1;
    case PlayerStance::Running_Left3:         return PlayerStance::Running_Left4;
    case PlayerStance::Running_Left2:         return PlayerStance::Running_Left3;
    case PlayerStance::Running_Left1:         return PlayerStance::Running_Left2;
    case PlayerStance::Running_Right1:        return PlayerStance::Running_Right2;
    case PlayerStance::Running_Right2:        return PlayerStance::Running_Right3;
    case PlayerStance::Running_Right3:        return PlayerStance::Running_Right4;
    case PlayerStance::Running_Right4:        return PlayerStance::Running_Right1;
    case PlayerStance::Climbing_Up1:          return PlayerStance::Climbing_Up2;
    case PlayerStance::Climbing_Up2:          return PlayerStance::Climbing_Up1;
    case PlayerStance::Swinging_Right1:       return PlayerStance::Swinging_Right2;
    case PlayerStance::Swinging_Right2:       return PlayerStance::Swinging_Right3;
    case PlayerStance::Swinging_Right3:       return PlayerStance::Swinging_Right4;
    case PlayerStance::Swinging_Right4:       return PlayerStance::Swinging_Right1;
    case PlayerStance::Rebirth_1:             return PlayerStance::Rebirth_2;
    case PlayerStance::Rebirth_2:             return PlayerStance::Rebirth_3;
    case PlayerStance::Rebirth_3:             return PlayerStance::StandingStill;
    default:                                  return stance;

  }

}

Direction getDirection_16Directions(int16_t xDiff, int16_t yDiff) {

  if (xDiff < 0) {
  
    if (yDiff > 0) {
    
      if (absT(xDiff) - absT(yDiff) > 0)    { return Direction::RightUp1; }
      if (absT(xDiff) - absT(yDiff) == 0)   { return Direction::RightUp; }
      if (absT(xDiff) - absT(yDiff) < 0)    { return Direction::RightUp2; }
      
    }
    else if (yDiff < 0) {
    
      if (absT(xDiff) - absT(yDiff) < 0)    { return Direction::RightDown1; }
      if (absT(xDiff) - absT(yDiff) == 0)   { return Direction::RightDown; }
      if (absT(xDiff) - absT(yDiff) > 0)    { return Direction::RightDown2; }
    
    }
    else {
    
      return Direction::Right;
      
    }
  
  } 
  else if (xDiff > 0) {
  
    if (yDiff > 0) {
    
      if (absT(xDiff) - absT(yDiff) > 0)    { return Direction::LeftUp1; }
      if (absT(xDiff) - absT(yDiff) == 0)   { return Direction::LeftUp; }
      if (absT(xDiff) - absT(yDiff) < 0)    { return Direction::LeftUp2; }
      
    }
    else if (yDiff < 0) {
    
      if (absT(xDiff) - absT(yDiff) < 0)    { return Direction::LeftDown1; }
      if (absT(xDiff) - absT(yDiff) == 0)   { return Direction::LeftDown; }
      if (absT(xDiff) - absT(yDiff) > 0)    { return Direction::LeftDown2; }
    
    }
    else {
    
      return Direction::Left;
      
    }
  
  }
  else {  
  
    if (yDiff < 0) {
    
      return Direction::Down;
      
    }
    else if (yDiff > 0) {
    
      return Direction::Up;
      
    }
    else {
    
      return Direction::Up;   // Player should be dead !
      
    }
  
  }

  return Direction::Up;       // Default, should never get here!

}

#define THRESHOLD 4

#ifdef INC_ARROWS

Direction getDirection_8Directions(int8_t xDiff, int8_t yDiff) {

  auto ax = abs(xDiff);
  auto ay = abs(yDiff);

  if (xDiff > 0) {  // left
  
    if (yDiff > 0) { // up
      
      if (ay - ax > THRESHOLD)        return Direction::Up;
      else if (ax - ay > THRESHOLD)   return Direction::Left;
      else                            return Direction::LeftUp;

    }
    else if (yDiff < 0) { //down
      
      if (ay - ax > THRESHOLD)        return Direction::Down;
      else if (ax - ay > THRESHOLD)   return Direction::Left;
      else                            return Direction::LeftDown;

    }
    else                              return Direction::Left;    

  }
  else if (xDiff < 0) {

    if (yDiff > 0) { // up
      
      if (ay - ax > THRESHOLD)        return Direction::Up;
      else if (ax - ay > THRESHOLD)   return Direction::Right;
      else                            return Direction::RightUp;

    }
    else if (yDiff < 0) { //down
      
      if (ay - ax > THRESHOLD)        return Direction::Down;
      else if (ax - ay > THRESHOLD)   return Direction::Right;
      else                            return Direction::RightDown;

    }
    else                              return Direction::Right;    

  }
  else {

    if (yDiff < 0)                    return Direction::Down;
    else if (yDiff > 0)               return Direction::Up;
    else                              return Direction::Up; 

  }
  
  return                              Direction::Up;       // Default, should never get here!

}

#endif

