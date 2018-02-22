#include "src/utils/Arduboy2Ext.h"
#include <ArduboyTones.h>
#include "src/utils/Utils.h"
#include "src/utils/Enums.h"
#include "src/images/Images.h"
#include "src/levels/Levels.h"
#include "src/levels/Level.h"
#include "src/utils/Queue.h"

Arduboy2Ext arduboy;
ArduboyTones sound(arduboy.audio.enabled);

Player player = {20, 35, PlayerStance::StandingStill, 0, 0};
Enemy enemies[NUMBER_OF_ENEMIES];

Level level;



// uint8_t levelData[level.getWidth()][level.getHeight()];
bool flashPlayer = false;


GameState gameState = GameState::Intro;
int8_t bannerStripe = -30;
int8_t introRect = 0;

Queue<Hole, 10> holes;


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
  arduboy.audio.begin();
  arduboy.setFrameRate(90);
  arduboy.initRandomSeed();

}


// --------------------------------------------------------------------------------------
//  Main Loop ..
//
void loop() {

  switch (gameState) {

    case GameState::Intro:
      Intro();
      break;

    case GameState::LevelInit:
      introRect = 28;
      gameState = GameState::LevelEntryAnimation;
      /* break; Drop through to next case */

    case GameState::LevelEntryAnimation:
      LevelPlay();
      break;

    case GameState::LevelFlash:
      LevelPlay();
      break;

    case GameState::LevelPlay:
      LevelPlay();
      break;

    case GameState::LevelExitInit:
      introRect = 0;
      gameState = GameState::LevelExitAnimation;
      /* break; Drop through to next case */

    case GameState::LevelExitAnimation:
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



  if (arduboy.justPressed(A_BUTTON))  { 
    
    gameState = GameState::LevelInit; 
    level.loadLevel(&player, enemies); 
    
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
  //arduboy.clear();

  if (gameState == GameState::LevelPlay) {

    uint8_t nearestX = getNearestX();
    uint8_t nearestY = getNearestY();
    LevelElement nearest = level.getLevelData(nearestX, nearestY);


    // Detect next movements for player and enemies ..

    playerMovements(nearestX, nearestY, nearest);

    for (uint8_t x = 0; x < NUMBER_OF_ENEMIES; x++) {

      Enemy *enemy = &enemies[x];

      if (enemy->enabled) {

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

      if ((player.xDelta != 0 || player.yDelta != 0 || level.getXOffsetDelta() != 0 || level.getYOffsetDelta() != 0)) {

        player.stance = getNextStance(player.stance);

      }


      // Update enemy stances ..

      for (uint8_t x = 0; x < NUMBER_OF_ENEMIES; x++) {

        Enemy *enemy = &enemies[x];

        if (enemy->enabled && enemy->escapeHole == EscapeHole::None) {

          switch (enemy->stance) {

            case PlayerStance::Rebirth_1 ... PlayerStance::Rebirth_3:
              
              enemy->stance = getNextStance(enemy->stance);
              break;

            default:
              
              if (enemy->xDelta != 0 || enemy->yDelta != 0) {

                enemy->stance = getNextStance(enemy->stance);

              }

              break;

          }

        }

      }

    }


    // Move player ..

    player.x = player.x + player.xDelta;
    player.y = player.y + player.yDelta;
    level.setXOffset(level.getXOffset() + level.getXOffsetDelta());
    level.setYOffset(level.getYOffset() + level.getYOffsetDelta());


    // Move enemies ..

    for (uint8_t x = 0; x < NUMBER_OF_ENEMIES; x++) {

      Enemy *enemy = &enemies[x];

      if (enemy->enabled) {

        enemy->x = enemy->x + enemy->xDelta;
        enemy->y = enemy->y + enemy->yDelta;

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

                if (enemy->enabled && (hole.x * GRID_SIZE) == enemy->x && (hole.y * GRID_SIZE) == enemy->y) {

                  LevelPoint startingLocation = level.getReentryPoint(random(0, 4));

                  enemy->x = (startingLocation.x * GRID_SIZE);
                  enemy->y = (startingLocation.y * GRID_SIZE);
                  enemy->stance = PlayerStance::Rebirth_1;
                  enemy->escapeHole = EscapeHole::None;
                  enemy->yDelta = 0;
                  enemy->yDelta = 0;

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

    if (arduboy.justPressed(A_BUTTON)) { gameState = GameState::LevelPlay;  }

  }

  arduboy.display(CLEAR_BUFFER);

}
