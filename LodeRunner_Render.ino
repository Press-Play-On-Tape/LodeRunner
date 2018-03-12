#include "src/utils/Arduboy2Ext.h"
#include <ArduboyTones.h>


// ------------------------------------------------------------------------------------------
//  Render the screen, players and scorboard ..
//
void renderScreen() {

  if (arduboy.everyXFrames(12)) flashPlayer = !flashPlayer;

  if (gameState != GameState::NextLevel && gameState != GameState::GameOver && gameState != GameState::RestartLevel) {

    renderLevelElements();


    // Draw player ..

    if (gameState == GameState::LevelPlay || flashPlayer) {

      boolean flip = (static_cast<int8_t>(player.getStance()) < 0);
      arduboy.drawCompressedMirror(player.getX(), player.getY(), men[absT(static_cast<int8_t>(player.getStance()))], WHITE, flip);

    }

    renderEnemies();

    #ifdef INC_ARROWS
    if (showArrows) renderArrows();
    #endif

  }


  // Draw entry rectangle ..

  renderEntryRectangle();


  // Draw footer ..

  arduboy.fillRect(0, 55, 128, 64, BLACK);
  arduboy.drawHorizontalDottedLine(0, 128, 56);


  // Draw scoreboard ..

  renderScoreboard();

}


// ------------------------------------------------------------------------------------------
//  Render the level elements (bricks, ladders, rails, etc) ..
//
void renderLevelElements() {

  for (uint8_t y = 0; y < level.getHeight(); y++) {

    for (uint8_t x = 0; x < level.getWidth() * 2; x++) {

      const auto tx = level.getXOffset() + (x * GRID_SIZE);
      const auto ty = level.getYOffset() + (y * GRID_SIZE);

      if (tx > -GRID_SIZE && tx < 128 && ty > -GRID_SIZE && ty < 64) {

        LevelElement element = (LevelElement)level.getLevelData(x, y);

        if (static_cast<uint8_t>(element) > 0) Sprites::drawOverwrite(tx, ty, levelElementImgs, static_cast<uint8_t>(element));

        if (element >= LevelElement::Brick_1 && element <= LevelElement::Brick_4) {

          Sprites::drawOverwrite(tx, ty - GRID_SIZE, brickDiggingImgs, static_cast<uint8_t>(element) - static_cast<uint8_t>(LevelElement::Brick_1));

        }

      }

    }

  }

}


// ------------------------------------------------------------------------------------------
//  Render the enemies ..
//
void renderEnemies() {

  for (uint8_t x = 0; x < NUMBER_OF_ENEMIES; x++) {

    Enemy *enemy = &enemies[x];

    if (enemy->getEnabled()) {

      const auto ex = enemy->getX() + level.getXOffset();
      const auto ey = enemy->getY() + level.getYOffset();

      auto dx = ex;
      auto dy = ey;
      uint8_t const * image = man_StandingStill;
      bool flip = false;

      switch (enemy->getEscapeHole()) {

        case EscapeHole::None:
          flip = (static_cast<int8_t>(enemy->getStance()) < 0);
          image = men[absT(static_cast<int8_t>(enemy->getStance()))];
          break;

        case EscapeHole::Wait1 ... EscapeHole::WaitMax:
          break;

        case EscapeHole::Wiggle1:
        case EscapeHole::Wiggle2:
        case EscapeHole::Wiggle5:
        case EscapeHole::Wiggle6:
          dx = ex - 1;
          break;

        case EscapeHole::Wiggle3:
        case EscapeHole::Wiggle4:
        case EscapeHole::Wiggle7:
        case EscapeHole::Wiggle8:
          dx = ex + 1;
          break;

        case EscapeHole::MoveUp9:
        case EscapeHole::MoveUp10:
          dy = ey - 2;
          image = man_LaddderLeft;
          break;

        case EscapeHole::MoveUp7:
        case EscapeHole::MoveUp8:
          dy = ey - 4;
          image = man_LaddderRight;
          break;

        case EscapeHole::MoveUp5:
        case EscapeHole::MoveUp6:
          dy = ey - 6;
          image = man_LaddderLeft;
          break;

        case EscapeHole::MoveUp3:
        case EscapeHole::MoveUp4:
          dy = ey - 8;
          image = man_LaddderRight;
          break;

        case EscapeHole::MoveUp2:
        case EscapeHole::MoveUp1:

          dy = ey - 10;
          image = man_LaddderLeft;

          enemy->setY(enemy->getY() - 10);
          enemy->setEscapeHole(EscapeHole::None);
          setDirectionAfterHoleEscape(enemy);

          break;

        default:
          // Uncomment this if man_StandingStill being default is an issue
          // will increase code size by ~30 bytes
          //continue;
          break;

        }

        arduboy.drawCompressedMirror(dx, dy, image, WHITE, flip);

    }

  }

}


