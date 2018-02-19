#include "src/utils/Arduboy2Ext.h"
#include <ArduboyTones.h>

void enemyMovements(Enemy *enemy) {

  if (enemy->x % GRID_SIZE == 0 && enemy->y % GRID_SIZE == 0) {

    bool hasMoved = false;
    uint8_t enemyX = enemy->x / GRID_SIZE;
    uint8_t enemyY = enemy->y / GRID_SIZE;

    LevelElement current =    level.getLevelData(enemyX, enemyY);
    LevelElement down =       level.getLevelData(enemyX, enemyY + 1);


    // If the enemy is in a hole, then attemt to wiggle out ..

    if (enemy->escapeHole > EscapeHole::None) {


      // Check to see if the enemy can continue falling ..

      if (canBeStoodOn_Enemy(down)) {
        
        enemy->yDelta = 0;

      }

      enemy->escapeHole--;

    }


    // Otherwise move the enemy towards the player ..

    else {

      LevelElement up =         level.getLevelData(enemyX, enemyY - 1);
      LevelElement right =      level.getLevelData(enemyX + 1, enemyY);
      LevelElement rightDown =  level.getLevelData(enemyX + 1, enemyY + 1);
      LevelElement leftDown =   level.getLevelData(enemyX - 1, enemyY + 1);
      LevelElement left =       level.getLevelData(enemyX - 1, enemyY);

      int16_t xDiff = enemy->x - (player.x - level.getXOffset());
      int16_t yDiff = enemy->y - (player.y - level.getYOffset());

      Direction direction = getDirection(xDiff, yDiff);
      Direction direction1 = direction;
      Direction direction2 = direction;


      // Can the enemy move in the preferred direction ?

      hasMoved = attemptToMove(enemy, enemyX, enemyY, direction, current, up, right, rightDown, down, leftDown, left);


      // If not, try to move in the closest possible direction to the preferred ..

      if (!hasMoved) {

        for (uint8_t x = 0; x < 8; x++) {

          if (!hasMoved) { 
            
            direction1--; 
            hasMoved = attemptToMove(enemy, enemyX, enemyY, direction1, current, up, right, rightDown, down, leftDown, left); 
            if (hasMoved) break;
            
          }
      
          if (!hasMoved) { 
            
            direction2++; 
            hasMoved = attemptToMove(enemy, enemyX, enemyY, direction2, current, up, right, rightDown, down, leftDown, left); 
            if (hasMoved) break;

          }

        }

      }


      // If no movement and we are falling, check to see if we have hit the bottom ..

      if (!hasMoved && enemy->stance == PlayerStance::Falling) {

        if (canBeStoodOn_Enemy(down)) {

          enemy->yDelta = 0;

        }

      }

    }  

  }

    // // Reduce differences to a ratio of x:1 or 1:y ..

    // if (absT(xDiff) > absT(yDiff) && yDiff != 0) { xDiff = xDiff / abst(yDiff); yDiff = abstT(yDiff) / yDiff; }
    // if (absT(yDiff) > absT(xDiff) && xDiff != 0) { yDiff = yDiff / abst(xDiff); xDiff = abstT(xDiff) / xDiff; }

}

