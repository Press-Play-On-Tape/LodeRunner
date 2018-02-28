#include "src/utils/Arduboy2Ext.h"
#include <ArduboyTones.h>

void clearEnemyMovementPositions(Enemy *enemies) {
  
  for (uint8_t x = 0; x < NUMBER_OF_ENEMIES; x++) {

    Enemy *enemy = &enemies[x];
    enemy->setXFuturePosition(0);
    enemy->setYFuturePosition(0);

  }
  
}

void enemyMovements(Enemy *enemy) {

  uint8_t enemyX = enemy->getX() / GRID_SIZE;
  uint8_t enemyY = enemy->getY() / GRID_SIZE;


  // Check to see if the enemy has touched gold!

  if (level.getLevelData(enemyX, enemyY) == LevelElement::Gold && enemy->getHasGold() == 0) {

    if (random(0, ENEMY_GOLD_PICKUP_THRESHOLD) == 0) {

      enemy->setHasGold(random(ENEMY_GOLD_HOLD_MINIMUM, ENEMY_GOLD_HOLD_MAXIMUM));
      level.setLevelData(enemyX, enemyY, LevelElement::Blank);

    }

  }


  // Move enemy ..

  switch (enemy->getPlayerStance()) {


    // If the enemy is being reborn, return without moving ..

    case PlayerStance::Rebirth_1 ... PlayerStance::Rebirth_3:
      break;


    // Otherwise move the enemy towards the player ..

    default:

      if (enemy->getX() % GRID_SIZE == 0 && enemy->getY() % GRID_SIZE == 0) {


        bool hasMoved = false;
        enemyX = enemy->getX() / GRID_SIZE;
        enemyY = enemy->getY() / GRID_SIZE;

        LevelElement current =    level.getLevelData(enemyX, enemyY);
        //LevelElement down =       level.getLevelData(enemyX, enemyY + 1);


        // If the enemy is in a hole, then attemt to wiggle out ..

        if (enemy->getEscapeHole() > EscapeHole::None) {


          // If the enemy has gold, then make it available to pickup ..

          if (enemy->getHasGold() > ENEMY_GOLD_DROP_VALUE) {

            enemy->setHasGold(0);
            level.setLevelData(enemyX, enemyY - 1, LevelElement::Gold);

          }



          // Check to see if the enemy can continue falling ..

//          if (canBeStoodOnBasic_Enemy(down)) {
            
            enemy->setYDelta(0);

//          }

          enemy->setEscapeHole(static_cast<EscapeHole>(static_cast<uint8_t>(enemy->getEscapeHole()) - 1));

        }


        // Otherwise move the enemy towards the player ..

        else {

          LevelElement up =         level.getLevelData(enemyX, enemyY - 1);
          LevelElement right =      level.getLevelData(enemyX + 1, enemyY);
          LevelElement rightDown =  level.getLevelData(enemyX + 1, enemyY + 1);
          LevelElement leftDown =   level.getLevelData(enemyX - 1, enemyY + 1);
          LevelElement left =       level.getLevelData(enemyX - 1, enemyY);
          LevelElement down =       level.getLevelData(enemyX, enemyY + 1);

          int16_t xDiff = enemy->getX() - (player.getX() - level.getXOffset());
          int16_t yDiff = enemy->getY() - (player.getY() - level.getYOffset());

          Direction direction = getDirection_16Directions(xDiff, yDiff);
          Direction direction1 = direction;
          Direction direction2 = direction;



          // Drop the gold?

          if (enemy->getHasGold() > 0 && isSolid(down) && current == LevelElement::Blank) {

            enemy->setHasGold(enemy->getHasGold() - 1);

            if (enemy->getHasGold() == ENEMY_GOLD_DROP_VALUE) {

              level.setLevelData(enemyX, enemyY, LevelElement::Gold);

            }

          }
 

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

          if (!hasMoved && enemy->getPlayerStance() == PlayerStance::Falling) {

            if (canBeStoodOn_Enemy(down)) {

               enemy->setYDelta(0);

            }

          }

        }  

      }

      break;

  }

}

boolean isOccupiedByAnotherEnemy(Enemy *enemies, Enemy *enemy, int8_t xDelta, int8_t yDelta) {

  for (uint8_t x = 0; x < NUMBER_OF_ENEMIES; x++) {

    Enemy *testEnemy = &enemies[x];

    if (testEnemy->getEnabled() && testEnemy->getId() != enemy->getId()) {

      Rect testRect = { static_cast<int16_t>(testEnemy->getX() + testEnemy->getXFuturePosition()), static_cast<int16_t>(testEnemy->getY() + testEnemy->getYFuturePosition()), GRID_SIZE, GRID_SIZE };
      Rect enemyRect = { static_cast<int16_t>(enemy->getX() + xDelta), static_cast<int16_t>(enemy->getY() + yDelta), GRID_SIZE, GRID_SIZE };

      if (arduboy.collide(testRect, enemyRect)) {

        return true;

      }

    }

  }

  return false;

}

