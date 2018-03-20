#include "src/utils/Arduboy2Ext.h"
#include <ArduboyTones.h>
#include "src/images/sounds.h"

#include "src/utils/Utils.h"
#include "src/utils/Enums.h"
#include "src/images/Images.h"
#include "src/levels/Levels.h"
#include "src/levels/Level.h"
#include "src/utils/Queue.h"
#include "src/utils/EEPROM_Utils.h"
#include "src/characters/Player.h"
#include "src/characters/Enemy.h"

Arduboy2Ext arduboy;
ArduboyTones sound(arduboy.audio.enabled);

Player player;
Enemy enemies[NUMBER_OF_ENEMIES];

Level level;


bool flashPlayer = false;

GameState gameState = GameState::Intro;
int8_t bannerStripe = -30;
int8_t introRect = 0;
Queue<Hole, 20> holes;

uint8_t suicide = 0;
uint8_t menuSelect = 0;
#ifdef INC_LEVEL_SELECTOR
uint8_t menuLevelSelect = LEVEL_OFFSET + 1;
#endif


// --------------------------------------------------------------------------------------
//  Forward declarations ..
//
uint8_t getNearestX(int8_t margin = HALF_GRID_SIZE);
uint8_t getNearestY(int8_t margin = HALF_GRID_SIZE);


// --------------------------------------------------------------------------------------
//  Setup ..
//
void setup() {

  arduboy.boot();
  arduboy.flashlight();
  arduboy.systemButtons();
  arduboy.setFrameRate(25);
  arduboy.initRandomSeed();
  arduboy.audio.begin();

  EEPROM_Utils::initEEPROM(false);
  EEPROM_Utils::getSavedGameData(&level, &player);

  player.setX(20);
  player.setY(35);
  player.setStance(PlayerStance::StandingStill);
  player.setNextState(GameState::Intro);

  sound.tones(score);

  uint8_t gameNumber = EEPROM_Utils::getGameNumber();
  
  if (gameNumber < GAME_NUMBER) {

    if (gameNumber == 1) { gameState = GameState::CompleteGame1; }
    if (gameNumber == 2) { gameState = GameState::CompleteGame2; }

  }

}


// --------------------------------------------------------------------------------------
//  Main Loop ..
//
void loop() {

  switch (gameState) {

    case GameState::Intro:
      Intro();
      break;

    case GameState::GameSelect:
      GameSelect();
      break;

    case GameState::LevelInit:

      while (!holes.isEmpty()) holes.dequeue();
      level.loadLevel(&player, enemies); 
      introRect = 28;
      gameState = GameState::LevelEntryAnimation;
      /* break; Drop through to next case */

    case GameState::LevelEntryAnimation:
    case GameState::LevelFlash:
    case GameState::LevelPlay:
      LevelPlay();
      break;

    case GameState::LevelExitInit:
      introRect = 0;
      gameState = GameState::LevelExitAnimation;
      /* break; Drop through to next case */

    case GameState::LevelExitAnimation:
    case GameState::GameOver:
    case GameState::RestartLevel:
      LevelPlay();
      break;

    case GameState::NextLevel:
      player.incrementMen();
      EEPROM_Utils::saveGameData(&level, &player);
      LevelPlay();
      break;

    case GameState::CompleteGame1:
      CompleteGame(1);
      break;

    case GameState::CompleteGame2:
      CompleteGame(2);
      break;

    case GameState::NextGame:
      NextGame();
      break;

    default: break;

  }
  
}



// --------------------------------------------------------------------------------------
//  Display intro banner ..
//
void Intro() {

  if (!(arduboy.nextFrame())) return;
  arduboy.pollButtons();

  arduboy.drawCompressedMirror(0, 4, banner, WHITE, false);
  if (arduboy.justPressedButtons() & A_BUTTON)  { gameState = GameState::GameSelect; }

  arduboy.display(CLEAR_BUFFER);

}



