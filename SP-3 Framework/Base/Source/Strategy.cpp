#include "Strategy.h"

Strategy::Strategy()
{
    currentEnemy = nullptr;
}

Strategy::~Strategy()
{
}

void Strategy::SetCurrentEnemy(Enemy* currentEnemy)
{
    this->currentEnemy = currentEnemy;
}