boolean attemptToMove(Enemy *enemy, uint8_t enemyX, uint8_t enemyY, Direction direction, 
                      LevelElement current, LevelElement up,  
                      LevelElement right, LevelElement rightDown, LevelElement down,
                      LevelElement leftDown, LevelElement left) {

  bool hasMoved = false;

  switch (direction) {

    case Direction::LeftUp ... Direction::LeftUp2:
    case Direction::Up     ... Direction::RightUp:

      if ( (current == LevelElement::Ladder || current == LevelElement::LadderLevel) && 
            (up == LevelElement::Ladder || up == LevelElement::LadderLevel) ) {

        if (enemy->stance < PlayerStance::Climbing_Up1 || enemy->stance > PlayerStance::Climbing_Up2) enemy->stance = PlayerStance::Climbing_Up1;
        moveUp(enemy);
        hasMoved = true;

      }

      break;

    case Direction::RightUp2 ... Direction::RightDown1:

      if (canBeFallenInto_Enemy(down, enemies, enemyX, enemyY + 1)) {

        enemy->stance = PlayerStance::Falling;
        moveDown(enemy);
        hasMoved = true;


        // If we have fallen into a brick hole, start counting ..

        switch (down) {

          case LevelElement::Brick_1 ... LevelElement::Brick_Close_4:
            enemy->escapeHole = EscapeHole::WaitMax;
            break;
          
          default:  break;

        }

      }

      else if (canBeStoodOn_Enemy(rightDown) && canBeOccupied_Enemy(right)) {

        if (enemy->stance < PlayerStance::Running_Right1 || enemy->stance < PlayerStance::Running_Right4) enemy->stance = PlayerStance::Running_Right1;
        moveRight(enemy);
        hasMoved = true;

      }

      else if (right == LevelElement::Rail) {

        if (enemy->stance < PlayerStance::Swinging_Right1 || enemy->stance < PlayerStance::Swinging_Right4) enemy->stance = PlayerStance::Swinging_Right1;
        moveRight(enemy);
        hasMoved = true;

      }

      else if (right == LevelElement::Ladder || right == LevelElement::LadderLevel) {
        if (enemy->stance < PlayerStance::Climbing_Up1 || enemy->stance < PlayerStance::Climbing_Up2) enemy->stance = PlayerStance::Climbing_Up1;
        moveRight(enemy);
        hasMoved = true;
      }

      break;

    case Direction::RightDown ... Direction::LeftDown:

      if (down == LevelElement::Ladder || down == LevelElement::LadderLevel) {

        if (enemy->stance < PlayerStance::Climbing_Down1 || enemy->stance < PlayerStance::Climbing_Down2) enemy->stance = PlayerStance::Climbing_Down1;
        moveDown(enemy);
        hasMoved = true;

      }

      else if (canBeFallenInto_Enemy(down, enemies, enemyX, enemyY + 1)) {

        enemy->stance = PlayerStance::Falling;
        moveDown(enemy);
        hasMoved = true;


        // If we have fallen into a brick hole, start counting ..

        switch (down) {

          case LevelElement::Brick_1 ... LevelElement::Brick_Close_4:
            enemy->escapeHole = EscapeHole::WaitMax;
            break;
          
          default:  break;

        }

      }

      break;

    case Direction::LeftDown2 ... Direction::LeftUp1:

      if (canBeFallenInto_Enemy(down, enemies, enemyX, enemyY + 1)) {

        enemy->stance = PlayerStance::Falling;
        moveDown(enemy);
        hasMoved = true;


        // If we have fallen into a brick hole, start counting ..

        switch (down) {

          case LevelElement::Brick_1 ... LevelElement::Brick_Close_4:
            enemy->escapeHole = EscapeHole::WaitMax;
            break;
          
          default:  break;

        }

      }

      else if (canBeStoodOn_Enemy(leftDown) && canBeOccupied_Enemy(left)) {

        if (enemy->stance < PlayerStance::Running_Left4 || enemy->stance > PlayerStance::Running_Left1) enemy->stance = PlayerStance::Running_Left1;
        moveLeft(enemy);
        hasMoved = true;

      }

      else if (left == LevelElement::Rail) {

        if (enemy->stance < PlayerStance::Swinging_Left4 || enemy->stance < PlayerStance::Swinging_Left1) enemy->stance = PlayerStance::Swinging_Left1;
        moveLeft(enemy);
        hasMoved = true;

      }

      else if (left == LevelElement::Ladder || left == LevelElement::LadderLevel) {

        if (enemy->stance < PlayerStance::Climbing_Up1 || enemy->stance < PlayerStance::Climbing_Up2) enemy->stance = PlayerStance::Climbing_Up1;
        moveLeft(enemy);
        hasMoved = true;

      }
      break;

    default:  break;

  }

  return hasMoved;
  
}


void setDirectionAfterHoleEscape(Enemy *enemy) {

  uint8_t enemyX = enemy->x / GRID_SIZE;
  uint8_t enemyY = enemy->y / GRID_SIZE;

  LevelElement left       = level.getLevelData(enemyX - 1, enemyY);
  LevelElement leftDown   = level.getLevelData(enemyX - 1, enemyY + 1);
  LevelElement right      = level.getLevelData(enemyX + 1, enemyY);
  LevelElement rightDown  = level.getLevelData(enemyX + 1, enemyY + 1);

  if (static_cast<int16_t>(enemy->x) > (static_cast<int16_t>(player.x) - level.getXOffset())) {

    if (canBeOccupied_Enemy(left) && canBeStoodOn_Enemy(leftDown)) {
    
      enemy->stance = PlayerStance::Running_Left1;
      enemy->xDelta = -2;
      
    }
    else {
    
      enemy->stance = PlayerStance::Running_Right1;
      enemy->xDelta = 2;

    }

  }
  else {

    if (canBeOccupied_Enemy(right) && canBeStoodOn_Enemy(rightDown)) {

      enemy->stance = PlayerStance::Running_Right1;
      enemy->xDelta = 2;
      
    }
    else {

      enemy->stance = PlayerStance::Running_Left1;
      enemy->xDelta = -2;
      
    }

  }

}


void moveUp(Enemy *enemy) {

  enemy->xDelta = 0;
  enemy->yDelta = -2;
 
}

void moveRight(Enemy *enemy) {

  enemy->xDelta = 2;
  enemy->yDelta = 0;
 
}

void moveDown(Enemy *enemy) {

  enemy->xDelta = 0;
  enemy->yDelta = 2;
 
}

void moveLeft(Enemy *enemy) {

  enemy->xDelta = -2;
  enemy->yDelta = 0;
 
}