// --------------------------------------------------------------------------------------
//  Display intro banner ..
//
void GameSelect() {

  if (!(arduboy.nextFrame())) return;
  arduboy.pollButtons();

  #ifdef INC_LEVEL_SELECTOR

  arduboy.drawCompressedMirror(38, 19, menuOption2, WHITE, false);
  switch (menuSelect) {

    case 0:
      arduboy.drawCompressedMirror(31, 19, menuArrow, WHITE, false);
      break;

    case 1:
      arduboy.drawCompressedMirror(31, 29, menuArrow, WHITE, false);
      break;

    case 2:
      arduboy.drawCompressedMirror(31, 39, menuArrow, WHITE, false);
      break;

  }
 

  uint8_t levelNumber = menuLevelSelect;
  Sprites::drawOverwrite(70, 39, numbers, levelNumber / 100);
  levelNumber = levelNumber - (levelNumber / 100) * 100;
  Sprites::drawOverwrite(75, 39, numbers, levelNumber / 10);
  Sprites::drawOverwrite(80, 39, numbers, levelNumber % 10);



  // Brick borders ..

  for (uint8_t x = 0; x < WIDTH; x = x + 10) {
  
    Sprites::drawOverwrite(x, 0, levelElementImgs, 1);
    Sprites::drawOverwrite(x, 55, levelElementImgs, 1);

  }


  // Selector control ..

  arduboy.display(CLEAR_BUFFER);
  uint8_t buttons = arduboy.justPressedButtons();

  if ((buttons & UP_BUTTON) && menuSelect > 0)                                         { menuSelect--; }
  if ((buttons & DOWN_BUTTON) && menuSelect < 2)                                       { menuSelect++; }

  if (menuSelect == 2) {
  
    if ((buttons & LEFT_BUTTON) && menuLevelSelect > LEVEL_OFFSET + 1)                 { menuLevelSelect--; }
    if ((buttons & RIGHT_BUTTON) && menuLevelSelect < LEVEL_OFFSET + LEVEL_COUNT)      { menuLevelSelect++; }

  }

  if (buttons & A_BUTTON)) {
    
    if (menuSelect == 0) { EEPROM_Utils::getSavedGameData(&level, &player); }
    if (menuSelect == 1) { EEPROM_Utils::initEEPROM(true); EEPROM_Utils::getSavedGameData(&level, &player); }
    if (menuSelect == 2) { EEPROM_Utils::initEEPROM(true); EEPROM_Utils::saveLevelNumber(menuLevelSelect); EEPROM_Utils::getSavedGameData(&level, &player); }

     gameState = GameState::LevelInit; 
     
  }

  #endif

  #ifndef INC_LEVEL_SELECTOR

  bool firstTime = EEPROM_Utils::getMen() == 5 && EEPROM_Utils::getLevelNumber() == 1;

  uint8_t menuOptionY = 24;
  uint8_t selectorY = 24;
  uint8_t const * menuOptionImg = menuOptionStart;

  if (firstTime) {

    selectorY = 24 + (menuSelect * 5);

  }
  else {

    menuOptionY = 19;
    menuOptionImg = menuOption;
    selectorY= 19 + (menuSelect * 10);

  }

  arduboy.drawCompressedMirror(38, menuOptionY, menuOptionImg, WHITE, false);
  arduboy.drawCompressedMirror(31, selectorY, menuArrow, WHITE, false);


  // Brick borders ..

  for (uint8_t x = 0; x < WIDTH; x = x + 10) {
  
    Sprites::drawOverwrite(x, 0, levelElementImgs, 1);
    Sprites::drawOverwrite(x, 55, levelElementImgs, 1);

  }

  arduboy.display(CLEAR_BUFFER);
  uint8_t buttons = arduboy.justPressedButtons();

  if (!firstTime) {

    if ((buttons & UP_BUTTON) && menuSelect > 0)     { menuSelect--; }
    if ((buttons & DOWN_BUTTON) && menuSelect < 1)   { menuSelect++; }

  }

  if (buttons & A_BUTTON) {
    
    if (menuSelect == 0) { EEPROM_Utils::getSavedGameData(&level, &player); gameState = GameState::LevelInit; }
    if (menuSelect == 1) { EEPROM_Utils::initEEPROM(true); EEPROM_Utils::getSavedGameData(&level, &player); gameState = GameState::LevelInit; }
     
  }

  #endif
  

}


