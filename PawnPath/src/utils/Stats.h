#pragma once

struct Stats
{
  uint8_t hp;
  uint8_t hurt;
  uint8_t change;
  uint8_t changeAmount;
  uint32_t score;

  void init()
  {
    hp = 5;
    hurt = 0;
    change = 0;
    score = 0;
  }

  void incHP(uint8_t val)
  {
    hp = min(hp + val, MAX_LIFE);
    hurt = 0;
  }

  void decHP(uint8_t val)
  {
    if (hurt == 0)
    {
      hp = max(hp - val, 0);
      hurt = LIFE_INVINCIBILITY_FRAMES;
    }
  }

  uint8_t getHP()
  {
    return min(hp, MAX_LIFE);
  }

  void incScore(uint32_t val)
  {
    score = min(score + val, MAX_SCORE);
    change = CHANGE_FRAMES;
    changeAmount = val;
  }

  void decScore(uint32_t val)
  {
    score = max(score - val, 0);
    change = CHANGE_FRAMES;
    changeAmount = val;
  }

  uint32_t getScore()
  {
    return min(score, MAX_SCORE);
  }

  void displayHub(Numbers *numbers, bool animatedScore = true)
  {
    timeTick();

    for (uint8_t pos = 0; pos < hp; pos++)
    {
      displayHeart(pos);
    }

    if (hurt > 0 && hurt % 2 == 0)
    {
      displayHeart(hp);
    }

    if (change > 15 && change % 2 == 0)
    {
      displayScore(numbers, changeAmount);
    }
    else if ((change > 0 && change < 15) || !animatedScore)
    {
      displayScore(numbers, score);
    }
  }

private:
  void timeTick()
  {
    if (hurt > 0)
    {
      hurt--;
    }

    if (change > 0)
    {
      change--;
    }
  }

  void displayHeart(uint8_t pos)
  {
    Arduboy2Base::drawBitmap(0, pos * ELEMENT_SIZE, Common::life, ELEMENT_SIZE, ELEMENT_SIZE, WHITE);
  }

  void displayScore(Numbers *numbers, uint32_t actualScore)
  {
    numbers->print(77, 55, actualScore);
    Arduboy2Base::drawBitmap(58, 56, Lines::hubScoreBack, 26, 7, BLACK);
    Arduboy2Base::drawBitmap(59, 57, Lines::hubScore, 24, 5, WHITE);
  }
};
