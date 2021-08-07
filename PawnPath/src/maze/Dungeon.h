
#include "Cutscene.h"

class Dungeon
{
public:
  size_t level;
  size_t lastCutscene;
  Cutscene cutscene;

protected:
  uint8_t map[SQUARE_AMOUNT_WEIGHT][SQUARE_AMOUNT_HEIGHT];
  uint8_t playerXPosition;
  uint8_t playerYPosition;
  uint8_t switchOffAmount;
  uint8_t movementOrientation;
  bool hasMove;

  uint8_t (*mapPointer[1])[SQUARE_AMOUNT_WEIGHT][SQUARE_AMOUNT_HEIGHT] = {
      &Maps::map_0,
  };

public:
  void refresh(bool mode)
  {
    timer = 0;
    level = 0;
    lastCutscene = 0;
    hasMove = false;
    reset(mode);
  }

  void cutsceneStart(bool start)
  {
    cutscene.start(start);
    lastCutscene = level;
  }

  bool canContinue()
  {
    return switchOffAmount == 0;
  }

  bool hasMoved()
  {
    return hasMove;
  }

  bool cutsceneDone()
  {
    return lastCutscene == level;
  }

  uint8_t movePlayer(Utils *utils, Stats *stats)
  {
    uint8_t value = 0;

    if (pressed(RIGHT_BUTTON))
    {
      movementOrientation = 0;
      value = move(1, 0);
    }

    if (pressed(LEFT_BUTTON))
    {
      movementOrientation = 1;
      value = move(-1, 0);
    }

    if (pressed(DOWN_BUTTON))
    {
      movementOrientation = 2;
      value = move(0, 1);
    }

    if (pressed(UP_BUTTON))
    {
      movementOrientation = 3;
      value = move(0, -1);
    }

    return value;
  }

  bool moveLeft()
  {
    if (playerXPosition - 1 > 0)
    {
      if (map[playerXPosition - 1][playerYPosition] == 0)
      {
        playerXPosition--;
        return true;
      }
    }
    return false;
  }

  bool moveRight()
  {
    if (playerXPosition + 1 < SQUARE_AMOUNT_WEIGHT - 1)
    {
      if (map[playerXPosition + 1][playerYPosition] == 0)
      {
        playerXPosition++;
        return true;
      }
    }
    return false;
  }

  bool moveTop()
  {
    if (playerYPosition - 1 > 0)
    {
      if (map[playerXPosition][playerYPosition - 1] == 0)
      {
        playerYPosition--;
        return true;
      }
    }
    return false;
  }

  bool moveDown()
  {
    if (playerYPosition + 1 < SQUARE_AMOUNT_HEIGHT - 1)
    {
      if (map[playerXPosition][playerYPosition + 1] == 0)
      {
        playerYPosition++;
        return true;
      }
    }
    return false;
  }

  bool moveWalker()
  {
    uint8_t can_continue = 10;
    bool move = false;

    while (!move && can_continue > 0)
    {
      switch (rand() % 4)
      {
      case 0:
        move = moveTop();
        break;
      case 1:
        move = moveRight();
        break;
      case 2:
        move = moveDown();
        break;
      case 3:
        move = moveLeft();
        break;
      }
      can_continue--;
    }
    return move;
  }

  void increaseLevel()
  {
    level++;
  }

  void reset(bool mode)
  {
    clearMap();
    hasMove = false;

    if (mode)
    {
      restorePlayerPosition();
      map[playerXPosition][playerYPosition] = 3;
      walkerCircle();
    }
    else
    {
      switchOffAmount = 0;
      uint8_t cell[SQUARE_AMOUNT_WEIGHT][SQUARE_AMOUNT_HEIGHT];
      memcpy_P(&cell, mapPointer[level], sizeof(cell));

      for (uint8_t i = 0; i < SQUARE_AMOUNT_WEIGHT; i++)
      {
        for (uint8_t j = 0; j < SQUARE_AMOUNT_HEIGHT; j++)
        {
          map[i][j] = cell[i][j];
          if (map[i][j] == 9)
          {
            playerXPosition = i;
            playerYPosition = j;
            map[i][j] = 3;
          }
          if (map[i][j] == 7)
          {
            switchOffAmount++;
          }
        }
      }
    }
  }

