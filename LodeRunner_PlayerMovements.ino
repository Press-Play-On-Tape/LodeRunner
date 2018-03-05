#include "src/utils/Arduboy2Ext.h"
#include <ArduboyTones.h>

void stopPlayer() {

  player.setXDelta(0);
  level.setXOffsetDelta(0);   
  player.setYDelta(0);
  level.setYOffsetDelta(0); 

}

void playerMovements(uint8_t nearestX, uint8_t nearestY, LevelElement nearest) {


  // Check to see if we have touched gold!

  if (level.getLevelData(nearestX, nearestY) == LevelElement::Gold) {

    player.setScore(player.getScore() + 25);
    level.setLevelData(nearestX, nearestY, LevelElement::Blank);
    level.pickupGold();

  }


  // Burn to the left .. 

  if (arduboy.justPressed(A_BUTTON) && !arduboy.justPressed(B_BUTTON)) {

    if (inCellY()) {

      nearestX = getNearestX(2);
      LevelElement leftDown = level.getLevelData(nearestX - 1, nearestY + 1);

      if (leftDown == LevelElement::Brick) {

//        player.setX((nearestX * GRID_SIZE) + level.getXOffset());
        player.setStance(PlayerStance::Burn_Left);
        player.setXDelta(0);
        level.setXOffsetDelta(0);

        level.setLevelData(nearestX - 1, nearestY + 1, LevelElement::Brick_1);
        Hole hole = {static_cast<uint8_t>(nearestX - 1), static_cast<uint8_t>(nearestY + 1), 100};
        holes.enqueue(hole);

        arduboy.pollButtons();
        return;

      }

    }

  } 


  // Burn to the right .. 

  else if (arduboy.justPressed(B_BUTTON) && !arduboy.justPressed(A_BUTTON)) {

    if (inCellY()) {

      nearestX = getNearestX(2);
      LevelElement rightDown = level.getLevelData(nearestX + 1, nearestY + 1);

      if (rightDown == LevelElement::Brick) {
 
//        player.setX((nearestX * GRID_SIZE) + level.getXOffset());
        player.setStance(PlayerStance::Burn_Right);
        player.setXDelta(0);
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
  
  if ( arduboy.justPressed(RIGHT_BUTTON) || ((!arduboy.justPressed(LEFT_BUTTON) && !arduboy.justPressed(UP_BUTTON) && !arduboy.justPressed(DOWN_BUTTON)) && (player.getXDelta() == 2 || level.getXOffsetDelta() == -2)) ) {

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

    if (player.getStance() == PlayerStance::Falling) {

      if (inCellY() && canBeStoodOn(down, enemies, nearestX, nearestY + 1)) {

        moveRight = false;
        moveDown = false;
        player.setStance(PlayerStance::StandingStill);

      }
      
      else if (inCellY() && right == LevelElement::Rail && inCellY()) {

        if (player.getStance() < PlayerStance::Swinging_Right1 || player.getStance() > PlayerStance::Swinging_Right4) player.setStance(PlayerStance::Swinging_Right1);
        moveRight = true;

      }

      else { 

        moveRight = false;
        moveDown = true;

      }     

    }
    else if (player.getStance() >= PlayerStance::Running_Right1 && player.getStance() <= PlayerStance::Running_Right4 && canBeFallenInto(down, enemies, nearestX, nearestY + 1) && right != LevelElement::Rail) {

        moveRight = false;
        moveDown = true;

    }
    else if (canBeStoodOn(down, enemies, nearestX, nearestY + 1)) {

      switch (right) {

        case LevelElement::Brick:
        case LevelElement::Solid:
        case LevelElement::FallThrough:

          moveRight = false;
          break;

        default:

          if (player.getStance() < PlayerStance::Running_Right1 || player.getStance() > PlayerStance::Running_Right4) player.setStance(PlayerStance::Running_Right1);
          moveRight = true;
          break;
      
      }

    }
    else if (nearest == LevelElement::Rail || nearest == LevelElement::Ladder) {

      if (canBeOccupied(right)) {

        if (player.getStance() < PlayerStance::Swinging_Right1 || player.getStance() > PlayerStance::Swinging_Right4) player.setStance(PlayerStance::Swinging_Right1);
        moveRight = true;

      }
      else {

        moveRight = false;

      }
    
    }
    else if (canBeOccupied(right) && canBeFallenOn(rightDown)) {

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
          
      player.setXDelta(0);
      level.setXOffsetDelta(0);    

    }

    if (moveDown) {

      player.setStance(PlayerStance::Falling);
      movePlayerDown();

    }

  }


  // ------------------------------------------------------------------------------------------
  //  Left
  
  else if ( arduboy.justPressed(LEFT_BUTTON) || ((!arduboy.justPressed(RIGHT_BUTTON) && !arduboy.justPressed(UP_BUTTON) && !arduboy.justPressed(DOWN_BUTTON)) && (player.getXDelta() == -2 || level.getXOffsetDelta() == 2)) ) {

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

    if (player.getStance() == PlayerStance::Falling) {

      if (inCellY() && canBeStoodOn(down, enemies, nearestX, nearestY + 1)) {

        moveLeft = false;
        moveDown = false;
        player.setStance(PlayerStance::StandingStill);

      }
      else if (inCellY() && left == LevelElement::Rail && inCellY()) {

        if (player.getStance() < PlayerStance::Swinging_Right1 || player.getStance() > PlayerStance::Swinging_Right4) player.setStance(PlayerStance::Swinging_Right1);
        moveLeft = true;

      }
      else { 

        moveLeft = false;
        moveDown = true;

      }

    }
    else if (player.getStance() >= PlayerStance::Running_Left4 && player.getStance() <= PlayerStance::Running_Left1 && canBeFallenInto(down, enemies, nearestX, nearestY + 1) && left != LevelElement::Rail) {

        moveLeft = false;
        moveDown = true;

    }
    else if (canBeStoodOn(down, enemies, nearestX, nearestY + 1)) {

      switch (left) {

        case LevelElement::Brick:
        case LevelElement::FallThrough:
        case LevelElement::Solid:

          moveLeft = false;
          break;

        default:

          if (player.getStance() < PlayerStance::Running_Left4 || player.getStance() > PlayerStance::Running_Left1) player.setStance(PlayerStance::Running_Left1);
          moveLeft = true;
          break;
        
      }

    }
    else if (nearest == LevelElement::Rail || nearest == LevelElement::Ladder) {

      if (canBeOccupied(left)) {

        if (player.getStance() < PlayerStance::Swinging_Right1 || player.getStance() > PlayerStance::Swinging_Right4) player.setStance(PlayerStance::Swinging_Right1);
        moveLeft = true;

      }
      else {

        moveLeft = false;

      }
      
    }
    else if (canBeOccupied(left) && canBeFallenOn(leftDown)) {

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

      player.setXDelta(0);
      level.setXOffsetDelta(0);

    }

    if (moveDown) {

      player.setStance(PlayerStance::Falling);
      movePlayerDown();

    }

  }


  // ------------------------------------------------------------------------------------------
  //  Up

  else if ( arduboy.justPressed(UP_BUTTON) || ((!arduboy.justPressed(RIGHT_BUTTON) && !arduboy.justPressed(LEFT_BUTTON) && !arduboy.justPressed(DOWN_BUTTON)) && (player.getYDelta() == -2 || level.getYOffsetDelta() == 2)) ) {

    boolean moveUp = true;
    boolean moveDown = true;

    nearestY = getNearestY(+8);
    LevelElement up = level.getLevelData(nearestX, (inCellY() ? nearestY - 1 : nearestY));
    LevelElement down = level.getLevelData(nearestX, (inCellY() ? nearestY + 1 : nearestY));


    switch (player.getStance()) {

      case PlayerStance::Falling:

        moveUp = false;

        if (nearest == LevelElement::Rail && inCellY()) {

          player.setStance(PlayerStance::Swinging_Right1);
          moveDown = false;

        }
        else if (canBeStoodOn(down, enemies, nearestX, nearestY + 1)) {

          moveDown = false;
          player.setStance(PlayerStance::StandingStill);
          
        } 

        break;

      case PlayerStance::Climbing_Up1 ... PlayerStance::Climbing_Up2:

        if (inCellY() && (nearest != LevelElement::Ladder || isSolid(up))) { 

          moveUp = false;
          moveDown = false;

        }

        break;

      default:

        if (nearest == LevelElement::Ladder) {

          player.setX((nearestX * GRID_SIZE) + level.getXOffset());
          player.setStance(PlayerStance::Climbing_Up1);
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

        stopPlayer();

      }
      else {

        movePlayerDown();

      }

    }

  }


  // ------------------------------------------------------------------------------------------
  //  Down

  else if ( arduboy.justPressed(DOWN_BUTTON) || ((!arduboy.justPressed(RIGHT_BUTTON) && !arduboy.justPressed(LEFT_BUTTON) && !arduboy.justPressed(UP_BUTTON)) && (player.getYDelta() == 2 || level.getYOffsetDelta() == -2)) ) {

    boolean moveDown = true;

    nearestY = getNearestY(+8);
    LevelElement current = level.getLevelData(nearestX, (inCellY() ? nearestY : nearestY - 1));
    LevelElement down = level.getLevelData(nearestX, (inCellY() ? nearestY + 1 : nearestY));

    switch (player.getStance()) {

      case PlayerStance::Falling:

        if (nearest == LevelElement::Rail && inCellY()) {

          player.setStance(PlayerStance::Swinging_Right1);
          moveDown = false;

        }

        else if (inCellY() && current >= LevelElement::Brick_Close_1 && current <= LevelElement::Brick_Close_4) {

          moveDown = false;

        }

        else if (canBeStoodOn(down, enemies, nearestX, nearestY + 1)) {

          moveDown = false;
          player.setStance(PlayerStance::StandingStill);

        }          

        break;

      default:

        if (down == LevelElement::Ladder) {

          player.setX((nearestX * GRID_SIZE) + level.getXOffset());
          if (player.getStance() < PlayerStance::Climbing_Down2 || player.getStance() > PlayerStance::Climbing_Down1) player.setStance(PlayerStance::Climbing_Down1);
          moveDown = true;

        }
        else if (canBeOccupied(down)) {

          if (down == LevelElement::Blank) player.setStance(PlayerStance::Falling);
          player.setX((nearestX * GRID_SIZE) + level.getXOffset());
          moveDown = true;

        }
        else {

          moveDown = false;
          player.setStance(PlayerStance::StandingStill);
          
        }
        
        break;

    }


    // Move player if needed ..

    if (moveDown) {

      movePlayerDown();

    }
    else {

      stopPlayer();

    }

  }

}


// ------------------------------------------------------------------------------------------
//  Move player or scenery left ..
// ------------------------------------------------------------------------------------------

void movePlayerLeft() {

  player.setYDelta(0);
  level.setYOffsetDelta(0);

  if (player.getX() > 60) {
    
    player.setXDelta(-2);
    level.setXOffsetDelta(0);

  }
  else {

    if (level.getXOffset() < 0) {

      player.setXDelta(0);
      level.setXOffsetDelta(2);

    }
    else {

      if (player.getX() > 0) {

        player.setXDelta(-2);
        level.setXOffsetDelta(0);

      }

    }

  }

}


// ------------------------------------------------------------------------------------------
//  Move player or scenery right ..
// ------------------------------------------------------------------------------------------

void movePlayerRight() {

  player.setYDelta(0);
  level.setYOffsetDelta(0);

  if (player.getX() < 60) {

    player.setXDelta(2);
    level.setXOffsetDelta(0);

  }
  else {

    if (level.getXOffset() > -((level.getWidth() * 2 * GRID_SIZE) - WIDTH)) {

      player.setXDelta(0);
      level.setXOffsetDelta(-2);

    }
    else {

      if (player.getX() < 128) {

        player.setXDelta(2);
        level.setXOffsetDelta(0);

      }

    }

  }

}


// ------------------------------------------------------------------------------------------
//  Move player or scenery down ..
// ------------------------------------------------------------------------------------------

void movePlayerDown() {

  player.setXDelta(0);
  level.setXOffsetDelta(0);

  player.setYDelta(2);
  level.setYOffsetDelta(0);


  if (player.getY() < (HEIGHT_LESS_TOOLBAR / 2) - 5) {

    player.setYDelta(2);
    level.setYOffsetDelta(0);

  }
  else {

    if (level.getYOffset() > -((level.getHeight() * GRID_SIZE) - HEIGHT_LESS_TOOLBAR)) {

      player.setYDelta(0);
      level.setYOffsetDelta(-2);

    }
    else {

      if (player.getY() < HEIGHT_LESS_TOOLBAR) {

        player.setYDelta(2);
        level.setYOffsetDelta(0);

      }

    }

  }

}


// ------------------------------------------------------------------------------------------
//  Move player or scenery up ..
// ------------------------------------------------------------------------------------------

void movePlayerUp() {

  player.setXDelta(0);
  level.setXOffsetDelta(0);

  if (player.getY() > (HEIGHT_LESS_TOOLBAR / 2) - 5) {
    
    player.setYDelta(-2);
    level.setYOffsetDelta(0);

  }
  else {

    if (level.getYOffset() < 0) {

      player.setYDelta(0);
      level.setYOffsetDelta(2);

    }
    else {

      if (player.getY() > 0) {

        player.setYDelta(-2);
        level.setYOffsetDelta(0);

      }

    }

  }

}