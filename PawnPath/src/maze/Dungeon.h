
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
  uint8_t hasMove;
  uint8_t movementOrientation;

public:
  void refresh()
  {
    timer = 0;
    level = 0;
    lastCutscene = 0;
    hasMove = 0;
    reset();
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

  bool moveLeft(uint8_t key)
  {
    if (playerXPosition - 1 > 0)
    {
      if (map[playerXPosition - 1][playerYPosition] == key)
      {
        playerXPosition--;
        return true;
      }
    }
    return false;
  }

  bool moveRight(uint8_t key)
  {
    if (playerXPosition + 1 < SQUARE_AMOUNT_WEIGHT - 1)
    {
      if (map[playerXPosition + 1][playerYPosition] == key)
      {
        playerXPosition++;
        return true;
      }
    }
    return false;
  }

  bool moveTop(uint8_t key)
  {
    if (playerYPosition - 1 > 0)
    {
      if (map[playerXPosition][playerYPosition - 1] == key)
      {
        playerYPosition--;
        return true;
      }
    }
    return false;
  }

  bool moveDown(uint8_t key)
  {
    if (playerYPosition + 1 < SQUARE_AMOUNT_HEIGHT - 1)
    {
      if (map[playerXPosition][playerYPosition + 1] == key)
      {
        playerYPosition++;
        return true;
      }
    }
    return false;
  }

  bool moveWalker(uint8_t key)
  {
    uint8_t can_continue = 10;
    bool move = false;

    while (!move && can_continue > 0)
    {
      switch (rand() % 4)
      {
      case 0:
        move = moveTop(key);
        break;
      case 1:
        move = moveRight(key);
        break;
      case 2:
        move = moveDown(key);
        break;
      case 3:
        move = moveLeft(key);
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

  void reset()
  {
    clearMap();
    clearPlayerPosition();

    map[playerXPosition][playerYPosition] = 3;

    walkerCircle();

    reduceMap();

    playerBorders(0);
    spawnObjects();
    playerBorders(3);

    map[playerXPosition][playerYPosition] = 3;
  }

  void borders(uint8_t weight = MAX_SQUARE_AMOUNT_WEIGHT, uint8_t height = MAX_SQUARE_AMOUNT_HEIGHT)
  {
    for (uint8_t y = 0; y < height - 1; y++)
    {
      Arduboy2Base::drawFastVLine(ELEMENT_SIZE, y * ELEMENT_SIZE, ELEMENT_SIZE, WHITE);
    }
  }

  void display(uint8_t cycle)
  {
    uint8_t camX = (playerXPosition < 5) ? 1 : playerXPosition - 4;
    uint8_t camY = (playerYPosition < 3) ? 1 : playerYPosition - 2;

    for (uint8_t x = camX, i = 1; i < 8 && x < SQUARE_AMOUNT_WEIGHT - 1; x++, i++)
    {
      for (uint8_t y = camY - 1, j = 0; j < 7 && y < SQUARE_AMOUNT_HEIGHT - 1; y++, j++)
      {
        displayElements(x, y, i, j, cycle);
        if (x == playerXPosition && y == playerYPosition)
        {
          if (hasMove)
          {
            hasMove = false;
            switch (movementOrientation)
            {
            case 0: // Right
              Arduboy2Base::drawBitmap(SQUARE_SIZE * i - 6, SQUARE_SIZE * j - 2 - SQUARE_SIZE, Common::player_1, SQUARE_SIZE, SQUARE_SIZE, BLACK);
              Arduboy2Base::drawBitmap(SQUARE_SIZE * i - 6, SQUARE_SIZE * j - 2 - SQUARE_SIZE, Common::player_2, SQUARE_SIZE, SQUARE_SIZE, WHITE);
              break;
            case 1: // Left
              Arduboy2Base::drawBitmap(SQUARE_SIZE * i + 2, SQUARE_SIZE * j - 2 - SQUARE_SIZE, Common::player_1, SQUARE_SIZE, SQUARE_SIZE, BLACK);
              Arduboy2Base::drawBitmap(SQUARE_SIZE * i + 2, SQUARE_SIZE * j - 2 - SQUARE_SIZE, Common::player_2, SQUARE_SIZE, SQUARE_SIZE, WHITE);
              break;
            case 2: // Buttom
              Arduboy2Base::drawBitmap(SQUARE_SIZE * i - 2, SQUARE_SIZE * j + 2 - SQUARE_SIZE, Common::player_1, SQUARE_SIZE, SQUARE_SIZE, BLACK);
              Arduboy2Base::drawBitmap(SQUARE_SIZE * i - 2, SQUARE_SIZE * j + 2 - SQUARE_SIZE, Common::player_2, SQUARE_SIZE, SQUARE_SIZE, WHITE);
              break;
            case 3: // Up
              Arduboy2Base::drawBitmap(SQUARE_SIZE * i - 2, SQUARE_SIZE * j - 6 - SQUARE_SIZE, Common::player_1, SQUARE_SIZE, SQUARE_SIZE, BLACK);
              Arduboy2Base::drawBitmap(SQUARE_SIZE * i - 2, SQUARE_SIZE * j - 6 - SQUARE_SIZE, Common::player_2, SQUARE_SIZE, SQUARE_SIZE, WHITE);
              break;
            }
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
    numbers->print(25, 36, stats->score);
    Arduboy2Base::drawBitmap(79, 36, Lines::hubScore, 24, 5, WHITE);
  }

  void displayEnding()
  {
    Arduboy2Base::drawBitmap(44, 38, Lines::ending, 39, 4, WHITE);
  }

  void displayLevelStart(Utils *utils, Effects *effects, Stats *stats, Numbers *numbers)
  {
    timer = (timer == 0) ? 10 : timer - 1;

    switch (timer)
    {
    case 1:
      Arduboy2Base::drawBitmap(58, 15, Common::book_5, 12, 12, WHITE);
      break;
    case 2:
      Arduboy2Base::drawBitmap(58, 15, Common::book_4, 12, 12, WHITE);
      break;
    case 3:
      Arduboy2Base::drawBitmap(58, 15, Common::book_3, 12, 12, WHITE);
      break;
    case 4:
      Arduboy2Base::drawBitmap(58, 15, Common::book_2, 12, 12, WHITE);
      break;
    default:
      Arduboy2Base::drawBitmap(58, 15, Common::book_1, 12, 12, WHITE);
      break;
    }

    numbers->print(45, 50, stats->score);
    Arduboy2Base::drawBitmap(99, 50, Lines::hubScore, 24, 5, WHITE);

    Arduboy2Base::drawBitmap(90, 0, Title::title_border, 38, 38, WHITE);
  }

private:
  bool pressed(uint8_t button)
  {
    if (Arduboy2Base::justPressed(button)) // Arduboy2Base::pressed(button)
    {
      return true;
    }
    return false;
  }

  void clearPlayerPosition()
  {
    playerXPosition = 6;
    playerYPosition = 4;
    hasMove = 0;
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

  void reduceMap()
  {
    for (uint8_t i = 1; i < SQUARE_AMOUNT_WEIGHT - 1; i++)
    {
      for (uint8_t j = 1; j < SQUARE_AMOUNT_HEIGHT - 1; j++)
      {
        if (map[i][j] == 0 && map[i - 1][j] == 3 && map[i + 1][j] == 3 && map[i][j - 1] == 3 && map[i - 1][j + 1] == 3)
        {
          map[i][j] = 1;
        }
      }
    }
  }

  void walkerCircle()
  {
    for (uint8_t i = 0; i < WALKER_CYCLES; i++)
    {
      if (!moveWalker(0))
      {
        moveWalker(1);
      }

      map[playerXPosition][playerYPosition] = 3;
    }

    clearPlayerPosition();
  }

  void spawnObjects()
  {
    if (level < MAX_LEVEL)
    {
      // Spawn Objects
      if (rand() % 2 == 0)
      {
        spawnObject(4 + (rand() % 3));
      }

      // Spawn Switch Points
      switchOffAmount = 0;
      for (uint8_t i = 0; i < (3 + rand() % RANDOM_ENEMY_AMOUNT); i++)
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

  void displayElements(uint8_t x, uint8_t y, uint8_t i, uint8_t j, uint8_t cycle)
  {
    switch (map[x][y])
    {
    case 0:
      // Arduboy2Base::drawBitmap(SQUARE_SIZE * i - 2, SQUARE_SIZE * j - SQUARE_SIZE, Common::empty_position, SQUARE_SIZE, SQUARE_SIZE, WHITE);
      break;
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
      Arduboy2Base::drawBitmap(SQUARE_SIZE * i - 2, SQUARE_SIZE * j - SQUARE_SIZE, Common::goal_position, SQUARE_SIZE, SQUARE_SIZE, WHITE);
      break;
    case 8:
      Arduboy2Base::drawBitmap(SQUARE_SIZE * i - 2, SQUARE_SIZE * j - SQUARE_SIZE, Common::goal_position_2, SQUARE_SIZE, SQUARE_SIZE, WHITE);
      break;
    case 9:
      Arduboy2Base::drawBitmap(SQUARE_SIZE * i - 2, SQUARE_SIZE * j - SQUARE_SIZE, Common::flag_position, SQUARE_SIZE, SQUARE_SIZE, WHITE);
      break;
    }
  }

  void displayMaze(uint8_t x, uint8_t y, uint8_t i, uint8_t j)
  {
    if (map[x][y] > 0)
    {
      if (map[x - 1][y] > 0 && map[x + 1][y] > 0 && map[x][y - 1] == 0 && map[x][y + 1] > 0)
      {
        //top
        Arduboy2Base::drawFastHLine(SQUARE_SIZE * i - 2, SQUARE_SIZE * j - SQUARE_SIZE, SQUARE_SIZE, WHITE);
      }
      else if (map[x - 1][y] > 0 && map[x + 1][y] == 0 && map[x][y - 1] > 0 && map[x][y + 1] > 0)
      {
        //right
        Arduboy2Base::drawFastVLine(SQUARE_SIZE * i + (SQUARE_SIZE - 1) - 2, SQUARE_SIZE * j - SQUARE_SIZE, SQUARE_SIZE, WHITE);
      }
      else if (map[x - 1][y] == 0 && map[x + 1][y] > 0 && map[x][y - 1] > 0 && map[x][y + 1] > 0)
      {
        //left
        Arduboy2Base::drawFastVLine(SQUARE_SIZE * i - 2, SQUARE_SIZE * j - SQUARE_SIZE, SQUARE_SIZE, WHITE);
      }
      else if (map[x - 1][y] > 0 && map[x + 1][y] > 0 && map[x][y - 1] > 0 && map[x][y + 1] == 0)
      {
        //bottom
        Arduboy2Base::drawFastHLine(SQUARE_SIZE * i - 2, SQUARE_SIZE * j - 1, SQUARE_SIZE, WHITE);
      }
      else if (map[x - 1][y] == 0 && map[x + 1][y] > 0 && map[x][y - 1] == 0 && map[x][y + 1] > 0)
      {
        Arduboy2Base::drawFastHLine(SQUARE_SIZE * i - 2, SQUARE_SIZE * j - SQUARE_SIZE, SQUARE_SIZE, WHITE);
        Arduboy2Base::drawFastVLine(SQUARE_SIZE * i - 2, SQUARE_SIZE * j - SQUARE_SIZE, SQUARE_SIZE, WHITE);
      }
      else if (map[x - 1][y] > 0 && map[x + 1][y] == 0 && map[x][y - 1] == 0 && map[x][y + 1] > 0)
      {
        Arduboy2Base::drawFastHLine(SQUARE_SIZE * i - 2, SQUARE_SIZE * j - SQUARE_SIZE, SQUARE_SIZE, WHITE);
        Arduboy2Base::drawFastVLine(SQUARE_SIZE * i + (SQUARE_SIZE - 1) - 2, SQUARE_SIZE * j - SQUARE_SIZE, SQUARE_SIZE, WHITE);
      }
      else if (map[x - 1][y] > 0 && map[x + 1][y] == 0 && map[x][y - 1] > 0 && map[x][y + 1] == 0)
      {
        Arduboy2Base::drawFastHLine(SQUARE_SIZE * i - 2, SQUARE_SIZE * j - 1, SQUARE_SIZE, WHITE);
        Arduboy2Base::drawFastVLine(SQUARE_SIZE * i + (SQUARE_SIZE - 1) - 2, SQUARE_SIZE * j - SQUARE_SIZE, SQUARE_SIZE, WHITE);
      }
      else if (map[x - 1][y] == 0 && map[x + 1][y] > 0 && map[x][y - 1] > 0 && map[x][y + 1] == 0)
      {
        Arduboy2Base::drawFastHLine(SQUARE_SIZE * i - 2, SQUARE_SIZE * j - 1, SQUARE_SIZE, WHITE);
        Arduboy2Base::drawFastVLine(SQUARE_SIZE * i - 2, SQUARE_SIZE * j - SQUARE_SIZE, SQUARE_SIZE, WHITE);
      }
      else if (map[x - 1][y] == 0 && map[x + 1][y] > 0 && map[x][y - 1] == 0 && map[x][y + 1] == 0)
      {
        Arduboy2Base::drawFastHLine(SQUARE_SIZE * i - 2, SQUARE_SIZE * j - SQUARE_SIZE, SQUARE_SIZE, WHITE);
        Arduboy2Base::drawFastHLine(SQUARE_SIZE * i - 2, SQUARE_SIZE * j - 1, SQUARE_SIZE, WHITE);
        Arduboy2Base::drawFastVLine(SQUARE_SIZE * i - 2, SQUARE_SIZE * j - SQUARE_SIZE, SQUARE_SIZE, WHITE);
      }
      else if (map[x - 1][y] > 0 && map[x + 1][y] == 0 && map[x][y - 1] == 0 && map[x][y + 1] == 0)
      {
        Arduboy2Base::drawFastHLine(SQUARE_SIZE * i - 2, SQUARE_SIZE * j - SQUARE_SIZE, SQUARE_SIZE, WHITE);
        Arduboy2Base::drawFastHLine(SQUARE_SIZE * i - 2, SQUARE_SIZE * j - 1, SQUARE_SIZE, WHITE);
        Arduboy2Base::drawFastVLine(SQUARE_SIZE * i + (SQUARE_SIZE - 1) - 2, SQUARE_SIZE * j - SQUARE_SIZE, SQUARE_SIZE, WHITE);
      }
      else if (map[x - 1][y] == 0 && map[x + 1][y] == 0 && map[x][y - 1] > 0 && map[x][y + 1] == 0)
      {
        Arduboy2Base::drawFastHLine(SQUARE_SIZE * i - 2, SQUARE_SIZE * j - 1, SQUARE_SIZE, WHITE);
        Arduboy2Base::drawFastVLine(SQUARE_SIZE * i - 2, SQUARE_SIZE * j - SQUARE_SIZE, SQUARE_SIZE, WHITE);
        Arduboy2Base::drawFastVLine(SQUARE_SIZE * i + (SQUARE_SIZE - 1) - 2, SQUARE_SIZE * j - SQUARE_SIZE, SQUARE_SIZE, WHITE);
      }
      else if (map[x - 1][y] == 0 && map[x + 1][y] == 0 && map[x][y - 1] == 0 && map[x][y + 1] > 0)
      {
        Arduboy2Base::drawFastHLine(SQUARE_SIZE * i - 2, SQUARE_SIZE * j - SQUARE_SIZE, SQUARE_SIZE, WHITE);
        Arduboy2Base::drawFastVLine(SQUARE_SIZE * i - 2, SQUARE_SIZE * j - SQUARE_SIZE, SQUARE_SIZE, WHITE);
        Arduboy2Base::drawFastVLine(SQUARE_SIZE * i + (SQUARE_SIZE - 1) - 2, SQUARE_SIZE * j - SQUARE_SIZE, SQUARE_SIZE, WHITE);
      }
      else if (map[x - 1][y] > 0 && map[x + 1][y] > 0 && map[x][y - 1] == 0 && map[x][y + 1] == 0)
      {
        Arduboy2Base::drawFastHLine(SQUARE_SIZE * i - 2, SQUARE_SIZE * j - SQUARE_SIZE, SQUARE_SIZE, WHITE);
        Arduboy2Base::drawFastHLine(SQUARE_SIZE * i - 2, SQUARE_SIZE * j - 1, SQUARE_SIZE, WHITE);
      }
      else if (map[x - 1][y] == 0 && map[x + 1][y] == 0 && map[x][y - 1] > 0 && map[x][y + 1] > 0)
      {
        Arduboy2Base::drawFastVLine(SQUARE_SIZE * i - 2, SQUARE_SIZE * j - SQUARE_SIZE, SQUARE_SIZE, WHITE);
        Arduboy2Base::drawFastVLine(SQUARE_SIZE * i + (SQUARE_SIZE - 1) - 2, SQUARE_SIZE * j - SQUARE_SIZE, SQUARE_SIZE, WHITE);
      }
    }
  }

  void playerBorders(uint8_t value)
  {
    for (uint8_t x = 0; x < 5; x++)
    {
      for (uint8_t y = 0; y < 5; y++)
      {
        map[playerXPosition + (2 - x)][playerYPosition + (2 - y)] = value;
      }
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
