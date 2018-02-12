#include "src/utils/Arduboy2Ext.h"
#include "src/utils/Stack.h"
#include <ArduboyTones.h>
#include "Enums.h"
#include "Images.h"

Arduboy2Ext arduboy;
ArduboyTones sound(arduboy.audio.enabled);

struct Player
{
  uint8_t x;
  uint8_t y;
  PlayerStance stance;
  int8_t xDelta;
  int8_t yDelta;
};

struct Level
{
  int16_t xOffset;
  int16_t yOffset;
  int8_t xOffsetDelta;
  int8_t yOffsetDelta;
};

//Player player = {60, 35};
//Level level = {-60, -55};
Player player = {20, 35};
Level level = {0, -55};

Stack<uint8_t, 10> playerStack;


const uint8_t width = 14;
const uint8_t height = 11;
const uint8_t gridSize = 10;
const uint8_t hSliderMax = 50;
const uint8_t hPerPixel = (width * 2 * gridSize) / hSliderMax;
const uint8_t hSliderWidth = (WIDTH * hSliderMax) / (width * 2 * gridSize) - 2;

const uint8_t vSliderMax = 53;
const uint8_t vPerPixel = (height * gridSize) / vSliderMax;
const uint8_t vSliderHeight = (HEIGHT * vSliderMax) / (height * gridSize) - 2;

const uint8_t PROGMEM Level1[] = {
    // 14 x 7
    0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, //0
    0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, //1
    0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x04, 0x43, 0x00, 0x00, 0x00, 0x00, //2
    0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x04, 0x40, 0x03, 0x00, 0x00, 0x00, 0x00, //3
    0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, //4
    0x11, 0x11, 0x11, 0x11, 0x13, 0x00, 0x00, 0x00, 0x00, 0x03, 0x11, 0x11, 0x11, 0x1114, //5
    0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x44, 0x44, 0x43, 0x00, 0x00, 0x00, 0x00, //6
    0x00, 0x44, 0x00, 0x00, 0x03, 0x00, 0x44, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, //7
    0x44, 0x00, 0x31, 0x11, 0x11, 0x10, 0x00, 0x44, 0x00, 0x01, 0x11, 0x11, 0x11, 0x13, //8
    0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x04, 0x44, 0x44, 0x00, 0x00, 0x00, 0x00, 0x03, //9
    0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x10, 0x00, 0x00, 0x11, 0x11, 0x11, 0x11, 0x11, //10
//    0     2     4     6     8     10    12    14    16    18    20    22    24    26
};

uint8_t levelData[width][height];



uint8_t getNearestX(int8_t margin = 5) {

  return (player.x - level.xOffset + margin) / gridSize;
  
}

uint8_t getNearestY(int8_t margin = 5) {

  return (player.y - level.yOffset + margin) / gridSize;
  
}

LevelElement getLevelData(uint8_t x, uint8_t y) {

  if ((x / 2) >= width || y >= height) return LevelElement::Brick;

  if (x % 2 == 0) {

    return static_cast<LevelElement>(levelData[x / 2][y] >> 4); 

  }
  else {

    return static_cast<LevelElement>(levelData[x / 2][y] & 0x0F); 

  }
      
}


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


  for (int y = 0; y < height; y++) {

    for (int x = 0; x < width; x++) {

      levelData[x][y] = pgm_read_byte(&Level1[(y * width) + x]);

    }

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


  uint8_t currPressed = arduboy.curButtonState();


  playerMovements(nearestX, nearestY, nearest, currPressed);


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

    }

  }

// -----------------------------------------------------------------------------------

  // for (int y = 0; y < height; y++) {

  //   for (int x = 0; x < width; x++) {

  //     Serial.print(levelData[x][y]);
  //     Serial.print(" ");

  //   }
  //   Serial.println(" ");

  // }
  //   Serial.println(" ");
  //   Serial.println(" ");


  for (uint8_t y = 0; y < height; y++) {

    for (uint8_t x = 0; x < width * 2; x++) {

// LevelElement d = (LevelElement)getLevelData(x, y);
// Serial.print((uint8_t)d); 
// Serial.print(" "); 

      if (level.xOffset + (x * gridSize) > -gridSize && level.xOffset + (x * gridSize) < 128 && level.yOffset + (y * gridSize) > -gridSize && level.yOffset + (y * gridSize) < 64) {

        switch ((LevelElement)getLevelData(x, y)) {
        //switch (d) {

          case LevelElement::Solid:
            arduboy.drawCompressedMirror(level.xOffset + (x * gridSize), level.yOffset + (y * gridSize), solid, WHITE, false);
            break;

          case LevelElement::Brick:
            arduboy.drawCompressedMirror(level.xOffset + (x * gridSize), level.yOffset + (y * gridSize), brick, WHITE, false);
            break;

          case LevelElement::Ladder:
            arduboy.drawCompressedMirror(level.xOffset + (x * gridSize), level.yOffset + (y * gridSize), ladder, WHITE, false);
            break;

          case LevelElement::Rail:
            arduboy.drawCompressedMirror(level.xOffset + (x * gridSize), level.yOffset + (y * gridSize), rail, WHITE, false);
            break;

          default:
            break;

        }

      }

    }
Serial.println(" "); 
Serial.println(" "); 

  }


  // Draw player ..
  {

    boolean flip = ((int8_t) player.stance < 0);
    arduboy.drawCompressedMirror(player.x, player.y, men[absT((int8_t)player.stance)], WHITE, flip);

  }


 
  // Draw foot and side bars ..

  arduboy.fillRect(0, 55, 128, 64, BLACK);
  drawHorizontalDottedLine(0, 128, 56);
//  arduboy.fillRect(119, 0, 9, 64, BLACK);



 // drawHorizontalDottedLine(0, 120, 56);
 // drawVerticalDottedLine(120, 0, 56);

  // // Draw horizontal scroll ..

  // uint8_t hOffset = (level.xOffset < 0 ? -level.xOffset / hPerPixel : 0);
  // arduboy.drawRect(67, 58, 54, 6, WHITE);
  // arduboy.drawRect(69 + hOffset, 60, hSliderWidth, 2, WHITE);
  // arduboy.drawRect(68, 59, 52, 4, BLACK);

  // // Draw vertical scroll ..

  // uint8_t vOffset = (level.yOffset < 0 ? -level.yOffset / hPerPixel : 0);
  // arduboy.drawRect(122, 0, 6, 57, WHITE);
  // arduboy.drawRect(124, 2 + vOffset, 2, vSliderHeight, WHITE);
  // arduboy.drawRect(123, 1, 4, 55, BLACK);

  // Draw scoreboard ..

  arduboy.drawCompressedMirror(0, 58, score, WHITE, false);
  arduboy.drawCompressedMirror(30, 57, digit_00, WHITE, false);
  arduboy.drawCompressedMirror(35, 57, digit_00, WHITE, false);
  arduboy.drawCompressedMirror(40, 57, digit_00, WHITE, false);
  arduboy.drawCompressedMirror(45, 57, digit_01, WHITE, false);
  arduboy.drawCompressedMirror(50, 57, digit_02, WHITE, false);
  arduboy.drawCompressedMirror(55, 57, digit_03, WHITE, false);








 arduboy.setCursor(0,0);
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



  arduboy.display();
}
