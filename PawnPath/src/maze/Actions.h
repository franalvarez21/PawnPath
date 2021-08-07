
class Actions
{
public:
  bool evaluateAction(Utils *utils, Stats *stats, Dungeon *dungeon, uint8_t action)
  {
    if (dungeon->canContinue())
    {
      dungeon->increaseLevel();
      dungeon->reset();
      return true;
    }

    switch (action)
    {
    case 1:
      stats->decHP(MAX_LIFE);
      utils->subtleKoBeep();
      break;
    case 2:
      stats->incHP(1);
      utils->subtleOkBeep();
      break;
    case 3:
      // Restore map
      utils->subtleOkBeep();
      break;
    case 4:
      stats->decHP(1);
      utils->subtleKoBeep();
      break;
    case 5:
      // Activate goal
      utils->subtleOkBeep();
      break;
    case 6:
      // Deactivate goal
      utils->subtleKoBeep();
      break;
    }

    return false;
  }
};
