#include "src/utils/Arduboy2Ext.h"
#include <ArduboyTones.h>

//void renderScreen(GameState gameState) {
void renderScreen() {


  if (arduboy.everyXFrames(12)) flashPlayer = !flashPlayer;

  if (gameState != GameState::NextLevel && gameState != GameState::GameOver && gameState != GameState::RestartLevel) {
      
    for (uint8_t y = 0; y < level.getHeight(); y++) {

      for (uint8_t x = 0; x < level.getWidth() * 2; x++) {

        const auto tx = level.getXOffset() + (x * GRID_SIZE);
        const auto ty = level.getYOffset() + (y * GRID_SIZE);
        if (tx > -GRID_SIZE && tx < 128 && ty > -GRID_SIZE && ty < 64) {

          LevelElement element = (LevelElement)level.getLevelData(x, y);
          
          switch (element) {

            case LevelElement::Brick ... LevelElement::Gold:
              Sprites::drawOverwrite(tx, ty, levelElements[static_cast<uint8_t>(element)], 0);
              break;

            case LevelElement::Brick_1 ... LevelElement::Brick_4:
              Sprites::drawOverwrite(tx, ty - GRID_SIZE, levelElements[static_cast<uint8_t>(element)], 0);
              break;

            case LevelElement::Brick_Transition ... LevelElement::Brick_Close_4:
              Sprites::drawOverwrite(tx, ty, levelElements[static_cast<uint8_t>(element)], 0);
              break;

            default:
              break;

          }

        }

      }

    }


    // Draw player ..

    if (gameState == GameState::LevelPlay || flashPlayer) {

      boolean flip = (static_cast<int8_t>(player.getStance()) < 0);
      arduboy.drawCompressedMirror(player.getX(), player.getY(), men[absT(static_cast<int8_t>(player.getStance()))], WHITE, flip);

    }


    // Draw enemies ..

    for (uint8_t x = 0; x < NUMBER_OF_ENEMIES; x++) {

      Enemy *enemy = &enemies[x];

      if (enemy->getEnabled()) {

        if (enemy->getEscapeHole() == EscapeHole::None) {

          boolean flip = (static_cast<int8_t>(enemy->getStance()) < 0);
          arduboy.drawCompressedMirror(enemy->getX() + level.getXOffset(), enemy->getY() + level.getYOffset(), men[absT(static_cast<int8_t>(enemy->getStance()))], WHITE, flip);

        }
        else {

          switch (enemy->getEscapeHole()) {

            case EscapeHole::Wait1 ... EscapeHole::WaitMax:
              arduboy.drawCompressedMirror(enemy->getX() + level.getXOffset(), enemy->getY() + level.getYOffset(), man_StandingStill, WHITE, false);
              break;

            case EscapeHole::Wiggle1:
            case EscapeHole::Wiggle2:
            case EscapeHole::Wiggle5:
            case EscapeHole::Wiggle6:
              arduboy.drawCompressedMirror(enemy->getX() + level.getXOffset() - 1, enemy->getY() + level.getYOffset(), man_StandingStill, WHITE, false);
              break;

            case EscapeHole::Wiggle3:
            case EscapeHole::Wiggle4:
            case EscapeHole::Wiggle7:
            case EscapeHole::Wiggle8:
              arduboy.drawCompressedMirror(enemy->getX() + level.getXOffset() + 1, enemy->getY() + level.getYOffset(), man_StandingStill, WHITE, false);
              break;

            case EscapeHole::MoveUp9:
            case EscapeHole::MoveUp10:
              arduboy.drawCompressedMirror(enemy->getX() + level.getXOffset(), enemy->getY() + level.getYOffset() - 2, man_LaddderLeft, WHITE, false);
              break;

            case EscapeHole::MoveUp7:
            case EscapeHole::MoveUp8:
              arduboy.drawCompressedMirror(enemy->getX() + level.getXOffset(), enemy->getY() + level.getYOffset() - 4, man_LaddderRight, WHITE, false);
              break;

            case EscapeHole::MoveUp5:
            case EscapeHole::MoveUp6:
              arduboy.drawCompressedMirror(enemy->getX() + level.getXOffset(), enemy->getY() + level.getYOffset() - 6, man_LaddderLeft, WHITE, false);
              break;

            case EscapeHole::MoveUp3:
            case EscapeHole::MoveUp4:
              arduboy.drawCompressedMirror(enemy->getX() + level.getXOffset(), enemy->getY() + level.getYOffset() - 8, man_LaddderRight, WHITE, false);
              break;

            case EscapeHole::MoveUp2:
            case EscapeHole::MoveUp1:
            
              arduboy.drawCompressedMirror(enemy->getX() + level.getXOffset(), enemy->getY() + level.getYOffset() - 10, man_LaddderLeft, WHITE, false);
              enemy->setY(enemy->getY() - 10);
              enemy->setEscapeHole(EscapeHole::None);
              setDirectionAfterHoleEscape(enemy);

              break;

            default: break;

          }

        }

      }

    }


    #ifdef INC_ARROWS

    if (flashPlayer) {


      if (drawArrow(Direction::Up)) {

        arduboy.drawCompressedMirror(62, 0, arrow_TM_mask, BLACK, false);
        arduboy.drawCompressedMirror(62, 0, arrow_TM, WHITE, false);

      }

      if (drawArrow(Direction::RightUp)) {

        arduboy.drawCompressedMirror(123, 0, arrow_TR_mask, BLACK, false);
        arduboy.drawCompressedMirror(123, 0, arrow_TR, WHITE, false);

      }

      if (drawArrow(Direction::Right)) {

        arduboy.drawCompressedMirror(124, 24, arrow_MR_mask, BLACK, false);
        arduboy.drawCompressedMirror(124, 24, arrow_MR, WHITE, false);

      }
      
      if (drawArrow(Direction::RightDown)) {

        arduboy.drawCompressedMirror(123, 50, arrow_BR_mask, BLACK, false);
        arduboy.drawCompressedMirror(123, 50, arrow_BR, WHITE, false);

      }
        
      if (drawArrow(Direction::Down)) {

        arduboy.drawCompressedMirror(62, 50, arrow_BM_mask, BLACK, false);
        arduboy.drawCompressedMirror(62, 50, arrow_BM, WHITE, false);

      }
    
      if (drawArrow(Direction::LeftDown)) {

        arduboy.drawCompressedMirror(0, 50, arrow_BR_mask, BLACK, true);
        arduboy.drawCompressedMirror(0, 50, arrow_BR, WHITE, true);

      }

      if (drawArrow(Direction::Left)) {

        arduboy.drawCompressedMirror(0, 24, arrow_MR_mask, BLACK, true);
        arduboy.drawCompressedMirror(0, 24, arrow_MR, WHITE, true);

      }

      if (drawArrow(Direction::LeftUp)) {

        arduboy.drawCompressedMirror(0, 0, arrow_TR_mask, BLACK, true);
        arduboy.drawCompressedMirror(0, 0, arrow_TR, WHITE, true);

      }

    }

    #endif

  }


  // Draw entry rectangle ..

  switch (gameState) {

    case GameState::LevelEntryAnimation:

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
      break;

    case GameState::LevelExitAnimation:

      arduboy.drawRect(introRect, introRect, 128 - (introRect * 2), 55 - (introRect * 2), BLACK);
      drawHorizontalDottedLine(&arduboy, 0, 128, introRect);
      drawHorizontalDottedLine(&arduboy, 0, 128, 54 - introRect);
      drawVerticalDottedLine(&arduboy, 0, 64, introRect);
      drawVerticalDottedLine(&arduboy, 0, 64, 127 - introRect);

      for (int8_t x = 0; x < introRect; x++) {

        arduboy.drawRect(x, x, 127 - (x * 2) + 1, 54 - (x * 2) + 1, BLACK);

      }

      introRect++;


      // Game over, restart level or next level ?

      if (introRect == LEVEL_ANIMATION_BANNER_WIDTH) gameState = player.getNextState();
      break;

    case GameState::NextLevel:
      {
        drawHorizontalDottedLine(&arduboy, 41, 87, 22);
        drawHorizontalDottedLine(&arduboy, 41, 87, 32);
        arduboy.drawCompressedMirror(43, 25, levelChange, WHITE, false);

        uint8_t levelNumber = level.getLevelNumber();
        arduboy.drawCompressedMirror(72, 24, digits[levelNumber / 100], WHITE, false);
        levelNumber = levelNumber - (levelNumber / 100) * 100;
        arduboy.drawCompressedMirror(77, 24, digits[levelNumber / 10], WHITE, false);
        arduboy.drawCompressedMirror(82, 24, digits[levelNumber % 10], WHITE, false);
      }

      break;

    case GameState::RestartLevel:

      drawHorizontalDottedLine(&arduboy, 41, 87, 22);
      drawHorizontalDottedLine(&arduboy, 41, 87, 32);
      arduboy.drawCompressedMirror(42, 25, tryAgain, WHITE, false);

      break;

    case GameState::GameOver:

      drawHorizontalDottedLine(&arduboy, 41, 87, 22);
      drawHorizontalDottedLine(&arduboy, 41, 87, 32);
      arduboy.drawCompressedMirror(43, 25, gameOver, WHITE, false);

      break;

    default: break;

  }

 
  // Draw footer ..

  arduboy.fillRect(0, 55, 128, 64, BLACK);
  drawHorizontalDottedLine(&arduboy, 0, 128, 56);


  // Draw scoreboard ..

  uint16_t score = player.getScore();
  arduboy.drawCompressedMirror(0, 58, score_sc, WHITE, false);
  arduboy.drawCompressedMirror(29, 57, digit_00, WHITE, false);
  arduboy.drawCompressedMirror(34, 57, digits[score / 10000], WHITE, false);
  score = score - (score / 10000) * 10000;
  arduboy.drawCompressedMirror(39, 57, digits[score / 1000], WHITE, false);
  score = score - (score / 1000) * 1000;
  arduboy.drawCompressedMirror(44, 57, digits[score / 100], WHITE, false);
  score = score - (score / 100) * 100;
  arduboy.drawCompressedMirror(49, 57, digits[score / 10], WHITE, false);
  arduboy.drawCompressedMirror(54, 57, digits[score % 10], WHITE, false);

  uint8_t menLeft = player.getMen();
  arduboy.drawCompressedMirror(64, 58, men_sc, WHITE, false);
  arduboy.drawCompressedMirror(82, 57, digits[menLeft / 10], WHITE, false);
  arduboy.drawCompressedMirror(87, 57, digits[menLeft % 10], WHITE, false);

  if (gameState == GameState::LevelPlay) {

    uint8_t goldLeft = level.getGoldLeft();
    arduboy.drawCompressedMirror(96, 58, gold_sc, WHITE, false);
    arduboy.drawCompressedMirror(118, 57, digits[goldLeft / 10], WHITE, false);
    arduboy.drawCompressedMirror(123, 57, digits[goldLeft % 10], WHITE, false);

  }
  else {

    uint8_t levelNumber = level.getLevelNumber();
    arduboy.drawCompressedMirror(96, 58, level_sc, WHITE, false);
    arduboy.drawCompressedMirror(113, 57, digits[levelNumber / 100], WHITE, false);
    levelNumber = levelNumber - (levelNumber / 100) * 100;
    arduboy.drawCompressedMirror(118, 57, digits[levelNumber / 10], WHITE, false);
    arduboy.drawCompressedMirror(123, 57, digits[levelNumber % 10], WHITE, false);

  }

}

#ifdef INC_ARROWS
bool drawArrow(Direction direction) {

  for (uint8_t y = 0; y < level.getHeight(); y++) {

    for (uint8_t x = 0; x < level.getWidth() * 2; x++) {
      
      if (level.getLevelData(x, y) == LevelElement::Gold) {

        int16_t xDiff = ((player.getX() - level.getXOffset()) / GRID_SIZE) - x;
        int16_t yDiff = ((player.getY() - level.getYOffset()) / GRID_SIZE) - y;

        Direction retDirection = getDirection_8Directions(xDiff, yDiff);

        if (direction == retDirection) return true;

      }

    }

  }

  return false;

}
#endif