  void displayLevel(Numbers *numbers)
  {
    numbers->print(26, 5, min(level, MAX_LEVEL));
    Arduboy2Base::drawBitmap(36, 5, Digits::back, 10, 10, BLACK);
    Arduboy2Base::drawBitmap(18, 5, Lines::hubLevel, 24, 5, WHITE);
  }

  void borders(uint8_t weight = MAX_SQUARE_AMOUNT_WEIGHT, uint8_t height = MAX_SQUARE_AMOUNT_HEIGHT)
  {
    for (uint8_t y = 0; y < height - 1; y++)
    {
      Arduboy2Base::drawFastVLine(ELEMENT_SIZE + 1, y * ELEMENT_SIZE, ELEMENT_SIZE, WHITE);
      Arduboy2Base::drawFastVLine(ELEMENT_SIZE + 2, y * ELEMENT_SIZE, ELEMENT_SIZE, WHITE);
      Arduboy2Base::drawFastVLine(ELEMENT_SIZE + 3, y * ELEMENT_SIZE, ELEMENT_SIZE, WHITE);
    }
  }

  void display(uint8_t cycle, bool mode)
  {
    uint8_t camX = (playerXPosition < 5) ? 1 : playerXPosition - 4;
    uint8_t camY = (playerYPosition < 3) ? 1 : playerYPosition - 2;

    for (uint8_t x = camX, i = 1; i < 8 && x < SQUARE_AMOUNT_WEIGHT - 1; x++, i++)
    {
      for (uint8_t y = camY - 1, j = 0; j < 7 && y < SQUARE_AMOUNT_HEIGHT - 1; y++, j++)
      {
        displayElements(mode, x, y, i, j, cycle);
        if (x == playerXPosition && y == playerYPosition)
        {
          if (hasMove)
          {
            Arduboy2Base::drawBitmap(SQUARE_SIZE * i - 2, SQUARE_SIZE * j - 6 - SQUARE_SIZE, Common::player_1, SQUARE_SIZE, SQUARE_SIZE, BLACK);
            Arduboy2Base::drawBitmap(SQUARE_SIZE * i - 2, SQUARE_SIZE * j - 6 - SQUARE_SIZE, Common::player_2, SQUARE_SIZE, SQUARE_SIZE, WHITE);
            hasMove = false;
          }
          else
          {
            Arduboy2Base::drawBitmap(SQUARE_SIZE * i - 2, SQUARE_SIZE * j - 2 - SQUARE_SIZE, Common::player_1, SQUARE_SIZE, SQUARE_SIZE, BLACK);
            Arduboy2Base::drawBitmap(SQUARE_SIZE * i - 2, SQUARE_SIZE * j - 2 - SQUARE_SIZE, Common::player_2, SQUARE_SIZE, SQUARE_SIZE, WHITE);
          }
        }
      }
    }
  }

  void displayGameOver(Stats *stats, Numbers *numbers)
  {
    Arduboy2Base::drawBitmap(25, 24, Lines::gameover, 78, 8, WHITE);
    numbers->print(25, 36, stats->getScore());
    Arduboy2Base::drawBitmap(79, 36, Lines::hubScore, 24, 5, WHITE);
  }

  void displayEnding(Stats *stats, Numbers *numbers)
  {
    Arduboy2Base::drawBitmap(0, 0, Title::title_ending, 128, 36, WHITE);
    numbers->print(25, 40, stats->getScore());
    Arduboy2Base::drawBitmap(79, 40, Lines::hubScore, 24, 5, WHITE);
  }

  void displayLevelStart(Utils *utils, Effects *effects)
  {
    timer = (timer == 0) ? 10 : timer - 1;

    switch (timer)
    {
    case 1:
      Arduboy2Base::drawBitmap(10, 25, Common::hourglass_0, 48, 39, WHITE);
      break;
    case 2:
      Arduboy2Base::drawBitmap(10, 25, Common::hourglass_3, 48, 39, WHITE);
      break;
    case 3:
      Arduboy2Base::drawBitmap(10, 25, Common::hourglass_2, 48, 39, WHITE);
      break;
    case 4:
      Arduboy2Base::drawBitmap(10, 25, Common::hourglass_1, 48, 39, WHITE);
      break;
    default:
      Arduboy2Base::drawBitmap(10, 25, Common::hourglass_0, 48, 39, WHITE);
      break;
    }

    Arduboy2Base::drawBitmap(90, 0, Title::title_border, 38, 38, WHITE);
  }

private:
  bool pressed(uint8_t button)
  {
    if (Arduboy2Base::justPressed(button))
    {
      return true;
    }
    return false;
  }

