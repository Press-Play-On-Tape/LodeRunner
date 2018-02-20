#include "src/utils/Arduboy2Ext.h"
#include <ArduboyTones.h>


void playerMovements(uint8_t nearestX, uint8_t nearestY, LevelElement nearest) {


  if (arduboy.justPressed(A_BUTTON) && !arduboy.justPressed(B_BUTTON)) {

    if (inCellX(2) && inCellY()) {

      nearestX = getNearestX(2);
      LevelElement leftDown = level.getLevelData(nearestX - 1, nearestY + 1);

      if (leftDown == LevelElement::Brick) {
 
        player.x = (nearestX * GRID_SIZE) + level.getXOffset();
        player.stance = PlayerStance::Burn_Left;
        player.xDelta = 0;
        level.setXOffsetDelta(0);

        level.setLevelData(nearestX - 1, nearestY + 1, LevelElement::Brick_1);
        Hole hole = {static_cast<uint8_t>(nearestX - 1), static_cast<uint8_t>(nearestY + 1), 100};
        holes.enqueue(hole);

        arduboy.pollButtons();
        return;

      }

    }

  } 


  else if (arduboy.justPressed(B_BUTTON) && !arduboy.justPressed(A_BUTTON)) {

    if (inCellX(2) && inCellY()) {

      nearestX = getNearestX(2);
      LevelElement rightDown = level.getLevelData(nearestX + 1, nearestY + 1);

      if (rightDown == LevelElement::Brick) {
 
        player.x = (nearestX * GRID_SIZE) + level.getXOffset();
        player.stance = PlayerStance::Burn_Right;
        player.xDelta = 0;
        level.setXOffsetDelta(0);

        level.setLevelData(nearestX + 1, nearestY + 1, LevelElement::Brick_1);
        Hole hole = {static_cast<uint8_t>(nearestX + 1), static_cast<uint8_t>(nearestY + 1), 100};
        holes.enqueue(hole);

        arduboy.pollButtons();
        return;

      }

    }

  }


  // ------------------------------------------------------------------------------------------
  //  Right
  
  if ( arduboy.justPressed(RIGHT_BUTTON) || ((!arduboy.justPressed(LEFT_BUTTON) && !arduboy.justPressed(UP_BUTTON) && !arduboy.justPressed(DOWN_BUTTON)) && (player.xDelta == 2 || level.getXOffsetDelta() == -2)) ) {

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

    LevelElement right = level.getLevelData(nearestX + 1, nearestY);
    LevelElement rightDown = level.getLevelData(nearestX + 1, nearestY + 1);
    LevelElement down = level.getLevelData(nearestX, nearestY + 1);
 

    if (player.stance == PlayerStance::Falling) {

      if (inCellY() && canBeStoodOn(down, enemies, nearestX, nearestY + 1)) {

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
    else if (player.stance >= PlayerStance::Running_Right1 && player.stance <= PlayerStance::Running_Right4 && canBeFallenInto(down, enemies, nearestX, nearestY + 1) && right != LevelElement::Rail) {

        moveRight = false;
        moveDown = true;

    }
    else if (canBeStoodOn(down, enemies, nearestX, nearestY + 1)) {

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

//       switch (right) {

//         case LevelElement::Blank:
//           player.stance = PlayerStance::Falling;
//           break;

//         default:
//           if (player.stance < PlayerStance::Swinging_Right1 || player.stance > PlayerStance::Swinging_Right4) player.stance = PlayerStance::Swinging_Right1;
//           break;

//       }

      moveRight = true;
      if (!canBeStoodOn(rightDown, enemies, nearestX, nearestY + 1)) moveDown = true;

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
      level.setXOffsetDelta(0);    

    }

    if (moveDown) {

      player.stance = PlayerStance::Falling;
      movePlayerDown();

    }

  }


  // ------------------------------------------------------------------------------------------
  //  Left
  
  else if ( arduboy.justPressed(LEFT_BUTTON) || ((!arduboy.justPressed(RIGHT_BUTTON) && !arduboy.justPressed(UP_BUTTON) && !arduboy.justPressed(DOWN_BUTTON)) && (player.xDelta == -2 || level.getXOffsetDelta() == 2)) ) {

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

    LevelElement left = level.getLevelData(nearestX - 1, nearestY);
    LevelElement leftDown = level.getLevelData(nearestX - 1, nearestY + 1);
    LevelElement down = level.getLevelData(nearestX, nearestY + 1);

    if (player.stance == PlayerStance::Falling) {

      if (inCellY() && canBeStoodOn(down, enemies, nearestX, nearestY + 1)) {

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
    else if (player.stance >= PlayerStance::Running_Left4 && player.stance <= PlayerStance::Running_Left1 && canBeFallenInto(down, enemies, nearestX, nearestY + 1) && left != LevelElement::Rail) {

        moveLeft = false;
        moveDown = true;

    }
    else if (canBeStoodOn(down, enemies, nearestX, nearestY + 1)) {

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

      // switch (left) {

      //   case LevelElement::Blank:
      //     player.stance = PlayerStance::Falling;
      //     break;

      //   default:
      //     if (player.stance < PlayerStance::Swinging_Left4 || player.stance > PlayerStance::Swinging_Left1) player.stance = PlayerStance::Swinging_Left1;
      //     break;

      // }

      moveLeft = true;
      if (!canBeStoodOn(leftDown, enemies, nearestX, nearestY + 1)) moveDown = true;

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
      level.setXOffsetDelta(0);

    }

    if (moveDown) {

      player.stance = PlayerStance::Falling;
      movePlayerDown();

    }

  }


  // ------------------------------------------------------------------------------------------
  //  Up

  else if ( arduboy.justPressed(UP_BUTTON) || ((!arduboy.justPressed(RIGHT_BUTTON) && !arduboy.justPressed(LEFT_BUTTON) && !arduboy.justPressed(DOWN_BUTTON)) && (player.yDelta == -2 || level.getYOffsetDelta() == 2)) ) {

    boolean moveUp = true;
    boolean moveDown = true;

    nearestY = getNearestY(+8);
    LevelElement down = level.getLevelData(nearestX, (inCellY() ? nearestY + 1 : nearestY));

    switch (player.stance) {

      case PlayerStance::Falling:

        moveUp = false;

        if (nearest == LevelElement::Rail && inCellY()) {

          player.stance = PlayerStance::Swinging_Right1;
          moveDown = false;

        }
        else if (canBeStoodOn(down, enemies, nearestX, nearestY + 1)) {

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

          player.x = (nearestX * GRID_SIZE) + level.getXOffset();
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
        level.setYOffsetDelta(0); 
        player.xDelta = 0;          // Added to stop the player ..
        level.setXOffsetDelta(0); 

      }
      else {

        movePlayerDown();

      }

    }

  }


  // ------------------------------------------------------------------------------------------
  //  Down

  else if ( arduboy.justPressed(DOWN_BUTTON) || ((!arduboy.justPressed(RIGHT_BUTTON) && !arduboy.justPressed(LEFT_BUTTON) && !arduboy.justPressed(UP_BUTTON)) && (player.yDelta == 2 || level.getYOffsetDelta() == -2)) ) {

    boolean moveDown = true;

    nearestY = getNearestY(+8);
    LevelElement down = level.getLevelData(nearestX, (inCellY() ? nearestY + 1 : nearestY));

    switch (player.stance) {

      case PlayerStance::Falling:

        if (nearest == LevelElement::Rail && inCellY()) {

          player.stance = PlayerStance::Swinging_Right1;
          moveDown = false;

        }
        else if (canBeStoodOn(down, enemies, nearestX, nearestY + 1)) {

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

      player.xDelta = 0;           // Added to stop the player ..
      level.setXOffsetDelta(0);   
      player.yDelta = 0;
      level.setYOffsetDelta(0);   

    }

  }

}


// ------------------------------------------------------------------------------------------
//  Move player or scenery left ..
// ------------------------------------------------------------------------------------------

void movePlayerLeft() {

  player.yDelta = 0;
  level.setYOffsetDelta(0);

  if (player.x > 60) {
    
    player.xDelta = -2;
    level.setXOffsetDelta(0);

  }
  else {

    if (level.getXOffset() < 0) {

      player.xDelta = 0;
      level.setXOffsetDelta(2);

    }
    else {

      if (player.x > 0) {

        player.xDelta = -2;
        level.setXOffsetDelta(0);

      }

    }

  }

}


// ------------------------------------------------------------------------------------------
//  Move player or scenery right ..
// ------------------------------------------------------------------------------------------

void movePlayerRight() {

  player.yDelta = 0;
  level.setYOffsetDelta(0);

  if (player.x < 60) {

    player.xDelta = 2;
    level.setXOffsetDelta(0);

  }
  else {

    if (level.getXOffset() > -((level.getWidth() * 2 * GRID_SIZE) - WIDTH)) {

      player.xDelta = 0;
      level.setXOffsetDelta(-2);

    }
    else {

      if (player.x < 128) {

        player.xDelta = 2;
        level.setXOffsetDelta(0);

      }

    }

  }

}


// ------------------------------------------------------------------------------------------
//  Move player or scenery down ..
// ------------------------------------------------------------------------------------------

void movePlayerDown() {

  player.xDelta = 0;
  level.setXOffsetDelta(0);

  player.yDelta = 2;
  level.setYOffsetDelta(0);


  if (player.y < (HEIGHT_LESS_TOOLBAR / 2) - 5) {

    player.yDelta = 2;
    level.setYOffsetDelta(0);

  }
  else {

    if (level.getYOffset() > -((level.getHeight() * GRID_SIZE) - HEIGHT_LESS_TOOLBAR)) {

      player.yDelta = 0;
      level.setYOffsetDelta(-2);

    }
    else {

      if (player.y < HEIGHT_LESS_TOOLBAR) {

        player.yDelta = 2;
        level.setYOffsetDelta(0);

      }

    }

  }

}


// ------------------------------------------------------------------------------------------
//  Move player or scenery up ..
// ------------------------------------------------------------------------------------------

void movePlayerUp() {

  player.xDelta = 0;
  level.setXOffsetDelta(0);

  if (player.y > (HEIGHT_LESS_TOOLBAR / 2) - 5) {
    
    player.yDelta = -2;
    level.setYOffsetDelta(0);

  }
  else {

    if (level.getYOffset() < 0) {

      player.yDelta = 0;
      level.setYOffsetDelta(2);

    }
    else {

      if (player.y > 0) {

        player.yDelta = -2;
        level.setYOffsetDelta(0);

      }

    }

  }

}