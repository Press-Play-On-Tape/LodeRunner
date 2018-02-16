#include "src/utils/Arduboy2Ext.h"
#include <ArduboyTones.h>
#include "Utils.h"
#include "Enums.h"
#include "Images.h"
#include "levels.h"

Arduboy2Ext arduboy;
ArduboyTones sound(arduboy.audio.enabled);



//Player player = {60, 35};
//Level level = {-60, -55};
Player player = {20, 35};
Enemy enemies[NUMBER_OF_ENEMIES];

Level level = {0, -55};


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


uint8_t getNearestX(int8_t margin = 5);
uint8_t getNearestY(int8_t margin = 5);


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


}



// --------------------------------------------------------------------------------------
//  Main Loop ..
//
void loop() {

  if (!(arduboy.nextFrame())) return;
  arduboy.pollButtons();
  arduboy.clear();


  uint8_t nearestX = getNearestX();
  uint8_t nearestY = getNearestY();
  LevelElement nearest = getLevelData(nearestX, nearestY);

  playerMovements(nearestX, nearestY, nearest);

  for (uint8_t x = 0; x < NUMBER_OF_ENEMIES; x++) {

    Enemy *enemy = &enemies[x];

    if (enemy->enabled) {

      enemyMovements(enemy);

    }

  }

  if (arduboy.everyXFrames(2) && (player.xDelta != 0 || player.yDelta != 0 || level.xOffsetDelta != 0 || level.yOffsetDelta != 0)) {

    switch (player.stance) {

      case PlayerStance::Swinging_Left4:
        player.stance = PlayerStance::Swinging_Left1;
        break;

      case PlayerStance::Swinging_Left3 ... PlayerStance::Swinging_Left1:
        player.stance--;
        break;

      case PlayerStance::Climbing_Down2:
        player.stance = PlayerStance::Climbing_Down1;
        break;

      case PlayerStance::Climbing_Down1:
        player.stance = PlayerStance::Climbing_Down2;
        break;

      case PlayerStance::Running_Left4:
        player.stance = PlayerStance::Running_Left1;
        break;

      case PlayerStance::Running_Left3 ... PlayerStance::Running_Left1:
        player.stance--;
        break;

      case PlayerStance::Running_Right1 ... PlayerStance::Running_Right3:
        player.stance++;
        break;

      case PlayerStance::Running_Right4:
        player.stance = PlayerStance::Running_Right1;
        break;

      case PlayerStance::Climbing_Up1:
        player.stance = PlayerStance::Climbing_Up2;
        break;

      case PlayerStance::Climbing_Up2:
        player.stance = PlayerStance::Climbing_Up1;
        break;

      case PlayerStance::Swinging_Right1 ... PlayerStance::Swinging_Right3:
        player.stance++;
        break;

      case PlayerStance::Swinging_Right4:
        player.stance = PlayerStance::Swinging_Right1;
        break;

      default: break;

    }

  }

// -----------------------------------------------------------------------------------

  for (uint8_t y = 0; y < height; y++) {

    for (uint8_t x = 0; x < width * 2; x++) {

      if (level.xOffset + (x * GRID_SIZE) > -GRID_SIZE && level.xOffset + (x * GRID_SIZE) < 128 && level.yOffset + (y * GRID_SIZE) > -GRID_SIZE && level.yOffset + (y * GRID_SIZE) < 64) {

        LevelElement element = (LevelElement)getLevelData(x, y);
        
        switch (element) {

          case LevelElement::Brick ... LevelElement::Gold:
            arduboy.drawCompressedMirror(level.xOffset + (x * GRID_SIZE), level.yOffset + (y * GRID_SIZE), levelElements[(uint8_t)element - 1], WHITE, false);
            break;

          case LevelElement::Brick_1 ... LevelElement::Brick_4:
            arduboy.drawCompressedMirror(level.xOffset + (x * GRID_SIZE), level.yOffset + (y * GRID_SIZE) - GRID_SIZE, levelElements[(uint8_t)element - 1], WHITE, false);
            break;

          default:
            break;

        }

      }

    }

  }


  // Draw player ..
  {

    boolean flip = ((int8_t) player.stance < 0);
    arduboy.drawCompressedMirror(player.x, player.y, men[absT((int8_t)player.stance)], WHITE, flip);

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








 //arduboy.setCursor(0,0);
//  arduboy.print((int8_t)nearest);
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



  player.x = player.x + player.xDelta;
  player.y = player.y + player.yDelta;
  level.xOffset = level.xOffset + level.xOffsetDelta;
  level.yOffset = level.yOffset + level.yOffsetDelta;





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

  arduboy.display();


}
