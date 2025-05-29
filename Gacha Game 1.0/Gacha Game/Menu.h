#pragma once
#include <string>
#include "Gacha.h"

class Menu {
private:
    int jewels = 160;
    Gacha gacha;

public:
    Menu();
    int Show();
    void ShowDescription();
    void GachaMenu();
    void ChangeFighter();
    bool SpendJewels(int amount);
    void ShowGachaStats();
    void CheatMenu();  
};