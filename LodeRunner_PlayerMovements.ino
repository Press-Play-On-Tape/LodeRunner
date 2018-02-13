#include "src/utils/Arduboy2Ext.h"
#include "src/utils/Stack.h"
#include <ArduboyTones.h>
#include "Enums.h"
#include "Images.h"

void playerMovements(uint8_t nearestX, uint8_t nearestY, LevelElement nearest, uint8_t currPressed) {

  if(currPressed && A_BUTTON) {
    player.xDelta = 0;
    player.yDelta = 0;
    level.xOffsetDelta = 0;
    level.yOffsetDelta = 0;
  }


  // ------------------------------------------------------------------------------------------
  //  Right
  
  if ( (currPressed & RIGHT_BUTTON) || (!(currPressed & (LEFT_BUTTON | UP_BUTTON | DOWN_BUTTON)) && (player.xDelta == 2 || level.xOffsetDelta == -2)) ) {

    boolean moveRight = true;
    boolean moveDown = false;

    if (inCellX()) {

      if (!inCellY()) {

        nearestY = getNearestY(0) + 1; // Err down a cell
        
      }

    }
    else {

      if (!inCellX()) {

        nearestX = getNearestX(0);
        
      }

    }

    LevelElement right = getLevelData(nearestX + 1, nearestY);
    LevelElement rightDown = getLevelData(nearestX + 1, nearestY + 1);
    LevelElement down = getLevelData(nearestX, nearestY + 1);
 
    if (player.stance == PlayerStance::Falling) {

      if (inCellY() && canBeStoodOn(down)) {

        moveRight = false;
        moveDown = false;
        player.stance = PlayerStance::StandingStill;

      }
      else if (inCellY() && right == LevelElement::Rail && inCellY()) {

        if (player.stance < PlayerStance::Swinging_Right1 || player.stance > PlayerStance::Swinging_Right4) player.stance = PlayerStance::Swinging_Right1;
        moveRight = true;

      }
      else { 
        moveRight = false;
        moveDown = true;

      }     

    }
    else if (canBeStoodOn(down)) {

      switch (right) {

        case LevelElement::Brick:
        case LevelElement::Solid:

          moveRight = false;
          break;

        default:

          if (player.stance < PlayerStance::Running_Right1 || player.stance > PlayerStance::Running_Right4) player.stance = PlayerStance::Running_Right1;
          moveRight = true;
          break;
        
      }

    }
    else if (nearest == LevelElement::Rail && inCellY()) {

      if (canBeOccupied(right)) {

        if (player.stance < PlayerStance::Swinging_Right1 || player.stance > PlayerStance::Swinging_Right4) player.stance = PlayerStance::Swinging_Right1;
        moveRight = true;

      }
      else {

        moveRight = false;

      }
      
    }
    else if (canBeOccupied(right) && canBeFallenOn(rightDown)) {

      if (player.stance < PlayerStance::Swinging_Left4 || player.stance > PlayerStance::Swinging_Left1) player.stance = PlayerStance::Swinging_Left1;
      moveRight = true;
      if (!canBeStoodOn(rightDown)) moveDown = true;

    }
    else {

      moveDown = true;

    }


    // Move player if needed ..

    if (moveRight) {
      
      movePlayerRight();

    }
    else {
          
      player.xDelta = 0;
      level.xOffsetDelta = 0;    

    }

    if (moveDown) {

      player.stance = PlayerStance::Falling;
      movePlayerDown();

    }

  }


  // ------------------------------------------------------------------------------------------
  //  Left
  
  else if ( (currPressed & LEFT_BUTTON) || (!(currPressed & (RIGHT_BUTTON | UP_BUTTON | DOWN_BUTTON)) && (player.xDelta == -2 || level.xOffsetDelta == 2)) ) {
  
    boolean moveLeft = true;
    boolean moveDown = false;

    if (inCellX()) {

      if (!inCellY()) {

        nearestY = getNearestY(0) + 1; // Err down a cell
        
      }

    }
    else {

      if (!inCellX()) {

        nearestX = getNearestX(0) + 1;
        
      }

    }

    LevelElement left = getLevelData(nearestX - 1, nearestY);
    LevelElement leftDown = getLevelData(nearestX - 1, nearestY + 1);
    LevelElement down = getLevelData(nearestX, nearestY + 1);


    if (player.stance == PlayerStance::Falling) {

      if (inCellY() && canBeStoodOn(down)) {

        moveLeft = false;
        moveDown = false;
        player.stance = PlayerStance::StandingStill;

      }
      else if (inCellY() && left == LevelElement::Rail && inCellY()) {

        if (player.stance < PlayerStance::Swinging_Right1 || player.stance > PlayerStance::Swinging_Right4) player.stance = PlayerStance::Swinging_Right1;
        moveLeft = true;

      }
      else { 

        moveLeft = false;
        moveDown = true;

      }

    }
    else if (canBeStoodOn(down)) {

      switch (left) {

        case LevelElement::Brick:
        case LevelElement::Solid:

          moveLeft = false;
          break;

        default:

          if (player.stance < PlayerStance::Running_Left4 || player.stance > PlayerStance::Running_Left1) player.stance = PlayerStance::Running_Left1;
          moveLeft = true;
          break;
        
      }

    }
    else if (nearest == LevelElement::Rail && inCellY()) {

      if (canBeOccupied(left)) {

        if (player.stance < PlayerStance::Swinging_Right1 || player.stance > PlayerStance::Swinging_Right4) player.stance = PlayerStance::Swinging_Right1;
        moveLeft = true;

      }
      else {

        moveLeft = false;

      }
      
    }
    else if (canBeOccupied(left) && canBeFallenOn(leftDown)) {

      if (player.stance < PlayerStance::Swinging_Left4 || player.stance > PlayerStance::Swinging_Left1) player.stance = PlayerStance::Swinging_Left1;
      moveLeft = true;
      if (!canBeStoodOn(leftDown)) moveDown = true;

    }
    else {

      moveDown = true;

    }


    // Move player if needed ..

    if (moveLeft) {

      movePlayerLeft();

    }
    else {

      player.xDelta = 0;
      level.xOffsetDelta = 0;

    }

    if (moveDown) {

      player.stance = PlayerStance::Falling;
      movePlayerDown();

    }

  }


  // ------------------------------------------------------------------------------------------
  //  Up

  else if ( (currPressed & UP_BUTTON) || (!(currPressed & (RIGHT_BUTTON | LEFT_BUTTON | DOWN_BUTTON)) && (player.yDelta == -2 || level.yOffsetDelta == 2)) ) {

    boolean moveUp = true;
    boolean moveDown = true;

    nearestY = getNearestY(+8);
    LevelElement down = getLevelData(nearestX, (inCellY() ? nearestY + 1 : nearestY));

    switch (player.stance) {

      case PlayerStance::Falling:

        moveUp = false;

        if (nearest == LevelElement::Rail && inCellY()) {

          player.stance = PlayerStance::Swinging_Right1;
          moveDown = false;

        }
        else if (canBeStoodOn(down)) {

          moveDown = false;
          player.stance = PlayerStance::StandingStill;
          
        } 

        break;

      case PlayerStance::Climbing_Up1 ... PlayerStance::Climbing_Up2:

        if (inCellY() && nearest != LevelElement::Ladder) {

          moveUp = false;
          moveDown = false;

        }

        break;

      default:

        if (nearest == LevelElement::Ladder) {

          player.x = (nearestX * gridSize) + level.xOffset;
          player.stance = PlayerStance::Climbing_Up1;
          moveUp = true;
          moveDown = false;

        }
        else {

          moveUp = false;
          moveDown = false;

        }

        break;

    }


    // Move player if needed ..

    if (moveUp) {

      movePlayerUp();

    }
    else {

      if (!moveDown) {

        player.yDelta = 0;
        level.yOffsetDelta = 0; 

      }
      else {

        movePlayerDown();

      }

    }

  }


  // ------------------------------------------------------------------------------------------
  //  Down

  else if ( (currPressed & DOWN_BUTTON) || (!(currPressed & (RIGHT_BUTTON | LEFT_BUTTON | UP_BUTTON)) && (player.yDelta == 2 || level.yOffsetDelta == -2)) ) {

    boolean moveDown = true;

    nearestY = getNearestY(+8);
    LevelElement down = getLevelData(nearestX, (inCellY() ? nearestY + 1 : nearestY));

    switch (player.stance) {

      case PlayerStance::Falling:

        if (nearest == LevelElement::Rail && inCellY()) {

          player.stance = PlayerStance::Swinging_Right1;
          moveDown = false;

        }
        else if (canBeStoodOn(down)) {

          moveDown = false;
          player.stance = PlayerStance::StandingStill;
          
        }          

        break;

      default:
      
        if (canBeOccupied(down)) {

          if (down == LevelElement::Blank) player.stance = PlayerStance::Falling;
          moveDown = true;

        }
        else {

          moveDown = false;
          player.stance = PlayerStance::StandingStill;
          
        }
        
        break;

    }


    // Move player if needed ..

    if (moveDown) {

      movePlayerDown();

    }
    else {

      player.yDelta = 0;
      level.yOffsetDelta = 0;   

    }

  }

}


