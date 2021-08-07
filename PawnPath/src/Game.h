#pragma once

#define MAX_SQUARE_AMOUNT_WEIGHT 16
#define MAX_SQUARE_AMOUNT_HEIGHT 9
#define SQUARE_AMOUNT_WEIGHT 16
#define SQUARE_AMOUNT_HEIGHT 10
#define ELEMENT_SIZE 8
#define SQUARE_SIZE 16
#define ENEMY_AMOUNT 2
#define RANDOM_ENEMY_AMOUNT 3
#define CUTSCENE_TIMER 25
#define MAX_LEVEL 10
#define MAX_LIFE 8
#define MAX_SCORE 9999
#define LIFE_INVINCIBILITY_FRAMES 10
#define CHANGE_FRAMES 20

#include "utils/Utils.h"

class Game
{
public:
  void setup(void);
  void loop(void);
  void restart(void);
  void mainMenuTick(void);
  void mainPauseTick(void);
  void mainGameTick(void);
  void mainCutsceneTick(void);
  void mainLevelCutsceneTick(void);
  void mainGameoverCutsceneTick(void);
  void mainLastCutsceneTick(void);
};