  void clearMap()
  {
    for (uint8_t i = 0; i < SQUARE_AMOUNT_WEIGHT; i++)
    {
      for (uint8_t j = 0; j < SQUARE_AMOUNT_HEIGHT; j++)
      {
        map[i][j] = 0;
      }
    }
  }

  void refreshMap()
  {
    for (uint8_t i = 0; i < SQUARE_AMOUNT_WEIGHT; i++)
    {
      for (uint8_t j = 0; j < SQUARE_AMOUNT_HEIGHT; j++)
      {
        if (map[i][j] == 1)
        {
          map[i][j] = 3;
        }
      }
    }
  }

  uint8_t getWalkerCiclesByLevel()
  {
    switch (level)
    {
    case 0 ... 1: // 0 ... 20:
      return 10;
    case 2 ... 3: // 21 ... 40:
      return 15;
    case 4 ... 5: // 41 ... 60:
      return 20;
    case 6 ... 7: // 61 ... 80:
      return 25;
    default:
      return 30;
    }
  }

  uint8_t getMaxAmountsByLevel()
  {
    switch (level)
    {
    case 0 ... 1: // 0 ... 20:
      return 1;
    case 2 ... 3: // 21 ... 40:
      return 3;
    case 4 ... 5: // 41 ... 60:
      return 5;
    case 6 ... 7: // 61 ... 80:
      return 7;
    default:
      return 9;
    }
  }

  void walkerCircle()
  {
    for (uint8_t i = 0; i < getWalkerCiclesByLevel(); i++)
    {
      if (i % 10 == 0)
      {
        restorePlayerPosition();
      }
      moveWalker();
      map[playerXPosition][playerYPosition] = 3;
    }

    spawnObjects();
    restorePlayerPosition();
    if (map[playerXPosition][playerYPosition] != 3)
    {
      if (map[playerXPosition][playerYPosition] == 7)
      {
        switchOffAmount--;
      }
    }
    map[playerXPosition][playerYPosition] = 3;
  }

  void restorePlayerPosition()
  {
    playerXPosition = 6;
    playerYPosition = 4;
  }

  void spawnObjects()
  {
    if (level < MAX_LEVEL)
    {
      switchOffAmount = 0;
      for (uint8_t i = 0; i < (1 + rand() % getMaxAmountsByLevel()); i++)
      {
        if (rand() % 2 == 0)
        {
          spawnObject(6);
        }
        else
        {
          spawnObject(4 + (rand() % 2));
        }
      }

      for (uint8_t i = 0; i < getMaxAmountsByLevel(); i++)
      {
        if (spawnObject(7))
        {
          switchOffAmount++;
        }
      }
    }
  }

  bool spawnObject(uint8_t item)
  {
    switch (rand() % 4)
    {
    case 0:
      for (uint8_t i = 1; i < SQUARE_AMOUNT_WEIGHT - 1; i++)
      {
        for (uint8_t j = 1; j < SQUARE_AMOUNT_HEIGHT - 1; j++)
        {
          if (canSetItem(i, j))
          {
            map[i][j] = item;
            return true;
          }
        }
      }
      break;
    case 1:
      for (uint8_t i = 1; i < SQUARE_AMOUNT_WEIGHT - 1; i++)
      {
        for (uint8_t j = SQUARE_AMOUNT_HEIGHT - 2; j > 0; j--)
        {
          if (canSetItem(i, j))
          {
            map[i][j] = item;
            return true;
          }
        }
      }
      break;
    case 2:
      for (uint8_t i = SQUARE_AMOUNT_WEIGHT - 2; i > 0; i--)
      {
        for (uint8_t j = SQUARE_AMOUNT_HEIGHT - 2; j > 0; j--)
        {
          if (canSetItem(i, j))
          {
            map[i][j] = item;
            return true;
          }
        }
      }
      break;
    case 3:
      for (uint8_t i = SQUARE_AMOUNT_WEIGHT - 2; i > 0; i--)
      {
        for (uint8_t j = 0; j < SQUARE_AMOUNT_HEIGHT - 1; j++)
        {
          if (canSetItem(i, j))
          {
            map[i][j] = item;
            return true;
          }
        }
      }
      break;
    }

    return false;
  }

