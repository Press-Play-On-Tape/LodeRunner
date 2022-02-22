#pragma once

#include "Arduboy2Ext.h"
#include "Enums.h"

#define EEPROM_START                  ((uint8_t *)175)
#define EEPROM_START_C1               ((uint8_t *)175)
#define EEPROM_START_C2               ((uint8_t *)176)
#define EEPROM_GAME_NO                ((uint8_t *)177)
#define EEPROM_LEVEL_NO               ((uint8_t *)178)
#define EEPROM_MEN_LEFT               ((uint8_t *)179)
#define EEPROM_SCORE                  ((uint16_t *)180)
#define EEPROM_GAME_NO_ORIG           ((uint8_t *)182)
#define EEPROM_LEVEL_NO_ORIG          ((uint8_t *)183)
#define EEPROM_MEN_LEFT_ORIG          ((uint8_t *)184)
#define EEPROM_SCORE_ORIG             ((uint16_t *)185)

class EEPROM_Utils {

  public: 

    EEPROM_Utils(){};
        
    static void initEEPROM(bool forceClear);
    static uint8_t getGameNumber();
    static uint8_t getLevelNumber();
    static uint8_t getMen();
    static void saveLevelNumber(uint8_t levelNumber);

    static void getSavedGameData(Level *level, Player *player);
    static void saveGameData(Level *level, Player *player);
    static void setGameNumber(uint8_t val);

};


/* ----------------------------------------------------------------------------
 *   Is the EEPROM initialised?
 *
 *   Looks for the characters 'L' and 'R' in the first two bytes of the EEPROM
 *   memory range starting from byte EEPROM_STORAGE_SPACE_START.  If not found,
 *   it resets the settings ..
 */
void EEPROM_Utils::initEEPROM(bool forceClear) {

  byte c1 = eeprom_read_byte(EEPROM_START_C1);
  byte c2 = eeprom_read_byte(EEPROM_START_C2);

  if (forceClear || c1 != 76 || c2 != 82) { // LR 76 82

    const uint16_t score = 0;
    eeprom_update_byte(EEPROM_START_C1, 76);
    eeprom_update_byte(EEPROM_START_C2, 82);

    eeprom_update_byte(EEPROM_GAME_NO, 1);
    eeprom_update_byte(EEPROM_LEVEL_NO, 1);
    eeprom_update_byte(EEPROM_MEN_LEFT, 5);

    eeprom_update_byte(EEPROM_GAME_NO_ORIG, 1);
    eeprom_update_byte(EEPROM_LEVEL_NO_ORIG, 1);
    eeprom_update_byte(EEPROM_MEN_LEFT_ORIG, 5);
    eeprom_update_word(EEPROM_SCORE, score);
    eeprom_update_word(EEPROM_SCORE_ORIG, score);

  }

}


/* -----------------------------------------------------------------------------
 *   Get the current level number. 
 */
uint8_t EEPROM_Utils::getGameNumber() {

  return eeprom_read_byte(EEPROM_GAME_NO);

}


/* -----------------------------------------------------------------------------
 *   Get the current level number. 
 */
uint8_t EEPROM_Utils::getLevelNumber() {

  return eeprom_read_byte(EEPROM_LEVEL_NO);

}


/* -----------------------------------------------------------------------------
 *   Get the number of men remaining. 
 */
uint8_t EEPROM_Utils::getMen() {

  return eeprom_read_byte(EEPROM_MEN_LEFT);

}

/* -----------------------------------------------------------------------------
 *   Save the current level number. 
 */
void EEPROM_Utils::saveLevelNumber(uint8_t levelNumber) {

  eeprom_update_byte(EEPROM_LEVEL_NO, levelNumber);

}


/* -----------------------------------------------------------------------------
 *   Get saved game data.
 */
void EEPROM_Utils::getSavedGameData(Level *level, Player *player) {

  int16_t score = 0;

  level->setLevelNumber(eeprom_read_byte(EEPROM_LEVEL_NO));
  player->setMen(eeprom_read_byte(EEPROM_MEN_LEFT));
  score = eeprom_read_word(EEPROM_SCORE);
  player->setScore(score);

}


/* -----------------------------------------------------------------------------
 *   Save game data.
 */
void EEPROM_Utils::saveGameData(Level *level, Player *player) {
 
  uint8_t levelNumber = level->getLevelNumber();
  eeprom_update_byte(EEPROM_LEVEL_NO, levelNumber);
  eeprom_update_byte(EEPROM_LEVEL_NO_ORIG, levelNumber);

  uint8_t menLeft = player->getMen();
  eeprom_update_byte(EEPROM_MEN_LEFT, menLeft);
  eeprom_update_byte(EEPROM_MEN_LEFT_ORIG, menLeft);

  uint16_t score = player->getScore();
  eeprom_update_word(EEPROM_SCORE, score);
  eeprom_update_word(EEPROM_SCORE_ORIG, score);

}


/* -----------------------------------------------------------------------------
 *   Save game number.
 */
void EEPROM_Utils::setGameNumber(uint8_t val) {

  eeprom_update_byte(EEPROM_GAME_NO, val);
  eeprom_update_byte(EEPROM_GAME_NO_ORIG, val);

}
