#pragma once

#include "src/utils/Arduboy2Ext.h"

#define HEIGHT_LESS_TOOLBAR 56

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

};

struct Level {

  int16_t xOffset;
  int16_t yOffset;
  int8_t xOffsetDelta;
  int8_t yOffsetDelta;

};