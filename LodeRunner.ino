#include "src/utils/Arduboy2Ext.h"
#include <ArduboyTones.h>
#include "Utils.h"
#include "Enums.h"
#include "Images.h"
#include "levels.h"
#include "src/utils/QueueArray.h"

Arduboy2Ext arduboy;
ArduboyTones sound(arduboy.audio.enabled);

Player player = {20, 35, PlayerStance::StandingStill, 0, 0};
Enemy enemies[NUMBER_OF_ENEMIES];

Level level = {0, -55, 0, 0};


const uint8_t width = 14;
const uint8_t height = 11;

const uint8_t PROGMEM Level1[] = {
    // 14 x 7
    0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, //0
    0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, //1
    0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x04, 0x43, 0x00, 0x00, 0x00, 0x00, //2
    0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x04, 0x40, 0x03, 0x00, 0x00, 0x00, 0x00, //3
    0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, //4
    0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x03, 0x11, 0x11, 0x11, 0x11, //5
    0x00, 0x44, 0x00, 0x00, 0x03, 0x00, 0x00, 0x44, 0x44, 0x43, 0x00, 0x00, 0x00, 0x00, //6
    0x04, 0x00, 0x31, 0x11, 0x11, 0x10, 0x44, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, //7
    0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x44, 0x00, 0x01, 0x11, 0x11, 0x11, 0x13, //8 
    0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x04, 0x44, 0x44, 0x00, 0x00, 0x00, 0x00, 0x03, //9
    0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x10, 0x00, 0x00, 0x11, 0x11, 0x11, 0x11, 0x11, //10
//    0     2     4     6     8     10    12    14    16    18    20    22    24    26
};

uint8_t levelData[width][height];
bool flashPlayer = false;

uint8_t getNearestX(int8_t margin = 5);
uint8_t getNearestY(int8_t margin = 5);

GameState gameState = GameState::Intro;
int8_t bannerStripe = -20;

QueueArray<Hole> holes;


// --------------------------------------------------------------------------------------
//  Setup ..
//
void setup()
{

  arduboy.boot();
  arduboy.flashlight();
  arduboy.systemButtons();
  arduboy.audio.begin();
  arduboy.setFrameRate(90);
  arduboy.initRandomSeed();


  for (uint8_t y = 0; y < height; y++) {

    for (uint8_t x = 0; x < width; x++) {

      levelData[x][y] = pgm_read_byte(&Level1[(y * width) + x]);

    }

  }

  for (uint8_t x = 0; x < NUMBER_OF_ENEMIES; x++) {

    enemies[x].x = 0;

  }


  enemies[0].x = 70;
  enemies[0].y = 90;
  enemies[0].enabled = true;

  // Hole hole = {2,2,255};
  // holes.push(hole);
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
      LevelPlay(false);
      break;

    case GameState::LevelPlay:
      LevelPlay(true);
      break;

      default: break;

  }


}




void Intro() {

  if (!(arduboy.nextFrame())) return;
  arduboy.pollButtons();
  arduboy.clear();

  arduboy.drawCompressedMirror(0, 0, banner, WHITE, false);
  arduboy.fillRect(0, bannerStripe, WIDTH, 2, BLACK);
  arduboy.fillRect(0, bannerStripe + 4, WIDTH, 2, BLACK);
  arduboy.fillRect(0, bannerStripe + 8, WIDTH, 2, BLACK);
  // arduboy.fillRect(0, bannerStripe, WIDTH, 3, BLACK);
  // arduboy.fillRect(0, bannerStripe + 5, WIDTH, 3, BLACK);
  // arduboy.fillRect(0, bannerStripe + 10, WIDTH, 3, BLACK);
  bannerStripe = bannerStripe + 2;

  arduboy.display();



  if (arduboy.justPressed(A_BUTTON))  { gameState = GameState::LevelInit; }


}

void LevelPlay(boolean play) {

  if (!(arduboy.nextFrame())) return;
  arduboy.pollButtons();
  arduboy.clear();

  if (play) {

    uint8_t nearestX = getNearestX();
    uint8_t nearestY = getNearestY();
    LevelElement nearest = getLevelData(nearestX, nearestY);


    // Detect next movements for player and enemies ..
    
    playerMovements(nearestX, nearestY, nearest);

    for (uint8_t x = 0; x < NUMBER_OF_ENEMIES; x++) {

      Enemy *enemy = &enemies[x];

      if (enemy->enabled) {

        enemyMovements(enemy);

      }

    }

  }

// -----------------------------------------------------------------------------------

  renderScreen(play);








 arduboy.setCursor(0,0);
//  arduboy.print(queueSize());

//   arduboy.print(" ");
//   arduboy.print(nearestX);
//   arduboy.print(" ");
//   arduboy.print(nearestY);
  // arduboy.print("x");
  // arduboy.print(player.x);
  // arduboy.print(" ");
  // arduboy.print(level.xOffset);
  // arduboy.print(" y");
  // arduboy.print(player.y);
  // arduboy.print(" ");
  // arduboy.print(level.yOffset);
  // arduboy.print(" ");
  // arduboy.print((int8_t)player.stance);
//   arduboy.print(" ");


  if (play) {


    // Update stances ..

    if (arduboy.everyXFrames(2)) {

      if ((player.xDelta != 0 || player.yDelta != 0 || level.xOffsetDelta != 0 || level.yOffsetDelta != 0)) {

        player.stance = getNextStance(player.stance);

      }

      // Move enemies ..

      for (uint8_t x = 0; x < NUMBER_OF_ENEMIES; x++) {

        Enemy *enemy = &enemies[x];

        if (enemy->enabled && enemy->escapeHole == EscapeHole::None && (enemy->xDelta != 0 || enemy->yDelta != 0)) {

          enemy->stance = getNextStance(enemy->stance);

        }

      }

    }


    // Move player ..

    player.x = player.x + player.xDelta;
    player.y = player.y + player.yDelta;
    level.xOffset = level.xOffset + level.xOffsetDelta;
    level.yOffset = level.yOffset + level.yOffsetDelta;



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
      
      for (uint8_t y = 0; y < height; y++) {

        for (uint8_t x = 0; x < width * 2; x++) {

          LevelElement element = (LevelElement)getLevelData(x, y);
          
          switch (element) {

            case LevelElement::Brick_1 ... LevelElement::Brick_4:
              element++;
              setLevelData(x, y, element);
              break;

            default:
              break;

          }

        }

      }

    }

    if (!holes.isEmpty()) {
    
      uint8_t size = holes.count();

      for (uint8_t x = 0; x < size; x++) {

        Hole hole = holes.dequeue();

        if (hole.countDown > 0) {

          hole.countDown--;

          switch (hole.countDown) {

            case 32:
              setLevelData(hole.x, hole.y, LevelElement::Brick_Close_1);
              holes.enqueue(hole);
              break;

            case 24:
              setLevelData(hole.x, hole.y, LevelElement::Brick_Close_2);
              holes.enqueue(hole);
              break;

            case 18:
              setLevelData(hole.x, hole.y, LevelElement::Brick_Close_3);
              holes.enqueue(hole);
              break;

            case 8:
              setLevelData(hole.x, hole.y, LevelElement::Brick_Close_4);
              holes.enqueue(hole);
              break;

            case 1:
              setLevelData(hole.x, hole.y, LevelElement::Brick);
              break;

            default:
              holes.enqueue(hole);
              break;

          }

        }

      }

    }

  }



  if (!play) {

    if (arduboy.justPressed(A_BUTTON)) { gameState = GameState::LevelPlay; }

  }

  arduboy.display();

}