boolean attemptToMove(Enemy *enemy, uint8_t enemyX, uint8_t enemyY, Direction direction, 
                      LevelElement current, LevelElement up,  
                      LevelElement right, LevelElement rightDown, LevelElement down,
                      LevelElement leftDown, LevelElement left) {

  bool hasMoved = false;

  switch (direction) {

    case Direction::LeftUp ... Direction::LeftUp2:
    case Direction::Up     ... Direction::RightUp:

      if ( current == LevelElement::Ladder && up == LevelElement::Ladder && !isOccupiedByAnotherEnemy(enemies, enemy, 0, -GRID_SIZE) ) {

        if (enemy->getPlayerStance() < PlayerStance::Climbing_Up1 || enemy->getPlayerStance() > PlayerStance::Climbing_Up2) enemy->setPlayerStance(PlayerStance::Climbing_Up1);
        moveUp(enemy);
        hasMoved = true;

      }

      break;

    case Direction::RightUp2 ... Direction::RightDown1:

      if (right == LevelElement::Rail && !isOccupiedByAnotherEnemy(enemies, enemy, GRID_SIZE, 0)) {

        if (enemy->getPlayerStance() < PlayerStance::Swinging_Right1 || enemy->getPlayerStance() > PlayerStance::Swinging_Right4) enemy->setPlayerStance(PlayerStance::Swinging_Right1);
        moveRight(enemy);
        hasMoved = true;

      }

      else if (current == LevelElement::Rail && canBeStoodOnBasic_Enemy(rightDown) && !isOccupiedByAnotherEnemy(enemies, enemy, GRID_SIZE, 0)) {

        if (enemy->getPlayerStance() < PlayerStance::Running_Right1 || enemy->getPlayerStance() > PlayerStance::Running_Right4) enemy->setPlayerStance(PlayerStance::Running_Right1);
        moveRight(enemy);
        hasMoved = true;

      }

      else if (right == LevelElement::Ladder && !isOccupiedByAnotherEnemy(enemies, enemy, GRID_SIZE, 0)) {

        if (enemy->getPlayerStance() < PlayerStance::Climbing_Up1 || enemy->getPlayerStance() > PlayerStance::Climbing_Up2) enemy->setPlayerStance(PlayerStance::Climbing_Up1);
        moveRight(enemy);
        hasMoved = true;

      }

      else if (canBeFallenInto_Enemy(down, enemies, enemyX, enemyY + 1)) {

        if (right == LevelElement::Ladder && !isOccupiedByAnotherEnemy(enemies, enemy, GRID_SIZE, 0)) {

          if (enemy->getPlayerStance() < PlayerStance::Swinging_Right1 || enemy->getPlayerStance() > PlayerStance::Swinging_Right4)  enemy->setPlayerStance(PlayerStance::Swinging_Right1);
          moveRight(enemy);
          hasMoved = true;

        }
        else {
            
          if (!isOccupiedByAnotherEnemy(enemies, enemy, 0, GRID_SIZE)) {

            enemy->setPlayerStance(PlayerStance::Falling);
            moveDown(enemy);
            hasMoved = true;


            // If we have fallen into a brick hole, start counting ..

            switch (down) {

              case LevelElement::Brick_1 ... LevelElement::Brick_Close_4:
                enemy->setEscapeHole(EscapeHole::WaitMax);
                break;
              
              default:  break;

            }

          }

        }

      }

      else if (canBeStoodOn_Enemy(rightDown) && canBeOccupied_Enemy(right) && !isOccupiedByAnotherEnemy(enemies, enemy, GRID_SIZE, 0)) {

        if (enemy->getPlayerStance() < PlayerStance::Running_Right1 || enemy->getPlayerStance() > PlayerStance::Running_Right4) enemy->setPlayerStance(PlayerStance::Running_Right1);
        moveRight(enemy);
        hasMoved = true;

      }

      break;

    case Direction::RightDown ... Direction::LeftDown:

      if (down == LevelElement::Ladder && !isOccupiedByAnotherEnemy(enemies, enemy, 0, GRID_SIZE)) {

        if (enemy->getPlayerStance() < PlayerStance::Climbing_Down1 || enemy->getPlayerStance() < PlayerStance::Climbing_Down2) enemy->setPlayerStance(PlayerStance::Climbing_Down1);
        moveDown(enemy);
        hasMoved = true;

      }

      else if (canBeFallenInto_Enemy(down, enemies, enemyX, enemyY + 1) && !isOccupiedByAnotherEnemy(enemies, enemy, 0, GRID_SIZE)) {

        enemy->setPlayerStance(PlayerStance::Falling);
        moveDown(enemy);
        hasMoved = true;


        // If we have fallen into a brick hole, start counting ..

        switch (down) {

          case LevelElement::Brick_1 ... LevelElement::Brick_Close_4:
            enemy->setEscapeHole(EscapeHole::WaitMax);
            break;
          
          default:  break;

        }

      }

      break;

    case Direction::LeftDown2 ... Direction::LeftUp1:

      if (left == LevelElement::Rail && !isOccupiedByAnotherEnemy(enemies, enemy, -GRID_SIZE, 0)) {

        if (enemy->getPlayerStance() < PlayerStance::Swinging_Left4 || enemy->getPlayerStance() > PlayerStance::Swinging_Left1) enemy->setPlayerStance(PlayerStance::Swinging_Left1);
        moveLeft(enemy);
        hasMoved = true;

      }
      
      else if (current == LevelElement::Rail && canBeStoodOnBasic_Enemy(leftDown) && !isOccupiedByAnotherEnemy(enemies, enemy, -GRID_SIZE, 0)) {

        if (enemy->getPlayerStance() < PlayerStance::Running_Left4 || enemy->getPlayerStance() > PlayerStance::Running_Left1) enemy->setPlayerStance(PlayerStance::Running_Left1);
        moveLeft(enemy);
        hasMoved = true;

      }
      
      else if (left == LevelElement::Ladder && !isOccupiedByAnotherEnemy(enemies, enemy, -GRID_SIZE, 0)) {

        if (enemy->getPlayerStance() < PlayerStance::Climbing_Up1 || enemy->getPlayerStance() > PlayerStance::Climbing_Up2) enemy->setPlayerStance(PlayerStance::Climbing_Up1);
        moveLeft(enemy);
        hasMoved = true;

      }

      else if (canBeFallenInto_Enemy(down, enemies, enemyX, enemyY + 1)) {

        if (left == LevelElement::Ladder && !isOccupiedByAnotherEnemy(enemies, enemy, -GRID_SIZE, 0)) {

          if (enemy->getPlayerStance() < PlayerStance::Swinging_Left4 || enemy->getPlayerStance() > PlayerStance::Swinging_Left1)  enemy->setPlayerStance(PlayerStance::Swinging_Left1);
          moveLeft(enemy);
          hasMoved = true;

        }
        else {

          if (!isOccupiedByAnotherEnemy(enemies, enemy, 0, GRID_SIZE)) {

            enemy->setPlayerStance(PlayerStance::Falling);
            moveDown(enemy);
            hasMoved = true;


            // If we have fallen into a brick hole, start counting ..

            switch (down) {

              case LevelElement::Brick_1 ... LevelElement::Brick_Close_4:
                enemy->setEscapeHole(EscapeHole::WaitMax);
                break;
              
              default:  break;

            }

          }

        }

      }
            
      else if (canBeStoodOn_Enemy(leftDown) && canBeOccupied_Enemy(left) && !isOccupiedByAnotherEnemy(enemies, enemy, -GRID_SIZE, 0)) {

        if (enemy->getPlayerStance() < PlayerStance::Running_Left4 || enemy->getPlayerStance() > PlayerStance::Running_Left1) enemy->setPlayerStance(PlayerStance::Running_Left1);
        moveLeft(enemy);
        hasMoved = true;

      }

      break;

    default:  break;

  }

  return hasMoved;
  
}