// ------------------------------------------------------------------------------------------
//  Move player or scenery left ..
// ------------------------------------------------------------------------------------------

void movePlayerLeft() {

  player.yDelta = 0;
  level.yOffsetDelta = 0;

  if (player.x > 60) {
    
    player.xDelta = -2;
    level.xOffsetDelta = 0;

  }
  else {

    if (level.xOffset < 0) {

      player.xDelta = 0;
      level.xOffsetDelta = 2;

    }
    else {

      if (player.x > 0) {

        player.xDelta = -2;
        level.xOffsetDelta = 0;

      }

    }

  }

}


// ------------------------------------------------------------------------------------------
//  Move player or scenery right ..
// ------------------------------------------------------------------------------------------

void movePlayerRight() {

  player.yDelta = 0;
  level.yOffsetDelta = 0;

  if (player.x < 60) {

    player.xDelta = 2;
    level.xOffsetDelta = 0;

  }
  else {

    if (level.xOffset > -((width * 2 * gridSize) - WIDTH)) {

      player.xDelta = 0;
      level.xOffsetDelta = -2;

    }
    else {

      if (player.x < 128) {

        player.xDelta = 2;
        level.xOffsetDelta = 0;

      }

    }

  }

}


// ------------------------------------------------------------------------------------------
//  Move player or scenery down ..
// ------------------------------------------------------------------------------------------