// ------------------------------------------------------------------------------------------
//  Render the arrows that indicate enemy and gold positions ..
//
#ifdef INC_ARROWS
void renderArrows() {
 
  int16_t px = player.getX() - level.getXOffset();
  int16_t py = player.getY() - level.getYOffset();

  for (uint8_t x = 0; x < NUMBER_OF_ENEMIES; x++) {

    Enemy *enemy = &enemies[x];

    if (enemy->getEnabled()) {

      int16_t dx = px - enemy->getX();
      int16_t dy = py - enemy->getY();

      uint8_t picX = 255;
      uint8_t picY = 155;

      uint8_t const * mask = arrow_TL_mask;
      uint8_t const * image = arrow_TL;
      
      if (player.getY() - dy < -9) {

        if (player.getX() - dx < -1) {

          picX = 0;
          picY = 0;
          
        }
        else if (player.getX() - dx > 123) {

          picX = 123;
          picY = 0;
          image = arrow_TR;
          mask = arrow_TR_mask;

        }
        else {

          picX = player.getX() - dx + 1;
          picY = 0;
          image = arrow_TM;
          mask = arrow_TM_mask;

        }

      }

      else if (player.getY() - dy > 50) { 

        if (player.getX() - dx < -1) {

          picX = 0;
          picY = 50;
          image = arrow_BL;
          mask = arrow_BL_mask;
          
        }
        else if (player.getX() - dx > 123) {

          picX = 123;
          picY = 50;
          image = arrow_BR;
          mask = arrow_BR_mask;

        }
        else {

          picX = player.getX() - dx + 1;
          picY = 51;
          image = arrow_BM;
          mask = arrow_BM_mask;

        }

      }
      else {

        if (player.getX() - dx < -1) {

          picX = 0;
          picY = player.getY() - dy;
          image = arrow_ML;
          mask = arrow_ML_mask;
          
        }
        else if (player.getX() - dx > 123) {

          picX = 123;
          picY = player.getY() - dy;
          image = arrow_MR;
          mask = arrow_MR_mask;

        }

      }

      if (picX != 255) {

        arduboy.drawCompressedMirror(picX, picY, mask, BLACK, false);
        arduboy.drawCompressedMirror(picX, picY, image, WHITE, false);

      }

    }

  }

}
#endif


// ------------------------------------------------------------------------------------------
//  Render then entry / exit rectangle ..
//
void renderEntryRectangle() {

  if (gameState == GameState::LevelEntryAnimation || gameState == GameState::LevelExitAnimation) {

    arduboy.drawRect(introRect, introRect, 128 - (introRect * 2), 55 - (introRect * 2), BLACK);
    arduboy.drawHorizontalDottedLine(0, 128, introRect);
    arduboy.drawHorizontalDottedLine(0, 128, 54 - introRect);
    arduboy.drawVerticalDottedLine(0, 64, introRect);
    arduboy.drawVerticalDottedLine(0, 64, 127 - introRect);

    if( gameState == GameState::LevelEntryAnimation) {

      for (int8_t x = introRect - 1; x >= 0; x--) {

        arduboy.drawRect(x, x, 127 - (x * 2) + 1, 54 - (x * 2) + 1, BLACK);

      }
      introRect--;

      if (introRect == -1) gameState = GameState::LevelFlash;

    }
    else {

      for (int8_t x = 0; x < introRect; x++) {

        arduboy.drawRect(x, x, 127 - (x * 2) + 1, 54 - (x * 2) + 1, BLACK);

      }
      introRect++;

      // Game over, restart level or next level ?
      if (introRect == LEVEL_ANIMATION_BANNER_WIDTH) gameState = player.getNextState();

    }

  }
  else if (gameState == GameState::NextLevel || gameState == GameState::RestartLevel || gameState == GameState::GameOver) {

    if(gameState == GameState::RestartLevel) {

      arduboy.drawCompressedMirror(42, 25, tryAgain, WHITE, false);

    }
    else if(gameState == GameState::GameOver) {

      arduboy.drawCompressedMirror(43, 25, gameOver, WHITE, false);

    }
    else {

      uint8_t levelNumber = level.getLevelNumber();
      Sprites::drawOverwrite(72, 25, numbers, levelNumber / 100);
      levelNumber = levelNumber - (levelNumber / 100) * 100;
      Sprites::drawOverwrite(77, 25, numbers, levelNumber / 10);
      Sprites::drawOverwrite(82, 25, numbers, levelNumber % 10);

      arduboy.drawCompressedMirror(43, 25, levelChange, WHITE, false);

    }

    arduboy.drawHorizontalDottedLine(41, 87, 22);
    arduboy.drawHorizontalDottedLine(41, 87, 32);
  
  }

}


// ------------------------------------------------------------------------------------------
//  Render the scorebaord ..
//
void renderScoreboard() {

  uint16_t score = player.getScore();
  arduboy.drawCompressedMirror(0, 58, score_sc, WHITE, false);
  Sprites::drawOverwrite(29, 58, numbers, 0);
  Sprites::drawOverwrite(34, 58, numbers, score / 10000);
  score = score - (score / 10000) * 10000;
  Sprites::drawOverwrite(39, 58, numbers, score / 1000);
  score = score - (score / 1000) * 1000;
  Sprites::drawOverwrite(44, 58, numbers, score / 100);
  score = score - (score / 100) * 100;
  Sprites::drawOverwrite(49, 58, numbers, score / 10);
  Sprites::drawOverwrite(54, 58, numbers, score % 10);

  uint8_t menLeft = player.getMen();
  arduboy.drawCompressedMirror(64, 58, men_sc, WHITE, false);
  Sprites::drawOverwrite(82, 58, numbers, menLeft / 10);
  Sprites::drawOverwrite(87, 58, numbers, menLeft % 10);

  if (gameState == GameState::LevelPlay) {

    uint8_t goldLeft = level.getGoldLeft();
    arduboy.drawCompressedMirror(96, 58, gold_sc, WHITE, false);
    Sprites::drawOverwrite(118, 58, numbers, goldLeft / 10);
    Sprites::drawOverwrite(123, 58, numbers, goldLeft % 10);

  }
  else {

    uint8_t levelNumber = level.getLevelNumber();
    arduboy.drawCompressedMirror(96, 58, level_sc, WHITE, false);
    Sprites::drawOverwrite(113, 58, numbers, levelNumber / 100);
    levelNumber = levelNumber - (levelNumber / 100) * 100;
    Sprites::drawOverwrite(118, 58, numbers, levelNumber / 10);
    Sprites::drawOverwrite(123, 58, numbers, levelNumber % 10);

  }

}
