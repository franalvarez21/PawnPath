
#include "Game.h"

#include "maze/Dungeon.h"
#include "maze/Actions.h"

#include "menus/Menu.h"
#include "menus/TitleMenu.h"
#include "menus/PauseMenu.h"

Arduboy2Base arduboy;
ArduboyTones sound(arduboy.audio.enabled);

uint8_t onStage;
uint8_t action;

Utils utils;
Stats stats;
Numbers numbers;
Effects effects;
Dungeon dungeon;

TitleMenu titleMenu;
PauseMenu pauseMenu;

Actions actions;

void Game::setup(void)
{
  arduboy.begin();
  arduboy.setFrameRate(15);
  arduboy.initRandomSeed();
  arduboy.systemButtons();
  arduboy.waitNoButtons();
  arduboy.audio.off();
  restart();
}

void Game::restart(void)
{
  dungeon.refresh();
  stats.init();
  action = 0;
}

void Game::loop(void)
{
  if (!(arduboy.nextFrame()))
  {
    return;
  }

  arduboy.pollButtons();
  arduboy.clear();
  utils.music = 0;

  switch (onStage)
  {
  case 0:
    mainMenuTick();
    break;
  case 1:
    mainPauseTick();
    break;
  case 2:
    mainGameTick();
    break;
  case 3:
    mainCutsceneTick();
    break;
  case 4:
    mainLevelCutsceneTick();
    break;
  case 5:
    mainGameoverCutsceneTick();
    break;
  default:
    mainLastCutsceneTick();
    break;
  }

  utils.tick();

  arduboy.display();
}

void Game::mainMenuTick(void)
{
  rand() % analogRead(0);
  utils.music = 2;
  titleMenu.eventDisplay(utils.cycle, utils.sound);
  if (!titleMenu.action(&utils))
  {
    restart();
    dungeon.cutsceneStart(false);
    onStage = 3;
    utils.lullaby = 0;
  }
}

void Game::mainPauseTick()
{
  pauseMenu.eventDisplay(&stats, &numbers, utils.sound);
  switch (pauseMenu.action(&utils))
  {
  case 1:
    onStage = 2;
    utils.lullaby = 0;
    break;
  case 2:
    onStage = 0;
    utils.lullaby = 0;
    break;
  }

  stats.displayHub();
  dungeon.borders();
}

void Game::mainGameTick(void)
{
  if (arduboy.justPressed(A_BUTTON))
  {
    pauseMenu.refresh();
    onStage = 1;
    utils.lullaby = 0;

    stats.displayHub();
    dungeon.borders();
  }
  else
  {
    action = dungeon.movePlayer(&utils, &stats);
    if (actions.evaluateAction(&utils, &stats, &dungeon, action))
    {
      dungeon.cutsceneStart(false);
      onStage = 4;
      utils.lullaby = 0;
    }
    else if (dungeon.level < MAX_LEVEL)
    {
      dungeon.display(utils.cycle);
    }

    if (dungeon.level == MAX_LEVEL)
    {
      dungeon.cutsceneStart(false);
      onStage = 6;
      utils.lullaby = 0;
    }
    else if (stats.getHP() < 1)
    {
      restart();
      utils.koBeep();
      dungeon.cutsceneStart(true);
      onStage = 5;
      utils.lullaby = 0;
    }
    else
    {
      stats.displayHub();
      dungeon.borders();
    }
  }
}

void Game::mainCutsceneTick(void)
{
  dungeon.cutscene.eventDisplay();
  if (dungeon.cutscene.enabled())
  {
    onStage = 2;
    utils.lullaby = 0;
  }
}

void Game::mainLevelCutsceneTick(void)
{
  dungeon.displayLevelStart(&utils, &effects, &stats, &numbers);
  dungeon.cutscene.eventDisplay();
  if (dungeon.cutscene.enabled())
  {
    onStage = 2;
    utils.lullaby = 0;
  }

  dungeon.borders();
  stats.displayHub();
}

void Game::mainGameoverCutsceneTick(void)
{
  dungeon.displayGameOver(&stats, &numbers);
  dungeon.cutscene.eventDisplay();
  if (dungeon.cutscene.enabled() && (arduboy.justPressed(A_BUTTON) || arduboy.justPressed(B_BUTTON) || arduboy.justPressed(LEFT_BUTTON) || arduboy.justPressed(RIGHT_BUTTON)))
  {
    onStage = 0;
    utils.lullaby = 0;
  }
}

void Game::mainLastCutsceneTick(void)
{
  utils.music = 3;
  dungeon.displayEnding();
  dungeon.cutscene.eventDisplay();
}
