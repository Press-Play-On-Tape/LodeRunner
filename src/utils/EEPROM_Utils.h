#pragma once

#include "Arduboy2Ext.h"
#include "Enums.h"

class EEPROM_Utils {

  public: 

    EEPROM_Utils(){};
        
    static void initEEPROM();
    static uint8_t getLevelNumber();
    static void saveLevelNumber(uint8_t levelNumber);

};


/* ----------------------------------------------------------------------------
 *   Is the EEPROM initialised?
 *
 *   Looks for the characters 'L' and 'R' in the first two bytes of the EEPROM
 *   memory range starting from byte EEPROM_STORAGE_SPACE_START.  If not found,
 *   it resets the settings ..
 */
void EEPROM_Utils::initEEPROM() {

  byte c1 = EEPROM.read(EEPROM_START_C1);
  byte c2 = EEPROM.read(EEPROM_START_C2);

  if (c1 != 76 || c2 != 82) { // LR 68 85

    EEPROM.update(EEPROM_START_C1, 76);
    EEPROM.update(EEPROM_START_C2, 82);
    EEPROM.update(EEPROM_LEVEL_NO, 1);

  }

}


/* -----------------------------------------------------------------------------
 *   Get the current level number. 
 */
uint8_t EEPROM_Utils::getLevelNumber() {

  return EEPROM.read(EEPROM_LEVEL_NO);

}


/* -----------------------------------------------------------------------------
 *   Save game state.
 */
void EEPROM_Utils::saveLevelNumber(uint8_t levelNumber) {

  EEPROM.update(EEPROM_LEVEL_NO, levelNumber);

}


