#include "src/utils/Arduboy2Ext.h"
#include <ArduboyTones.h>
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
uint8_t menuSelect = 0;
Queue<Hole, 10> holes;


// --------------------------------------------------------------------------------------
//  Forward declarations ..
//
uint8_t getNearestX(int8_t margin = HALF_GRID_SIZE);
uint8_t getNearestY(int8_t margin = HALF_GRID_SIZE);

#ifdef INC_ARROWS
Direction getDirection_8Directions(int8_t xDiff, int8_t yDiff);
#endif

// --------------------------------------------------------------------------------------
//  Setup ..
//
void setup() {

  arduboy.boot();
  arduboy.flashlight();
  arduboy.systemButtons();
  arduboy.audio.begin();
  arduboy.setFrameRate(90);
  arduboy.initRandomSeed();
  EEPROM_Utils::initEEPROM(false);
  EEPROM_Utils::getSavedGameData(&level, &player);

  player.setX(20);
  player.setY(35);
  player.setStance(PlayerStance::StandingStill);
  player.setNextState(GameState::Intro);

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
      EEPROM_Utils::saveGameData(&level, &player);
      LevelPlay();
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
  //arduboy.clear();

  arduboy.drawCompressedMirror(0, 4, banner, WHITE, false);

  /* Pharap .. uncomment from here 
  
  if (bannerStripe < 52) arduboy.fillRect(0, bannerStripe, WIDTH, 2, BLACK);
  if (bannerStripe < 48) arduboy.fillRect(0, bannerStripe + 4, WIDTH, 2, BLACK);
  if (bannerStripe < 44) arduboy.fillRect(0, bannerStripe + 8, WIDTH, 2, BLACK);
  if (bannerStripe < 40) arduboy.fillRect(0, bannerStripe + 12, WIDTH, 2, BLACK);
  bannerStripe++;
  if (bannerStripe > 66) bannerStripe = -30;

  Pharap to here .. */

  arduboy.display(CLEAR_BUFFER);

  if (arduboy.justPressed(A_BUTTON))  { gameState = (EEPROM_Utils::getLevelNumber() == 1 ? GameState::LevelInit : GameState::GameSelect); }

}



// --------------------------------------------------------------------------------------
//  Display intro banner ..
//
void GameSelect() {

  if (!(arduboy.nextFrame())) return;
  arduboy.pollButtons();

  arduboy.drawCompressedMirror(38, 24, menuOption, WHITE, false);
  arduboy.drawCompressedMirror(31, (menuSelect == 0 ? 24 : 34), menuArrow, WHITE, false);

  for (uint8_t x = 0; x < WIDTH; x = x + 10) {
  
    arduboy.drawCompressedMirror(x, 0, brick, WHITE, false);
    arduboy.drawCompressedMirror(x, 55, brick, WHITE, false);

  }

  arduboy.display(CLEAR_BUFFER);

  if (arduboy.justPressed(UP_BUTTON) && menuSelect == 1)    { menuSelect = 0; }
  if (arduboy.justPressed(DOWN_BUTTON) && menuSelect == 0)  { menuSelect = 1; }

  if (arduboy.justPressed(A_BUTTON)) {
    
    if (menuSelect == 0) { EEPROM_Utils::getSavedGameData(&level, &player); }
    if (menuSelect == 1) { EEPROM_Utils::initEEPROM(true); EEPROM_Utils::getSavedGameData(&level, &player); }

     gameState = GameState::LevelInit; 
     
  }

}


