#pragma once
#include <string>
#include "Gacha.h"

class Menu {
private:
    int jewels = 160;
    Gacha gacha;
    bool selectedPlane = false;      // 5성 전투기 선택 여부
    bool selectedWeapon = false;     // 5성 무기 선택 여부

public:
    Menu();
    int Show();
    void ShowDescription();
    void GachaMenu();
    void ChangeFighter();
    bool SpendJewels(int amount);
    void ShowGachaStats();

    bool GetSelectedPlane() const { return selectedPlane; }
    bool GetSelectedWeapon() const { return selectedWeapon; }
    void CheatMenu();
};