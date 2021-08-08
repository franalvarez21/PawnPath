#pragma once

#include <stdint.h>
#include <stdlib.h>

#include <Arduboy2.h>
#include <ArduboyPlaytune.h>

#include "const/Maps.h"
#include "const/Digits.h"
#include "const/Common.h"
#include "const/Lines.h"
#include "const/Title.h"
#include "const/Tunes.h"

struct Utils
{
  ArduboyPlaytune *soundTunes;
  bool sound = false;
  uint8_t mode = 0;
  uint8_t cycle = 10;

  void init(ArduboyPlaytune *ref)
  {
    soundTunes = ref;
    soundTunes->initChannel(PIN_SPEAKER_1);
  }

  void tick()
  {
    cycle--;
    if (cycle < 1)
    {
      cycle = 10;
    }
  }

  void changeRightMode()
  {
    if (mode >= 2)
    {
      mode = 0;
    }
    else
    {
      mode++;
    }
  }

  void changeLeftMode()
  {
    if (mode <= 0)
    {
      mode = 2;
    }
    else
    {
      mode--;
    }
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

  void playSound(const byte *score)
  {
    if (soundTunes->playing())
    {
      soundTunes->stopScore();
    }
    soundTunes->playScore(score);
  }

  void koBeep()
  {
    playSound(Tunes::soundTick);
  }

  void okBeep()
  {
    playSound(Tunes::soundClick);
  }

  void startBeep()
  {
    playSound(Tunes::soundStart);
  }

  void overBeep()
  {
    playSound(Tunes::soundOver);
  }

  void levelUpBeep()
  {
    playSound(Tunes::soundLevelUp);
  }

  void boundBeep()
  {
    playSound(Tunes::soundBound);
  }

  void fastBeep()
  {
    playSound(Tunes::soundFast);
  }
};

#include "Numbers.h"
#include "Stats.h"
#include "Effects.h"
