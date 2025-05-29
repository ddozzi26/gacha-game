#pragma once
#include <string>
#include "Gacha.h"

class Menu {
private:
    int jewels = 160;
    Gacha gacha;
    bool selectedPlane = false;      // 5�� ������ ���� ����
    bool selectedWeapon = false;     // 5�� ���� ���� ����

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