  bool canSetItem(uint8_t i, uint8_t j)
  {
    return (map[i][j] == 3 && map[i - 1][j] < 4 && map[i][j - 1] < 4 && map[i + 1][j] < 4 && map[i][j + 1] < 4);
  }

  void displayElements(bool mode, uint8_t x, uint8_t y, uint8_t i, uint8_t j, uint8_t cycle)
  {
    switch (map[x][y])
    {
    case 1:
      Arduboy2Base::drawBitmap(SQUARE_SIZE * i - 2, SQUARE_SIZE * j - SQUARE_SIZE, Common::empty_position, SQUARE_SIZE, SQUARE_SIZE, WHITE);
      break;
    case 2:
      Arduboy2Base::drawBitmap(SQUARE_SIZE * i - 2, SQUARE_SIZE * j - SQUARE_SIZE, Common::half_position, SQUARE_SIZE, SQUARE_SIZE, WHITE);
      break;
    case 3:
      Arduboy2Base::drawBitmap(SQUARE_SIZE * i - 2, SQUARE_SIZE * j - SQUARE_SIZE, Common::full_position, SQUARE_SIZE, SQUARE_SIZE, WHITE);
      break;
    case 4:
      Arduboy2Base::drawBitmap(SQUARE_SIZE * i - 2, SQUARE_SIZE * j - SQUARE_SIZE, Common::heal_position, SQUARE_SIZE, SQUARE_SIZE, WHITE);
      break;
    case 5:
      Arduboy2Base::drawBitmap(SQUARE_SIZE * i - 2, SQUARE_SIZE * j - SQUARE_SIZE, (cycle <= 5) ? Common::refresh_position : Common::refresh_position_2, SQUARE_SIZE, SQUARE_SIZE, WHITE);
      break;
    case 6:
      Arduboy2Base::drawBitmap(SQUARE_SIZE * i - 2, SQUARE_SIZE * j - SQUARE_SIZE, (cycle <= 5) ? Common::spike_position : Common::spike_position_2, SQUARE_SIZE, SQUARE_SIZE, WHITE);
      break;
    case 7:
      if (mode)
      {
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i - 2, SQUARE_SIZE * j - SQUARE_SIZE, (switchOffAmount == 1) ? Common::crown_position : Common::goal_position, SQUARE_SIZE, SQUARE_SIZE, WHITE);
      }
      else
      {
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i - 2, SQUARE_SIZE * j - SQUARE_SIZE, (switchOffAmount == 1) ? Common::flag_position : Common::goal_position, SQUARE_SIZE, SQUARE_SIZE, WHITE);
      }
      break;
    case 8:
      Arduboy2Base::drawBitmap(SQUARE_SIZE * i - 2, SQUARE_SIZE * j - SQUARE_SIZE, Common::goal_position_2, SQUARE_SIZE, SQUARE_SIZE, WHITE);
      break;
    }
  }

  uint8_t move(const int extX, const int extY)
  {
    uint8_t value = map[playerXPosition + extX][playerYPosition + extY];
    if (value > 0)
    {
      hasMove = true;

      if (map[playerXPosition][playerYPosition] == 3)
      {
        map[playerXPosition][playerYPosition] = 2;
      }
      else if (map[playerXPosition][playerYPosition] == 2)
      {
        map[playerXPosition][playerYPosition] = 1;
      }

      playerXPosition += extX;
      playerYPosition += extY;

      if (map[playerXPosition][playerYPosition] == 1)
      {
        return 1;
      }
      else if (map[playerXPosition][playerYPosition] == 4)
      {
        map[playerXPosition][playerYPosition] = 3;
        return 2;
      }
      else if (map[playerXPosition][playerYPosition] == 5)
      {
        refreshMap();
        map[playerXPosition][playerYPosition] = 3;
        return 3;
      }
      else if (map[playerXPosition][playerYPosition] == 6)
      {
        return 4;
      }
      else if (map[playerXPosition][playerYPosition] == 7)
      {
        switchOffAmount--;
        map[playerXPosition][playerYPosition] = 8;
        return 5;
      }
      else if (map[playerXPosition][playerYPosition] == 8)
      {
        switchOffAmount++;
        map[playerXPosition][playerYPosition] = 7;
        return 6;
      }
    }
    return 0;
  }

private:
  uint8_t timer;
};
