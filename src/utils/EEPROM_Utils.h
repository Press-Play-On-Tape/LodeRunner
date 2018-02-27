#pragma once

#include "Arduboy2Ext.h"
#include "Enums.h"

#define EEPROM_START                  EEPROM_STORAGE_SPACE_START + 175
#define EEPROM_START_C1               EEPROM_START
#define EEPROM_START_C2               EEPROM_START + 1
#define EEPROM_LEVEL_NO               EEPROM_START + 2
#define EEPROM_MEN_LEFT               EEPROM_START + 3
#define EEPROM_SCORE                  EEPROM_START + 4


class EEPROM_Utils {

  public: 

    EEPROM_Utils(){};
        
    static void initEEPROM(bool forceClear);
    static uint8_t getLevelNumber();
    static void saveLevelNumber(uint8_t levelNumber);

    static void getSavedGameData(Level *level, Player *player);
    static void saveGameData(Level *level, Player *player);


};


/* ----------------------------------------------------------------------------
 *   Is the EEPROM initialised?
 *
 *   Looks for the characters 'L' and 'R' in the first two bytes of the EEPROM
 *   memory range starting from byte EEPROM_STORAGE_SPACE_START.  If not found,
 *   it resets the settings ..
 */
void EEPROM_Utils::initEEPROM(bool forceClear) {

  byte c1 = EEPROM.read(EEPROM_START_C1);
  byte c2 = EEPROM.read(EEPROM_START_C2);

  if (forceClear || c1 != 76 || c2 != 81) { // LR 76 82

    const uint16_t score = 0;
    EEPROM.update(EEPROM_START_C1, 76);
    EEPROM.update(EEPROM_START_C2, 81);
    EEPROM.update(EEPROM_LEVEL_NO, 1);
    EEPROM.update(EEPROM_MEN_LEFT, 5);
    EEPROM.put(EEPROM_SCORE, score);

  }

}


/* -----------------------------------------------------------------------------
 *   Get the current level number. 
 */
uint8_t EEPROM_Utils::getLevelNumber() {

  return EEPROM.read(EEPROM_LEVEL_NO);

}


/* -----------------------------------------------------------------------------
 *   Save the current level number. 
 */
void EEPROM_Utils::saveLevelNumber(uint8_t levelNumber) {

  EEPROM.update(EEPROM_LEVEL_NO, levelNumber);

}


/* -----------------------------------------------------------------------------
 *   Get saved game data.
 */
void EEPROM_Utils::getSavedGameData(Level *level, Player *player) {

  level->setLevelNumber(EEPROM.read(EEPROM_LEVEL_NO));
  player->men = EEPROM.read(EEPROM_MEN_LEFT);
  EEPROM.get(EEPROM_SCORE, player->score);

}


/* -----------------------------------------------------------------------------
 *   Save game data.
 */
void EEPROM_Utils::saveGameData(Level *level, Player *player) {

  EEPROM.update(EEPROM_LEVEL_NO, level->getLevelNumber());
  EEPROM.update(EEPROM_MEN_LEFT, player->men);
  EEPROM.put(EEPROM_SCORE, player->score);

}
