#include "src/utils/Arduboy2Ext.h"
#include "src/utils/Stack.h"
#include <ArduboyTones.h>
#include "Enums.h"
#include "Images.h"

void playerMovements(uint8_t nearestX, uint8_t nearestY, LevelElement nearest, uint8_t currPressed) {


  // ------------------------------------------------------------------------------------------
  //  Right
  
  if ( (currPressed & RIGHT_BUTTON) || (!(currPressed & (LEFT_BUTTON | UP_BUTTON | DOWN_BUTTON)) && (player.xDelta == 2 || level.xOffsetDelta == -2)) ) {

    boolean moveRight = true;
    boolean moveDown = false;

    LevelElement right = getLevelData(((player.x - level.xOffset) % gridSize != 0 ? nearestX : nearestX + 1), nearestY);
    LevelElement rightDown = getLevelData(((player.x - level.xOffset) % gridSize != 0 ? nearestX : nearestX + 1), ((player.y - level.yOffset) % gridSize == 0 ? nearestY + 1 : nearestY));
    nearestX = getNearestX(0);
    LevelElement down = getLevelData(nearestX, ((player.y - level.yOffset) % gridSize == 0 ? nearestY + 1 : nearestY));
  
//  arduboy.setCursor(0,10);
//  arduboy.print((int8_t)right);
//  arduboy.print(" ");
//  arduboy.print((int8_t)rightDown);
//  arduboy.print(" ");
//  arduboy.print((int8_t)down);
//  arduboy.print(" ");
//  arduboy.print((int8_t)nearest);
//  arduboy.print(" ");
// arduboy.setCursor(0,20);
//  arduboy.print(nearestX );
//  arduboy.print(" ");
//  arduboy.print(((player.x - level.xOffset) % gridSize != 0 ? nearestX : nearestX + 1));
//  arduboy.print(" ");
//  arduboy.print(nearestY);
//  arduboy.print(" ");
 
    if (canBeStoodOn(down)) {

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
    else if (nearest == LevelElement::Rail && inCell(player.y - level.yOffset)) {

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
      
    LevelElement left = getLevelData(((player.x - level.xOffset) % gridSize != 0 ? nearestX : nearestX - 1), nearestY);
    LevelElement leftDown = getLevelData(((player.x - level.xOffset) % gridSize != 0 ? nearestX : nearestX - 1), ((player.y - level.yOffset) % gridSize == 0 ? nearestY + 1 : nearestY));
    nearestX = getNearestX(8);
    LevelElement down = getLevelData(nearestX, ((player.y - level.yOffset) % gridSize == 0 ? nearestY + 1 : nearestY));

 arduboy.setCursor(0,10);
 arduboy.print((int8_t)left);
 arduboy.print(" ");
 arduboy.print((int8_t)leftDown);
 arduboy.print(" ");
 arduboy.print((int8_t)down);
 arduboy.print(" ");
 arduboy.print((int8_t)nearest);
 arduboy.print(" ");


    if (canBeStoodOn(down)) {

      switch (left) {

        case LevelElement::Brick:
        case LevelElement::Solid:
          moveLeft = false;
  arduboy.print("A");
          break;

        default:
          if (player.stance < PlayerStance::Running_Left4 || player.stance > PlayerStance::Running_Left1) player.stance = PlayerStance::Running_Left1;
          moveLeft = true;
  arduboy.print("B");
          break;
        
      }

    }
    else if (nearest == LevelElement::Rail && inCell(player.y - level.yOffset)) {

      if (canBeOccupied(left)) {
        if (player.stance < PlayerStance::Swinging_Right1 || player.stance > PlayerStance::Swinging_Right4) player.stance = PlayerStance::Swinging_Right1;
        moveLeft = true;
  arduboy.print("C");

      }
      else {
        moveLeft = false;
  arduboy.print("D");
      }
      
    }
    else if (canBeOccupied(left) && canBeFallenOn(leftDown)) {

      if (player.stance < PlayerStance::Swinging_Left4 || player.stance > PlayerStance::Swinging_Left1) player.stance = PlayerStance::Swinging_Left1;
      moveLeft = true;
      if (!canBeStoodOn(leftDown)) moveDown = true;
  arduboy.print("E");

    }
    else {

  arduboy.print("F");
      moveDown = true;

    }


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

    switch (player.stance) {

      case PlayerStance::Climbing_Up1 ... PlayerStance::Climbing_Up2:

        if ((player.y - level.yOffset) % gridSize == 0 && nearest != LevelElement::Ladder) {
// arduboy.setCursor(20,10);
// arduboy.print("c");
          
          // player.yDelta = 0;
          // level.yOffsetDelta = 0;
          moveUp = false;

        }

        break;

      default:

        if (nearest == LevelElement::Ladder) {
//arduboy.setCursor(20,10);
//arduboy.print("a");

          player.x = (nearestX * gridSize) + level.xOffset;
          // player.xDelta = 0;
          // player.yDelta = -2;
          player.stance = PlayerStance::Climbing_Up1;
          moveUp = true;

        }
        else {
//arduboy.setCursor(20,10);
//arduboy.print("x");
          // player.xDelta = 0;
          // level.xOffsetDelta = 0;
          // player.yDelta = 0;
          // level.yOffsetDelta = 0;
          moveUp = false;

        }

        break;

    }

    if (moveUp) {

      movePlayerUp();

    }
    else {

      player.yDelta = 0;
      level.yOffsetDelta = 0; 

    }

  }


  // ------------------------------------------------------------------------------------------
  //  Down

  else if ( (currPressed & DOWN_BUTTON) || (!(currPressed & (RIGHT_BUTTON | LEFT_BUTTON | UP_BUTTON)) && (player.yDelta == 2 || level.yOffsetDelta == -2)) ) {

    boolean moveDown = true;

    nearestY = getNearestY(+8);
    LevelElement down = getLevelData(nearestX, (inCell(player.y - level.yOffset) ? nearestY + 1 : nearestY));
// arduboy.setCursor(0,10);
// arduboy.print((int8_t)down);
// arduboy.print(" ");
// arduboy.print(nearestX);
// arduboy.print(" ");
// arduboy.print(nearestY);
// arduboy.print("    ");
// arduboy.print(((player.y - level.yOffset) % gridSize == 0 ? nearestY + 1 : nearestY));
// arduboy.setCursor(0,20);
// arduboy.print((int8_t)player.stance);
    switch (player.stance) {

      case PlayerStance::Falling:

        if (nearest == LevelElement::Rail && inCell(player.y - level.yOffset)) {

          player.stance = PlayerStance::Swinging_Right1;
          moveDown = false;
// arduboy.print("A");

        }
        else if (canBeStoodOn(down)) {

          moveDown = false;
// arduboy.print("B");
          
        }          

        break;

      default:
      
        if (canBeOccupied(down)) {

          moveDown = true;
// arduboy.print("C");

        }
        else {

          moveDown = false;
// arduboy.print("D");
          
        }
        
        break;

    }

    if (moveDown) {

      movePlayerDown();

    }
    else {

      player.yDelta = 0;
      level.yOffsetDelta = 0;   

    }
// arduboy.print(" ");
// arduboy.print(player.yDelta);
// arduboy.print(" ");
// arduboy.print(level.yOffsetDelta);

  }

}


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

void movePlayerUp() {
// arduboy.setCursor(0,10);
// arduboy.print("up");
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