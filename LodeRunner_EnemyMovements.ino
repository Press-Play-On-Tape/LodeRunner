#include "src/utils/Arduboy2Ext.h"
#include <ArduboyTones.h>

void enemyMovements(Enemy *enemy) {

  if (enemy->x % GRID_SIZE == 0 && enemy->y % GRID_SIZE == 0) {

    bool hasMoved = false;
    uint8_t enemyX = enemy->x / GRID_SIZE;
    uint8_t enemyY = enemy->y / GRID_SIZE;

    LevelElement current =    getLevelData(enemyX, enemyY);


    // If the enemy is in a hole, then attemt to wiggle out ..

    if (current >= LevelElement::Brick_Transition) {

    }


    // Otherwise move the enemy towards the player ..

    else {

      LevelElement up =         getLevelData(enemyX, enemyY - 1);
      LevelElement rightUp =    getLevelData(enemyX + 1, enemyY - 1);
      LevelElement right =      getLevelData(enemyX + 1, enemyY);
      LevelElement rightDown =  getLevelData(enemyX + 1, enemyY + 1);
      LevelElement down =       getLevelData(enemyX, enemyY + 1);
      LevelElement leftDown =   getLevelData(enemyX - 1, enemyY + 1);
      LevelElement left =       getLevelData(enemyX - 1, enemyY);
      LevelElement leftUp =     getLevelData(enemyX - 1, enemyY - 1);

      int16_t xDiff = enemy->x - (player.x - level.xOffset);
      int16_t yDiff = enemy->y - (player.y - level.yOffset);

      Direction direction = getDirection(xDiff, yDiff);
      Direction direction1 = direction;
      Direction direction2 = direction;


      // Can the enemy move in the preferred direction ?

      hasMoved = attemptToMove(enemy, direction, current, up, rightUp, right, rightDown, down, leftDown, left, leftUp);
  

      // If not, try to move in the closest possible direction to the preferred ..

      for (uint8_t x = 0; x < 8; x++) {

        if (!hasMoved) { 
          
          direction1--; 
          hasMoved = attemptToMove(enemy, direction1, current, up, rightUp, right, rightDown, down, leftDown, left, leftUp); 
          if (hasMoved) break;
          
        }
    
        if (!hasMoved) { 
          
          direction2++; 
          hasMoved = attemptToMove(enemy, direction2, current, up, rightUp, right, rightDown, down, leftDown, left, leftUp); 
          if (hasMoved) break;

        }

      }

    }  

  }

    // // Reduce differences to a ratio of x:1 or 1:y ..

    // if (absT(xDiff) > absT(yDiff) && yDiff != 0) { xDiff = xDiff / abst(yDiff); yDiff = abstT(yDiff) / yDiff; }
    // if (absT(yDiff) > absT(xDiff) && xDiff != 0) { yDiff = yDiff / abst(xDiff); xDiff = abstT(xDiff) / xDiff; }

}

boolean attemptToMove(Enemy *enemy, Direction direction, 
                      LevelElement current, LevelElement up, LevelElement rightUp, 
                      LevelElement right, LevelElement rightDown, LevelElement down,
                      LevelElement leftDown, LevelElement left, LevelElement leftUp) {

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

      if (canBeStoodOn_Enemy(rightDown) && canBeOccupiedTemporarily(right)) {
        if (enemy->stance < PlayerStance::Running_Right1 || enemy->stance < PlayerStance::Running_Right4) enemy->stance = PlayerStance::Running_Right1;
        moveRight(enemy);
        hasMoved = true;
      }

      if (canBeFallenIntoTemporarily(rightDown) && canBeOccupiedTemporarily(right)) {
        enemy->stance = PlayerStance::Falling;
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

      else if (canBeFallenInto(down)) {
        enemy->stance = PlayerStance::Falling;
        moveDown(enemy);
        hasMoved = true;
      }

      break;

    case Direction::LeftDown2 ... Direction::LeftUp1:

      if (canBeStoodOn_Enemy(leftDown) && canBeOccupiedTemporarily(left)) {
        if (enemy->stance < PlayerStance::Running_Left4 || enemy->stance < PlayerStance::Running_Left1) enemy->stance = PlayerStance::Running_Left1;
        moveLeft(enemy);
        hasMoved = true;
      }

      if (canBeFallenIntoTemporarily(rightDown) && canBeOccupiedTemporarily(left)) {
        enemy->stance = PlayerStance::Falling;
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