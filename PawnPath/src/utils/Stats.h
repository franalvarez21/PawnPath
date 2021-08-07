#pragma once

struct Stats
{
  uint8_t hp;
  uint8_t hurt;
  uint32_t score;

  void init()
  {
    hp = 5;
    hurt = 0;
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

  void displayHub()
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
  }

private:
  void timeTick()
  {
    if (hurt > 0)
    {
      hurt--;
    }
  }

  void displayHeart(uint8_t pos)
  {
    Arduboy2Base::drawBitmap(0, pos * ELEMENT_SIZE, Common::life, ELEMENT_SIZE, ELEMENT_SIZE, WHITE);
  }
};
