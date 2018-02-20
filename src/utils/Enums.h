#pragma once

#include "Arduboy2Ext.h"
#include "Utils.h"

#define HEIGHT_LESS_TOOLBAR 56
#define NUMBER_OF_ENEMIES 10
#define GRID_SIZE 10

/* ----------------------------------------------------------------------------
 *  A better absolute!
 */
template<typename T> T absT(const T & v) {
  
  return (v < 0) ? -v : v;

}

enum class GameState : uint8_t {

  Intro,
  LevelInit,
  LevelEntry,
  LevelPlay

};

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
  Up          = 0,
  RightUp1    = 1,
  RightUp     = 2,
  RightUp2    = 3,
  Right       = 4,
  RightDown1  = 5,
  RightDown   = 6,
  RightDown2  = 7,
  Down        = 8,
  LeftDown1   = 9,
  LeftDown    = 10,
  LeftDown2   = 11,
  Left        = 12,
  LeftUp1     = 13,
  LeftUp      = 14,
  LeftUp2     = 15,
  None        = 16,
};

enum class EscapeHole : uint8_t {

  None,
  MoveUp1,
  MoveUp2,
  MoveUp3,
  MoveUp4,
  MoveUp5,
  MoveUp6,
  MoveUp7,
  MoveUp8,
  MoveUp9,
  MoveUp10,
  Wiggle1,
  Wiggle2,
  Wiggle3,
  Wiggle4,
  Wiggle5,
  Wiggle6,
  Wiggle7,
  Wiggle8,
  Wait1,
  Wait2,
  Wait3,
  Wait4,
  Wait5,
  Wait6,
  Wait7,
  Wait8,
  Wait9,
  Wait10,
  Wait11,
  Wait12,
  Wait13,
  Wait14,
  Wait15,
  Wait16,
  Wait17,
  Wait18,
  Wait19,
  Wait20,
  Wait21,
  Wait22,
  Wait23,
  Wait24,
  Wait25,
  Wait26,
  Wait27,
  Wait28,
  Wait29,
  Wait30,
  WaitMax

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
  --c;
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


// Escape Hole elements ..

inline EscapeHole operator++( EscapeHole & c ) {

  c = static_cast<EscapeHole>( static_cast<uint8_t>(c) + 1 );
  return c;

}

inline EscapeHole operator++( EscapeHole & c, int ) {

  EscapeHole result = c;
  ++c;
  return result;

}

inline EscapeHole operator--( EscapeHole & c ) {
 
  c = static_cast<EscapeHole>( static_cast<uint8_t>(c) - 1 );
  return c;

}

inline EscapeHole operator--( EscapeHole & c, int ) {

  EscapeHole result = c;
  --c;
  return result;

}

struct Player {

  uint8_t x;
  uint8_t y;
  PlayerStance stance;
  int8_t xDelta;
  int8_t yDelta;

};

struct Enemy {

  uint16_t x;
  uint16_t y;
  PlayerStance stance;
  int8_t xDelta;
  int8_t yDelta;
  EscapeHole escapeHole;
  bool enabled;

};

struct Hole {

  uint8_t x;
  uint8_t y;
  uint8_t countDown;
  
};

struct LevelPoint {

  uint8_t x;
  uint8_t y;
  
};