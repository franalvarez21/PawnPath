
class Actions
{
public:
  bool evaluateAction(Utils *utils, Stats *stats, Dungeon *dungeon, uint8_t action)
  {
    if (dungeon->canContinue())
    {
      if (dungeon->hasMoved())
      {
        stats->incScore(5);
        dungeon->increaseLevel();
        utils->subtleOkBeep();
      }
      dungeon->reset(stats, utils->mode);
      return true;
    }

    switch (action)
    {
    case 1:
      // Fall of map
      dungeon->reset(stats, utils->mode);
      utils->subtleKoBeep();
      stats->decHP(1);
      break;
    case 2:
      // Restore HP
      stats->incHP(1);
      utils->subtleOkBeep();
      stats->incScore(1);
      break;
    case 3:
      // Restore map
      utils->subtleOkBeep();
      break;
    case 4:
      // Decrease HP
      stats->decHP(1);
      utils->subtleKoBeep();
      break;
    case 5:
      // Activate goal
      utils->subtleOkBeep();
      stats->incScore(5);
      break;
    case 6:
      // Deactivate goal
      utils->subtleKoBeep();
      stats->decScore(5);
      break;
    }

    return false;
  }
};