// --------------------------------------------------------------------------------------
//  Play the current level ..  
//
//  If 'play' is false, play is halted and the player flashes waiting on a keypress.
//
void LevelPlay() {

  if (!(arduboy.nextFrame())) return;
  arduboy.pollButtons();



  if (gameState == GameState::LevelPlay) {

    uint8_t nearestX = getNearestX();
    uint8_t nearestY = getNearestY();
    LevelElement nearest = level.getLevelData(nearestX, nearestY);


    // Detect next movements for player and enemies ..

    playerMovements(nearestX, nearestY, nearest);

    clearEnemyMovementPositions(enemies);
    for (uint8_t x = 0; x < NUMBER_OF_ENEMIES; x++) {

      Enemy *enemy = &enemies[x];

      if (enemy->getEnabled()) {

        enemyMovements(enemy);

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


      // Update enemy stances ..

      for (uint8_t x = 0; x < NUMBER_OF_ENEMIES; x++) {

        Enemy *enemy = &enemies[x];

        if (enemy->getEnabled() && enemy->getEscapeHole() == EscapeHole::None) {

          switch (enemy->getStance()) {

            case PlayerStance::Rebirth_1 ... PlayerStance::Rebirth_3:
              
              enemy->setStance(getNextStance(enemy->getStance()));
              break;

            default:
              
              if (enemy->getXDelta() != 0 || enemy->getYDelta() != 0) {

                enemy->setStance(getNextStance(enemy->getStance()));

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

    if (player.getY() > (level.getHeight() * GRID_SIZE)) {

      gameState = GameState::LevelExitInit;
      player.setNextState(GameState::NextLevel);
      level.setLevelNumber(level.getLevelNumber() + 1);
      EEPROM_Utils::saveLevelNumber(level.getLevelNumber());

    } 


    // Move enemies ..

    for (uint8_t x = 0; x < NUMBER_OF_ENEMIES; x++) {

      Enemy *enemy = &enemies[x];

      if (enemy->getEnabled()) {

        enemy->setX(enemy->getX() + enemy->getXDelta());
        enemy->setY(enemy->getY() + enemy->getYDelta());

      }

    }


    // Are any of the enemies touching the player?

    for (uint8_t x = 0; x < NUMBER_OF_ENEMIES; x++) {

      Enemy *enemy = &enemies[x];

      if (enemy->getEnabled() && arduboy.collide(Rect {static_cast<int16_t>(enemy->getX()) + 2, static_cast<int16_t>(enemy->getY()) + 2, 6, 6}, Rect {static_cast<int16_t>(player.getX() - level.getXOffset()) + 2, static_cast<int16_t>(player.getY() - level.getYOffset()) + 2, 6, 6} )) {

        player.setMen(player.getMen() - 1);

        if (player.getMen() > 0) {

          gameState = GameState::LevelExitInit;
          player.setNextState(GameState::RestartLevel);

        }
        else {

          gameState = GameState::LevelExitInit;
          player.setNextState(GameState::GameOver);

        }

      }

    }


    // Update level details ..

    if (arduboy.everyXFrames(2)) {
      
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

            case 32:        
              level.setLevelData(hole.x, hole.y, LevelElement::Brick_Close_1);
              break;

            case 24:
              level.setLevelData(hole.x, hole.y, LevelElement::Brick_Close_2);
              break;

            case 16:
              level.setLevelData(hole.x, hole.y, LevelElement::Brick_Close_3);
              break;

            case 8:
              level.setLevelData(hole.x, hole.y, LevelElement::Brick_Close_4);
              break;

            case 1:

              // Have any of the enemies been trapped ?  If so, relocate them ..

              for (uint8_t x = 0; x < NUMBER_OF_ENEMIES; x++) {

                Enemy *enemy = &enemies[x];

                if (enemy->getEnabled() && (hole.x * GRID_SIZE) == enemy->getX() && (hole.y * GRID_SIZE) == enemy->getY()) {

                  LevelPoint startingLocation = level.getReentryPoint(random(0, 4));

                  enemy->setX(startingLocation.x * GRID_SIZE);
                  enemy->setY(startingLocation.y * GRID_SIZE);
                  enemy->setStance( PlayerStance::Rebirth_1);
                  enemy->setEscapeHole(EscapeHole::None);
                  enemy->setXDelta(0);
                  enemy->setYDelta(0);

                }

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

    if (arduboy.justPressed(A_BUTTON)) { 

      switch (gameState) {

        case GameState::NextLevel:
          gameState = GameState::LevelInit;  
          break;

        case GameState::RestartLevel:
          gameState = GameState::LevelInit;  
          break;

        case GameState::GameOver:
          gameState = GameState::Intro;  
          break;

        default:
          gameState = GameState::LevelPlay;
          break;

      }  
      
    }

  }

  arduboy.display(CLEAR_BUFFER);

}
