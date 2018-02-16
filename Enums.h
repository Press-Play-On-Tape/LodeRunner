#pragma once

#include "src/utils/Arduboy2Ext.h"
#include "Utils.h"

#define HEIGHT_LESS_TOOLBAR 56
#define NUMBER_OF_ENEMIES 10
#define GRID_SIZE 10

enum class LevelElement : uint8_t {

  Blank,       // 0
  Brick,       // 1
  Solid,       // 2
  Ladder,      // 3
  Rail,        // 4
  LadderLevel, // 5
  Gold,        // 6
  Brick_1,     // 7
  Brick_2,     // 8
  Brick_3,     // 9
  Brick_4,     // 10
  Brick_Transition,  // 11
  Brick_Close_1,  // 12
  Brick_Close_2,  // 13
  Brick_Close_3,  // 14
  Brick_Close_4,  // 15
  
};

enum class PlayerStance : int8_t {

  Burn_Left = -12,
  Swinging_Left4 = -10,
  Swinging_Left3,
  Swinging_Left2,
  Swinging_Left1,
  Climbing_Down2 = -6,
  Climbing_Down1,
  Running_Left4 = -4,
  Running_Left3,
  Running_Left2,
  Running_Left1,
  StandingStill = 0,  
  Running_Right1 = 1,
  Running_Right2,
  Running_Right3,
  Running_Right4,
  Climbing_Up1 = 5,
  Climbing_Up2,
  Swinging_Right1 = 7,
  Swinging_Right2,
  Swinging_Right3,
  Swinging_Right4,
  Falling = 11,
  Burn_Right = 12,

};

enum class Direction : uint8_t {
  Up,
  RightUp1,
  RightUp,
  RightUp2,
  Right,
  RightDown1,
  RightDown,
  RightDown2,
  Down,
  LeftDown1,
  LeftDown,
  LeftDown2,
  Left,
  LeftUp1,
  LeftUp,
  LeftUp2,
  None,
};



// Level elements ..

inline LevelElement operator++( LevelElement & c ) {

  c = static_cast<LevelElement>( static_cast<int8_t>(c) + 1 );
  return c;

}

inline LevelElement operator++( LevelElement & c, int ) {

  LevelElement result = c;
  ++c;
  return result;

}

inline LevelElement operator--( LevelElement & c ) {
 
  c = static_cast<LevelElement>( static_cast<int8_t>(c) - 1 );
  return c;

}

inline LevelElement operator--( LevelElement & c, int ) {

  LevelElement result = c;
  --c;
  return result;

}


// Player stances ..

inline PlayerStance operator++( PlayerStance & c ) {

  c = static_cast<PlayerStance>( static_cast<int8_t>(c) + 1 );
  return c;

}

inline PlayerStance operator++( PlayerStance & c, int ) {

  PlayerStance result = c;
  ++c;
  return result;

}

inline PlayerStance operator--( PlayerStance & c ) {
 
  c = static_cast<PlayerStance>( static_cast<int8_t>(c) - 1 );
  return c;

}

inline PlayerStance operator--( PlayerStance & c, int ) {

  PlayerStance result = c;
  --c;
  return result;

}


// Direction ..   

inline Direction operator++( Direction & c ) {

  c = ( c == Direction::LeftUp2 )
  ? Direction::Up
  : static_cast<Direction>( static_cast<uint8_t>(c) + 1 );
  return c;

}

inline Direction operator++( Direction & c, int ) {

  Direction result = c;
  ++c;
  return result;

}

inline Direction operator--( Direction & c ) {

  c = ( c == Direction::Up )
  ? Direction::LeftUp2
  : static_cast<Direction>( static_cast<uint8_t>(c) - 1 );
  return c;

}

inline Direction operator--( Direction & c, int ) {

  Direction result = c;
  ++c;
  return result;

}


inline bool operator<(const Direction  lhs, const Direction  rhs)  { 

  return (abs((uint8_t)lhs - (uint8_t)rhs) < 8 ? (uint8_t)lhs - (uint8_t)rhs : (uint8_t)lhs - (16 + (uint8_t)rhs)) < 0; 
  
} 

inline bool operator>(const Direction  lhs, const Direction  rhs)  { 
    
  return (abs((uint8_t)lhs - (uint8_t)rhs) < 8 ? (uint8_t)lhs - (uint8_t)rhs : (16 + (uint8_t)lhs) - (uint8_t)rhs) > 0;
 
} 

inline bool operator==(const Direction lhs, const Direction rhs)   { return (uint8_t)lhs == (uint8_t)rhs; }
inline bool operator!=(const Direction lhs, const Direction rhs)   { return !operator == (lhs,rhs); }
inline bool operator<=(const Direction lhs, const Direction rhs)   { return !operator >  (lhs,rhs); }
inline bool operator>=(const Direction lhs, const Direction rhs)   { return !operator <  (lhs,rhs); }


Direction getDirection(int16_t xDiff, int16_t yDiff) {

  if (xDiff > 0) {
  
    if (yDiff > 0) {
    
      if (absT(xDiff) - absT(yDiff) < 0)    { return Direction::RightUp1; }
      if (absT(xDiff) - absT(yDiff) == 0)   { return Direction::RightUp; }
      if (absT(xDiff) - absT(yDiff) > 0)    { return Direction::RightUp2; }
      
    }
    else if (yDiff < 0) {
    
      if (absT(xDiff) - absT(yDiff) > 0)    { return Direction::RightDown1; }
      if (absT(xDiff) - absT(yDiff) == 0)   { return Direction::RightDown; }
      if (absT(xDiff) - absT(yDiff) < 0)    { return Direction::RightDown2; }
    
    }
    else {
    
      return Direction::Right;
      
    }
  
  } 
  else if (xDiff < 0) {
  
    if (yDiff > 0) {
    
      if (absT(xDiff) - absT(yDiff) < 0)    { return Direction::LeftUp1; }
      if (absT(xDiff) - absT(yDiff) == 0)   { return Direction::LeftUp; }
      if (absT(xDiff) - absT(yDiff) > 0)    { return Direction::LeftUp2; }
      
    }
    else if (yDiff < 0) {
    
      if (absT(xDiff) - absT(yDiff) > 0)    { return Direction::LeftDown1; }
      if (absT(xDiff) - absT(yDiff) == 0)   { return Direction::LeftDown; }
      if (absT(xDiff) - absT(yDiff) < 0)    { return Direction::LeftDown2; }
    
    }
    else {
    
      return Direction::Left;
      
    }
  
  }
  else {  
  
    if (yDiff > 0) {
    
      return Direction::Down;
      
    }
    else if (yDiff < 0) {
    
      return Direction::Up;
      
    }
    else {
    
      return Direction::Up;   // Player should be dead !
      
    }
  
  }

  return Direction::Up;       // Default, should never get here!

}

struct Player {

  uint8_t x;
  uint8_t y;
  PlayerStance stance;
  int8_t xDelta;
  int8_t yDelta;

};

struct Enemy {

  uint8_t x;
  uint8_t y;
  PlayerStance stance;
  int8_t xDelta;
  int8_t yDelta;
  bool enabled;

};

struct Level {

  int16_t xOffset;
  int16_t yOffset;
  int8_t xOffsetDelta;
  int8_t yOffsetDelta;

};