// --------------------------------------------------------------------------------------
//  Play the current level ..  
//
//  If 'play' is false, play is halted and the player flashes waiting on a keypress.
//
void LevelPlay() {

  if (!(arduboy.nextFrame())) return;
  arduboy.pollButtons();

  uint8_t nearestX = getNearestX();
  uint8_t nearestY = getNearestY();


  if (gameState == GameState::LevelPlay) {

    LevelElement nearest = level.getLevelData(nearestX, nearestY);


    // Detect next movements for player and enemies ..

    playerMovements(nearestX, nearestY, nearest);


    if (arduboy.everyXFrames(2)) {

      clearEnemyMovementPositions(enemies);
      for (uint8_t x = 0; x < NUMBER_OF_ENEMIES; x++) {

        Enemy *enemy = &enemies[x];

        if (enemy->getEnabled()) {

          enemyMovements(enemy);

        }

      }

    }

  }


  // Render the screen ..

  renderScreen();


  // Update the player and enemy stance, positions, etc ..

  if (gameState == GameState::LevelPlay) {



    // Update player stance ..

    if (arduboy.everyXFrames(2)) {

      if ((player.getXDelta() != 0 || player.getYDelta() != 0 || level.getXOffsetDelta() != 0 || level.getYOffsetDelta() != 0)) {

        player.setStance(getNextStance(player.getStance()));

      }
    
    }
    if (arduboy.everyXFrames(4)) {


      // Update enemy stances ..

      for (uint8_t x = 0; x < NUMBER_OF_ENEMIES; x++) {

        Enemy *enemy = &enemies[x];
        PlayerStance stance = enemy->getStance();

        if (enemy->getEnabled() && enemy->getEscapeHole() == EscapeHole::None) {

          switch (stance) {

            case PlayerStance::Rebirth_1 ... PlayerStance::Rebirth_3:
              
              enemy->setStance(getNextStance(stance));
              break;

            default:
              
              if (enemy->getXDelta() != 0 || enemy->getYDelta() != 0) {

                enemy->setStance(getNextStance(stance));

              }

              break;

          }

        }

      }

    }


    // Move player ..

    player.setX(player.getX() + player.getXDelta());
    player.setY(player.getY() + player.getYDelta());
    level.setXOffset(level.getXOffset() + level.getXOffsetDelta());
    level.setYOffset(level.getYOffset() + level.getYOffsetDelta());


    // If the player has gone off the top of the screen .. level over!

    LevelElement current = level.getLevelData(getNearestX(), getNearestY());

    if (player.getY() == 0 && current == LevelElement::Ladder) {

      uint8_t levelNumber = level.getLevelNumber() + 1;

      gameState = GameState::LevelExitInit;
      level.setLevelNumber(levelNumber);
      EEPROM_Utils::saveLevelNumber(level.getLevelNumber());

      if (levelNumber > LEVEL_OFFSET + LEVEL_COUNT) {
        player.incrementMen();
        EEPROM_Utils::setGameNumber(EEPROM_Utils::getGameNumber() + 1);
        EEPROM_Utils::saveGameData(&level, &player);
        player.setNextState(GameState::NextGame);
      }
      else {
        player.setNextState(GameState::NextLevel);
      }

      sound.tones(levelComplete); 

    } 


    // Move enemies ..

    if (arduboy.everyXFrames(2)) {

      for (uint8_t x = 0; x < NUMBER_OF_ENEMIES; x++) {

        Enemy *enemy = &enemies[x];

        if (enemy->getEnabled()) {

          enemy->setX(enemy->getX() + enemy->getXDelta());
          enemy->setY(enemy->getY() + enemy->getYDelta());

        }


        // Are any of the enemies touching the player?

        if (enemy->getEnabled() && arduboy.collide(Rect {static_cast<int16_t>(enemy->getX()) + 2, static_cast<int16_t>(enemy->getY()) + 2, 6, 6}, Rect {static_cast<int16_t>(player.getX() - level.getXOffset()) + 2, static_cast<int16_t>(player.getY() - level.getYOffset()) + 2, 6, 6} )) {

          playerDies();

        }

      }


      // Update level details ..
      
      for (uint8_t y = 0; y < level.getHeight(); y++) {

        for (uint8_t x = 0; x < level.getWidth() * 2; x++) {

          LevelElement element = (LevelElement)level.getLevelData(x, y);
          
          switch (element) {

            case LevelElement::Brick_1 ... LevelElement::Brick_4:
              element++;
              level.setLevelData(x, y, element);
              break;

            default:
              break;

          }

        }

      }

    }


    // Do any holes need to be filled in ?

    if (!holes.isEmpty()) {

      for (uint8_t x = 0; x < holes.getCount(); x++) {

        Hole &hole = holes.operator[](x);

        if (hole.countDown > 0) {

          hole.countDown--;

          switch (hole.countDown) {

            case HOLE_FILL_4:        
              level.setLevelData(hole.x, hole.y, LevelElement::Brick_Close_1);
              break;

            case HOLE_FILL_3:
              level.setLevelData(hole.x, hole.y, LevelElement::Brick_Close_2);
              break;

            case HOLE_FILL_2:
              level.setLevelData(hole.x, hole.y, LevelElement::Brick_Close_3);
              break;

            case HOLE_FILL_1:
              level.setLevelData(hole.x, hole.y, LevelElement::Brick_Close_4);
              break;

            case 1:


              // Have any of the enemies been trapped ?  If so, relocate them ..

              for (uint8_t x = 0; x < NUMBER_OF_ENEMIES; x++) {

                Enemy *enemy = &enemies[x];

                if (enemy->getEnabled() && (hole.x * GRID_SIZE) == enemy->getX() && (hole.y * GRID_SIZE) == enemy->getY()) {

                  LevelPoint reentryPoint = level.getNextReentryPoint();
                  enemy->setX(reentryPoint.x * GRID_SIZE);
                  enemy->setY(reentryPoint.y * GRID_SIZE);
                  enemy->setStance( PlayerStance::Rebirth_1);
                  enemy->setEscapeHole(EscapeHole::None);
                  enemy->setXDelta(0);
                  enemy->setYDelta(0);

                }

              }


              // What about the player ?

              if ( hole.x == nearestX && hole.y == nearestY ) {

                  playerDies();

              }

              level.setLevelData(hole.x, hole.y, LevelElement::Brick);
              break;

            default: break;

          }

        }

      }


      // Burn any holes that have been filled in from the queue ..

      while (true) {
        
        Hole &hole = holes.peek();

        if (hole.countDown == 1) {

          holes.dequeue();

          if (holes.isEmpty()) { break; }

        }
        else {

          break;

        }

      }

    }

  }
  else {


    // We are not playing so wait for a key press to continue the game ..

    uint8_t buttons = arduboy.justPressedButtons();

    if (buttons > 0) { 

      switch (gameState) {

        case GameState::NextGame:
          break;

        case GameState::NextLevel:
        case GameState::RestartLevel:
          gameState = GameState::LevelInit;  
          break;

        case GameState::GameOver:
          gameState = GameState::Intro;  
          break;

        case GameState::LevelExitAnimation:
          gameState = player.getNextState();
          break;

        default:
          arduboy.clearButtonState();
          gameState = GameState::LevelPlay;
          break;

      }  
      
    }

  }


  // Show level clear indicator?

  if (suicide == 0) {
    arduboy.setRGBled(0, (flashPlayer && level.getGoldLeft() == 0 && gameState == GameState::LevelPlay ? 32 : 0), 0);
  }

  arduboy.display(CLEAR_BUFFER);

}


// --------------------------------------------------------------------------------------
//  Our player is dead ..
//
void playerDies() {

  player.setMen(player.getMen() - 1);
  gameState = GameState::LevelExitInit;

  if (player.getMen() > 0) {

    player.setNextState(GameState::RestartLevel);

  }
  else {

    player.setNextState(GameState::GameOver);

  }

  sound.tones(dead); 

}



// --------------------------------------------------------------------------------------
//  Display 'Next Game' banner ..
//
void NextGame() {

  arduboy.drawCompressedMirror(20, 23, loadNextGame, WHITE, false);
  arduboy.display(CLEAR_BUFFER);

}


// --------------------------------------------------------------------------------------
//  Display 'complete game' banner ..
//
void CompleteGame(uint8_t level) {

  arduboy.drawCompressedMirror(19, 20, completeGame, WHITE, false);
  arduboy.drawCompressedMirror(71, 35, (level == 1 ? completeGame1 : completeGame2), WHITE, false);
  arduboy.display(CLEAR_BUFFER);

}