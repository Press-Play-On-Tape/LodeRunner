#pragma once

#include "src/utils/Arduboy2Ext.h"

#include "Utils.h"
#include "Enums.h"

boolean isSolid(LevelElement levelElement) {

  switch (levelElement) {

    case LevelElement::Brick:
    case LevelElement::Solid:
      return true;

    default:
      return false;

  }

}

boolean canBeStoodOn(LevelElement levelElement) {

  switch (levelElement) {

    case LevelElement::Brick:
    case LevelElement::Solid:
    case LevelElement::Ladder:
    case LevelElement::LadderLevel:
      return true;

    default:
      return false;

  }

}

boolean canBeStoodOn_Enemy(LevelElement levelElement) {

  switch (levelElement) {

    case LevelElement::Brick:
    case LevelElement::Solid:
    case LevelElement::Ladder:
    case LevelElement::LadderLevel:
    case LevelElement::Brick_3:
    case LevelElement::Brick_4:
    case LevelElement::Brick_Transition:
    case LevelElement::Brick_Close_1:
    case LevelElement::Brick_Close_2:
      return true;

    default:
      return false;

  }

}

boolean canBeFallenOn(LevelElement levelElement) {

  switch (levelElement) {

    case LevelElement::Brick:
    case LevelElement::Solid:
    case LevelElement::Rail:
    case LevelElement::Ladder:
    case LevelElement::LadderLevel:
      return true;

    default:
      return false;

  }

}

boolean canBeOccupied(LevelElement levelElement) {

  switch (levelElement) {

    case LevelElement::Blank:
    case LevelElement::Ladder:
    case LevelElement::Rail:
    case LevelElement::LadderLevel:
    case LevelElement::Gold:
      return true;

    default:
      return false;

  }

}

boolean canBeOccupiedTemporarily(LevelElement levelElement) {

  switch (levelElement) {

    case LevelElement::Blank:
    case LevelElement::Ladder:
    case LevelElement::Rail:
    case LevelElement::LadderLevel:
    case LevelElement::Gold:
    case LevelElement::Brick_3:
    case LevelElement::Brick_4:
    case LevelElement::Brick_Transition:
    case LevelElement::Brick_Close_1:
    case LevelElement::Brick_Close_2:
      return true;

    default:
      return false;

  }

}

boolean canBeFallenInto(LevelElement levelElement) {

  switch (levelElement) {

    case LevelElement::Blank:
      return true;

    default:
      return false;

  }

}

boolean canBeFallenIntoTemporarily(LevelElement levelElement) {

  switch (levelElement) {

    case LevelElement::Blank:
    case LevelElement::Brick_3:
    case LevelElement::Brick_4:
    case LevelElement::Brick_Transition:
    case LevelElement::Brick_Close_1:
    case LevelElement::Brick_Close_2:
      return true;

    default:
      return false;

  }

}