void setDirectionAfterHoleEscape(Enemy *enemy) {

  uint8_t enemyX = enemy->getX() / GRID_SIZE;
  uint8_t enemyY = enemy->getY() / GRID_SIZE;

  LevelElement left       = level.getLevelData(enemyX - 1, enemyY);
  LevelElement leftDown   = level.getLevelData(enemyX - 1, enemyY + 1);
  LevelElement right      = level.getLevelData(enemyX + 1, enemyY);
  LevelElement rightDown  = level.getLevelData(enemyX + 1, enemyY + 1);

  if (static_cast<int16_t>(enemy->getX()) > (static_cast<int16_t>(player.getX()) - level.getXOffset())) {

    if (canBeOccupied_Enemy(left) && canBeStoodOn_Enemy(leftDown)) {
    
      enemy->setPlayerStance(PlayerStance::Running_Left1);
      enemy->setXDelta(-2);
      
    }
    else {
    
      enemy->setPlayerStance(PlayerStance::Running_Right1);
      enemy->setXDelta(2);

    }

  }
  else {

    if (canBeOccupied_Enemy(right) && canBeStoodOn_Enemy(rightDown)) {

      enemy->setPlayerStance(PlayerStance::Running_Right1);
      enemy->setXDelta(2);
      
    }
    else {

      enemy->setPlayerStance(PlayerStance::Running_Left1);
      enemy->setXDelta(-2);
      
    }

  }

}


void moveUp(Enemy *enemy) {

  enemy->setXDelta(0);
  enemy->setYDelta(-2);
  enemy->setYFuturePosition(-GRID_SIZE);
 
}

void moveRight(Enemy *enemy) {

  enemy->setXDelta(2);
  enemy->setYDelta(0);
  enemy->setXFuturePosition(GRID_SIZE);
 
}

void moveDown(Enemy *enemy) {

  enemy->setXDelta(0);
  enemy->setYDelta(2);
  enemy->setYFuturePosition(GRID_SIZE);
 
}

void moveLeft(Enemy *enemy) {

  enemy->setXDelta(-2);
  enemy->setYDelta(0);
  enemy->setXFuturePosition(-GRID_SIZE);
 
}