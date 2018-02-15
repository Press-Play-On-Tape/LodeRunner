#include "src/utils/Arduboy2Ext.h"
#include <ArduboyTones.h>
#include "Enums.h"
#include "Images.h"


void enemyMovements(Enemy *enemy) {

  if (enemy->x % gridSize == 0 && enemy->y % gridSize == 0) {

    bool haveMoved = false;
    uint8_t enemyX = getNearestX();
    uint8_t nearestY = getNearestY();

    LevelElement up =         getLevelData(nearestX, nearestY - 1);
    LevelElement rightUp =    getLevelData(nearestX + 1, nearestY - 1);
    LevelElement right =      getLevelData(nearestX + 1, nearestY);
    LevelElement rightDown =  getLevelData(nearestX + 1, nearestY + 1);
    LevelElement down =       getLevelData(nearestX, nearestY + 1);
    LevelElement leftDown =   getLevelData(nearestX - 1, nearestY + 1);
    LevelElement left =       getLevelData(nearestX - 1, nearestY);
    LevelElement leftUp =     getLevelData(nearestX - 1, nearestY - 1);

    int16_t xDiff = enemy.x - (player.x - level.xOffset);
    int16_t yDiff = enemy.y - (player.y - level.yOffset);


    // Reduce differences to a ratio of x:1 or 1:y ..

    if (absT(xDiff) > absT(yDiff) { xDiff = xDiff / abst(yDiff); yDiff = abstT(yDiff) / yDiff; }
    if (absT(yDiff) > absT(xDiff) { yDiff = yDiff / abst(xDiff); xDiff = abstT(xDiff) / xDiff; }

    if (xDiff < 0 && yDiff == 0) {  // move left

      if (canBeOccupiedTemporarily(left)) {

        if (canBeStoodOn(leftDown) || left == LevelElement::Rail) {

          moveLeft();
          return;

        }

      }

    }

  }

}