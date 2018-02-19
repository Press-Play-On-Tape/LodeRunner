#pragma once

#include "Arduboy2Ext.h"
#include "Enums.h"



/* ----------------------------------------------------------------------------
 *  Return the upper 4 bits of a byte.
 */
uint8_t leftValue(uint8_t val) {

  return val >> 4; 
      
}


/* ----------------------------------------------------------------------------
 *  Return the lower 4 bits of a byte.
 */
uint8_t rightValue(uint8_t val) {

  return val & 0x0F; 
      
}


/* ----------------------------------------------------------------------------
 *  Draw a horizontal dotted line. 
 */
void drawHorizontalDottedLine(Arduboy2Ext *arduboy, uint8_t x1, uint8_t x2, uint8_t y) {

  for (uint8_t x3 = x1; x3 <= x2; x3+=2) {
    arduboy->drawPixel(x3, y, WHITE);
  }
  
}




// ---------------------------------------------------------------------------------
// Can be stood on by the player ?
//
// The player cannot stand on brick that has been dug out or is repairing itself.
//
boolean canBeStoodOn(LevelElement levelElement, Enemy *enemies, uint16_t positionX, uint16_t positionY) {

  switch (levelElement) {

    case LevelElement::Brick:
    case LevelElement::Solid:
    case LevelElement::Ladder:
    case LevelElement::LadderLevel:
      return true;

    case LevelElement::Brick_1:
    case LevelElement::Brick_2:
    case LevelElement::Brick_3:
    case LevelElement::Brick_4:
    case LevelElement::Brick_Transition:
    case LevelElement::Brick_Close_1:
    case LevelElement::Brick_Close_2:
    case LevelElement::Brick_Close_3:
    case LevelElement::Brick_Close_4:

      for (uint8_t x = 0; x < NUMBER_OF_ENEMIES; x++) {

        Enemy *enemy = &enemies[x];

        if (enemy->enabled) {

          if (enemy->stance == PlayerStance::Falling && enemy->x == positionX * GRID_SIZE && enemy->y == positionY * GRID_SIZE) {

            return true; 

          }

        }

      }

      return false;

    default:
      return false;

  }

}


// ---------------------------------------------------------------------------------
// Can the player fall onto these elements ?
//
// Elements should be the same as the 'canBeStoodOn' with the addition of the rail.
//
boolean canBeFallenOn(LevelElement levelElement) {

  switch (levelElement) {

    case LevelElement::Brick:
    case LevelElement::Solid:
    case LevelElement::Rail:
    case LevelElement::Ladder:
    case LevelElement::LadderLevel:
      return true;

    default:
      return false;

  }

}


// ---------------------------------------------------------------------------------
// Can the space be occupied by the player ?
//
// Can the player enter the square - ie. is it empty or something that can be climbed on?
//
boolean canBeOccupied(LevelElement levelElement) {

  switch (levelElement) {

    case LevelElement::Blank:
    case LevelElement::Ladder:
    case LevelElement::Rail:
    case LevelElement::LadderLevel:
    case LevelElement::Gold:
    case LevelElement::Brick_1 ... LevelElement::Brick_Close_4:
      return true;

    default:
      return false;

  }

}


// ---------------------------------------------------------------------------------
// Can the space be fallen into by the player ?
//
boolean canBeFallenInto(LevelElement levelElement, Enemy *enemies, uint16_t positionX, uint16_t positionY) {

  switch (levelElement) {

    case LevelElement::Blank:
      return true;

    case LevelElement::Brick_1:
    case LevelElement::Brick_2:
    case LevelElement::Brick_3:
    case LevelElement::Brick_4:
    case LevelElement::Brick_Transition:
    case LevelElement::Brick_Close_1:
    case LevelElement::Brick_Close_2:
    case LevelElement::Brick_Close_3:
    case LevelElement::Brick_Close_4:

      for (uint8_t x = 0; x < NUMBER_OF_ENEMIES; x++) {

        Enemy *enemy = &enemies[x];

        if (enemy->enabled) {

          if (enemy->stance == PlayerStance::Falling && enemy->x == positionX * GRID_SIZE && enemy->y == positionY * GRID_SIZE) {

            return false; 

          }

        }

      }

      return true;

    default:
      return false;

  }

}


// ---------------------------------------------------------------------------------
// Can be stood on by the enemy ?
//
// The enemy can stand on bricks that have been dug our or are reforming.  Of 
// course they will fall into these if they do step on them.
//
boolean canBeStoodOn_Enemy(LevelElement levelElement) {

  switch (levelElement) {

    case LevelElement::Brick:
    case LevelElement::Solid:
    case LevelElement::Ladder:
    case LevelElement::LadderLevel:
    case LevelElement::Brick_1:
    case LevelElement::Brick_2:
    case LevelElement::Brick_3:
    case LevelElement::Brick_4:
    case LevelElement::Brick_Transition:
    case LevelElement::Brick_Close_1:
    case LevelElement::Brick_Close_2:
    case LevelElement::Brick_Close_3:
    case LevelElement::Brick_Close_4:
      return true;

    default:
      return false;

  }

}


// ---------------------------------------------------------------------------------
// Can the space be occupied by the enemy ?
//
// Can the player enter the square - ie. is it empty or something that can be climbed on?
//
boolean canBeOccupied_Enemy(LevelElement levelElement) {

  switch (levelElement) {

    case LevelElement::Blank:
    case LevelElement::Ladder:
    case LevelElement::Rail:
    case LevelElement::LadderLevel:
    case LevelElement::Gold:
    case LevelElement::Brick_1:
    case LevelElement::Brick_2:
    case LevelElement::Brick_3:
    case LevelElement::Brick_4:
    case LevelElement::Brick_Transition:
    case LevelElement::Brick_Close_1:
    case LevelElement::Brick_Close_2:
    case LevelElement::Brick_Close_3:
    case LevelElement::Brick_Close_4:
      return true;

    default:
      return false;

  }

}


// ---------------------------------------------------------------------------------
// Can the space be fallen into by the enemy ?
//
boolean canBeFallenInto_Enemy(LevelElement levelElement, Enemy *enemies, uint16_t positionX, uint16_t positionY) {

  switch (levelElement) {

    case LevelElement::Blank:
      return true;

    case LevelElement::Brick_1:
    case LevelElement::Brick_2:
    case LevelElement::Brick_3:
    case LevelElement::Brick_4:
    case LevelElement::Brick_Transition:
    case LevelElement::Brick_Close_1:
    case LevelElement::Brick_Close_2:
    case LevelElement::Brick_Close_3:
    case LevelElement::Brick_Close_4:

      for (uint8_t x = 0; x < NUMBER_OF_ENEMIES; x++) {

        Enemy *enemy = &enemies[x];

        if (enemy->enabled) {

          if (enemy->stance == PlayerStance::Falling && enemy->x == positionX * GRID_SIZE && enemy->y == positionY * GRID_SIZE) {

            return false; 

          }

        }

      }

      return true;

    default:
      return false;

  }

}