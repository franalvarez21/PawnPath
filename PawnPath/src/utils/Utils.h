#pragma once

#include <stdint.h>
#include <stdlib.h>

#include <Arduboy2.h>
#include <ArduboyTones.h>

#include "const/Maps.h"
#include "const/Digits.h"
#include "const/Common.h"
#include "const/Lines.h"
#include "const/Title.h"

struct Utils
{
  bool sound = false;
  bool mode = false;
  uint8_t music = 0;
  uint8_t cycle = 10;
  uint8_t lullaby = 0;
  uint8_t musicalLullaby[4][10] = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 1, 0, 1, 2, 0, 1, 1, 2, 0}, {0, 1, 2, 0, 1, 2, 0, 1, 1, 2}, {0, 1, 1, 1, 3, 3, 3, 1, 1, 1}};

  void tick()
  {
    cycle--;
    if (cycle < 1)
    {
      lullaby++;
      if (lullaby == 10)
      {
        lullaby = 0;
      }

      if (musicalLullaby[music][lullaby] > 0)
      {
        if (musicalLullaby[music][lullaby] == 1)
        {
          ArduboyTones::tone(80, 25);
        }
        else if (musicalLullaby[music][lullaby] == 2)
        {
          ArduboyTones::tone(50, 50);
        }
        else
        {
          ArduboyTones::tone(80, 50);
        }
      }
      cycle = 10;
    }
  }

  void changeMode()
  {
    mode = !mode;
  }

  void changeSound()
  {
    if (sound)
    {
      sound = false;
      Arduboy2Base::audio.off();
    }
    else
    {
      sound = true;
      Arduboy2Base::audio.on();
      okBeep();
    }
  }

  void koBeep()
  {
    ArduboyTones::tone(250, 50);
  }

  void okBeep()
  {
    ArduboyTones::tone(700, 50);
  }

  void subtleKoBeep()
  {
    ArduboyTones::tone(200, 40);
  }

  void subtleOkBeep()
  {
    ArduboyTones::tone(600, 40);
  }

  uint8_t sizeTypeAbs(uint8_t a, uint8_t b)
  {
    return a < b ? b - a : a - b;
  }
};

#include "Numbers.h"
#include "Stats.h"
#include "Effects.h"
