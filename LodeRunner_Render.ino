#include "src/utils/Arduboy2Ext.h"
#include <ArduboyTones.h>

void renderScreen(bool play) {

  for (uint8_t y = 0; y < height; y++) {

    for (uint8_t x = 0; x < width * 2; x++) {

      if (level.xOffset + (x * GRID_SIZE) > -GRID_SIZE && level.xOffset + (x * GRID_SIZE) < 128 && level.yOffset + (y * GRID_SIZE) > -GRID_SIZE && level.yOffset + (y * GRID_SIZE) < 64) {

        LevelElement element = (LevelElement)getLevelData(x, y);
        
        switch (element) {

          case LevelElement::Brick ... LevelElement::Gold:
            arduboy.drawCompressedMirror(level.xOffset + (x * GRID_SIZE), level.yOffset + (y * GRID_SIZE), levelElements[(uint8_t)element], WHITE, false);
            break;

          case LevelElement::Brick_1 ... LevelElement::Brick_4:
            arduboy.drawCompressedMirror(level.xOffset + (x * GRID_SIZE), level.yOffset + (y * GRID_SIZE) - GRID_SIZE, levelElements[(uint8_t)element], WHITE, false);
            break;

          case LevelElement::Brick_Transition ... LevelElement::Brick_Close_4:
            arduboy.drawCompressedMirror(level.xOffset + (x * GRID_SIZE), level.yOffset + (y * GRID_SIZE), levelElements[(uint8_t)element], WHITE, false);
            break;

          default:
            break;

        }

      }

    }

  }


  // Draw player ..

  if (!play) {

    if (arduboy.everyXFrames(6)) flashPlayer = !flashPlayer;

  }

  if (play || flashPlayer) {

    boolean flip = ((int8_t) player.stance < 0);
    arduboy.drawCompressedMirror(player.x, player.y, men[absT((int8_t)player.stance)], WHITE, flip);

  }


  // Draw enemies ..

  for (uint8_t x = 0; x < NUMBER_OF_ENEMIES; x++) {

    Enemy *enemy = &enemies[x];

    if (enemy->enabled) {

      if (enemy->escapeHole == EscapeHole::None) {

        boolean flip = ((int8_t) enemy->stance < 0);
        arduboy.drawCompressedMirror(enemy->x + level.xOffset, enemy->y + level.yOffset, men[absT((int8_t)enemy->stance)], WHITE, flip);

      }
      else {

        switch (enemy->escapeHole) {

          case EscapeHole::Wait1 ... EscapeHole::WaitMax:
            arduboy.drawCompressedMirror(enemy->x + level.xOffset, enemy->y + level.yOffset, man_StandingStill, WHITE, false);
            break;

          case EscapeHole::Wiggle1:
          case EscapeHole::Wiggle2:
          case EscapeHole::Wiggle5:
          case EscapeHole::Wiggle6:
            arduboy.drawCompressedMirror(enemy->x + level.xOffset - 1, enemy->y + level.yOffset, man_StandingStill, WHITE, false);
            break;

          case EscapeHole::Wiggle3:
          case EscapeHole::Wiggle4:
          case EscapeHole::Wiggle7:
          case EscapeHole::Wiggle8:
            arduboy.drawCompressedMirror(enemy->x + level.xOffset + 1, enemy->y + level.yOffset, man_StandingStill, WHITE, false);
            break;

          case EscapeHole::MoveUp9:
          case EscapeHole::MoveUp10:
            arduboy.drawCompressedMirror(enemy->x + level.xOffset, enemy->y + level.yOffset - 2, man_LaddderLeft, WHITE, false);
            break;

          case EscapeHole::MoveUp7:
          case EscapeHole::MoveUp8:
            arduboy.drawCompressedMirror(enemy->x + level.xOffset, enemy->y + level.yOffset - 4, man_LaddderRight, WHITE, false);
            break;

          case EscapeHole::MoveUp5:
          case EscapeHole::MoveUp6:
            arduboy.drawCompressedMirror(enemy->x + level.xOffset, enemy->y + level.yOffset - 6, man_LaddderLeft, WHITE, false);
            break;

          case EscapeHole::MoveUp3:
          case EscapeHole::MoveUp4:
            arduboy.drawCompressedMirror(enemy->x + level.xOffset, enemy->y + level.yOffset - 8, man_LaddderRight, WHITE, false);
            break;

          case EscapeHole::MoveUp2:
          case EscapeHole::MoveUp1:
          
            arduboy.drawCompressedMirror(enemy->x + level.xOffset, enemy->y + level.yOffset - 10, man_LaddderLeft, WHITE, false);
            enemy->y = enemy->y - 10;
            enemy->escapeHole = EscapeHole::None;
            setDirectionAfterHoleEscape(enemy);

            break;

          default: break;

        }

      }

    }

  }

 
  // Draw foot and side bars ..

  arduboy.fillRect(0, 55, 128, 64, BLACK);
  drawHorizontalDottedLine(&arduboy, 0, 128, 56);


  // Draw scoreboard ..

  arduboy.drawCompressedMirror(0, 58, score, WHITE, false);
  arduboy.drawCompressedMirror(30, 57, digit_00, WHITE, false);
  arduboy.drawCompressedMirror(35, 57, digit_00, WHITE, false);
  arduboy.drawCompressedMirror(40, 57, digit_00, WHITE, false);
  arduboy.drawCompressedMirror(45, 57, digit_01, WHITE, false);
  arduboy.drawCompressedMirror(50, 57, digit_02, WHITE, false);
  arduboy.drawCompressedMirror(55, 57, digit_03, WHITE, false);

}