void movePlayerDown() {

  player.xDelta = 0;
  level.xOffsetDelta = 0;

  player.yDelta = 2;
  level.yOffsetDelta = 0;


  if (player.y < (HEIGHT_LESS_TOOLBAR / 2) - 5) {

    player.yDelta = 2;
    level.yOffsetDelta = 0;

  }
  else {

    if (level.yOffset > -((height * gridSize) - HEIGHT_LESS_TOOLBAR)) {

      player.yDelta = 0;
      level.yOffsetDelta = -2;

    }
    else {

      if (player.y < HEIGHT_LESS_TOOLBAR) {

        player.yDelta = 2;
        level.yOffsetDelta = 0;

      }

    }

  }

}


// ------------------------------------------------------------------------------------------
//  Move player or scenery up ..
// ------------------------------------------------------------------------------------------

void movePlayerUp() {

  player.xDelta = 0;
  level.xOffsetDelta = 0;

  if (player.y > (HEIGHT_LESS_TOOLBAR / 2) - 5) {
    
    player.yDelta = -2;
    level.yOffsetDelta = 0;

  }
  else {

    if (level.yOffset < 0) {

      player.yDelta = 0;
      level.yOffsetDelta = 2;

    }
    else {

      if (player.y > 0) {

        player.yDelta = -2;
        level.yOffsetDelta = 0;

      }

    }

  }

}