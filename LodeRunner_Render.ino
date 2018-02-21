#include "src/utils/Arduboy2Ext.h"
#include <ArduboyTones.h>

//void renderScreen(GameState gameState) {
void renderScreen() {

  for (uint8_t y = 0; y < level.getHeight(); y++) {

    for (uint8_t x = 0; x < level.getWidth() * 2; x++) {

      if (level.getXOffset() + (x * GRID_SIZE) > -GRID_SIZE && level.getXOffset() + (x * GRID_SIZE) < 128 && level.getYOffset() + (y * GRID_SIZE) > -GRID_SIZE && level.getYOffset() + (y * GRID_SIZE) < 64) {

        LevelElement element = (LevelElement)level.getLevelData(x, y);
        
        switch (element) {

          case LevelElement::Brick ... LevelElement::Gold:
            arduboy.drawCompressedMirror(level.getXOffset() + (x * GRID_SIZE), level.getYOffset() + (y * GRID_SIZE), levelElements[static_cast<uint8_t>(element)], WHITE, false);
            break;

          case LevelElement::Brick_1 ... LevelElement::Brick_4:
            arduboy.drawCompressedMirror(level.getXOffset() + (x * GRID_SIZE), level.getYOffset() + (y * GRID_SIZE) - GRID_SIZE, levelElements[static_cast<uint8_t>(element)], WHITE, false);
            break;

          case LevelElement::Brick_Transition ... LevelElement::Brick_Close_4:
            arduboy.drawCompressedMirror(level.getXOffset() + (x * GRID_SIZE), level.getYOffset() + (y * GRID_SIZE), levelElements[static_cast<uint8_t>(element)], WHITE, false);
            break;

          default:
            break;

        }

      }

    }

  }


  // Draw player ..

  if (gameState != GameState::LevelPlay) {

    if (arduboy.everyXFrames(6)) flashPlayer = !flashPlayer;

  }

  if (gameState == GameState::LevelPlay || flashPlayer) {

    boolean flip = (static_cast<int8_t>(player.stance) < 0);
    arduboy.drawCompressedMirror(player.x, player.y, men[absT(static_cast<int8_t>(player.stance))], WHITE, flip);

  }


  // Draw enemies ..

  for (uint8_t x = 0; x < NUMBER_OF_ENEMIES; x++) {

    Enemy *enemy = &enemies[x];

    if (enemy->enabled) {

      if (enemy->escapeHole == EscapeHole::None) {

        boolean flip = (static_cast<int8_t>(enemy->stance) < 0);
        arduboy.drawCompressedMirror(enemy->x + level.getXOffset(), enemy->y + level.getYOffset(), men[absT(static_cast<int8_t>(enemy->stance))], WHITE, flip);

      }
      else {

        switch (enemy->escapeHole) {

          case EscapeHole::Wait1 ... EscapeHole::WaitMax:
            arduboy.drawCompressedMirror(enemy->x + level.getXOffset(), enemy->y + level.getYOffset(), man_StandingStill, WHITE, false);
            break;

          case EscapeHole::Wiggle1:
          case EscapeHole::Wiggle2:
          case EscapeHole::Wiggle5:
          case EscapeHole::Wiggle6:
            arduboy.drawCompressedMirror(enemy->x + level.getXOffset() - 1, enemy->y + level.getYOffset(), man_StandingStill, WHITE, false);
            break;

          case EscapeHole::Wiggle3:
          case EscapeHole::Wiggle4:
          case EscapeHole::Wiggle7:
          case EscapeHole::Wiggle8:
            arduboy.drawCompressedMirror(enemy->x + level.getXOffset() + 1, enemy->y + level.getYOffset(), man_StandingStill, WHITE, false);
            break;

          case EscapeHole::MoveUp9:
          case EscapeHole::MoveUp10:
            arduboy.drawCompressedMirror(enemy->x + level.getXOffset(), enemy->y + level.getYOffset() - 2, man_LaddderLeft, WHITE, false);
            break;

          case EscapeHole::MoveUp7:
          case EscapeHole::MoveUp8:
            arduboy.drawCompressedMirror(enemy->x + level.getXOffset(), enemy->y + level.getYOffset() - 4, man_LaddderRight, WHITE, false);
            break;

          case EscapeHole::MoveUp5:
          case EscapeHole::MoveUp6:
            arduboy.drawCompressedMirror(enemy->x + level.getXOffset(), enemy->y + level.getYOffset() - 6, man_LaddderLeft, WHITE, false);
            break;

          case EscapeHole::MoveUp3:
          case EscapeHole::MoveUp4:
            arduboy.drawCompressedMirror(enemy->x + level.getXOffset(), enemy->y + level.getYOffset() - 8, man_LaddderRight, WHITE, false);
            break;

          case EscapeHole::MoveUp2:
          case EscapeHole::MoveUp1:
          
            arduboy.drawCompressedMirror(enemy->x + level.getXOffset(), enemy->y + level.getYOffset() - 10, man_LaddderLeft, WHITE, false);
            enemy->y = enemy->y - 10;
            enemy->escapeHole = EscapeHole::None;
            setDirectionAfterHoleEscape(enemy);

            break;

          default: break;

        }

      }

    }

  }


  // Draw rectangle ..

  if (gameState == GameState::LevelEntry) {

    arduboy.drawRect(introRect, introRect, 128 - (introRect * 2), 55 - (introRect * 2), BLACK);
    drawHorizontalDottedLine(&arduboy, 0, 128, introRect);
    drawHorizontalDottedLine(&arduboy, 0, 128, 54 - introRect);
    drawVerticalDottedLine(&arduboy, 0, 64, introRect);
    drawVerticalDottedLine(&arduboy, 0, 64, 127 - introRect);

    for (int8_t x = introRect - 1; x >= 0; x--) {

      arduboy.drawRect(x, x, 127 - (x * 2) + 1, 54 - (x * 2) + 1, BLACK);

    }

    introRect--;

    if (introRect == -1) gameState = GameState::LevelFlash;

  }


 
  // Draw footer ..

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