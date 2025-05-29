#include "Menu.h"
#include <iostream>
#include <cstdlib>
#include <limits>
#include <string>

Menu::Menu()
    : gacha(jewels) {
}

int Menu::Show() {
    while (true) {
        system("cls");
        std::cout << "\n===== ���� ���� �޴� =====\n\n";
        std::cout << "1. ���� ����\n";
        std::cout << "2. ���� ���� ����\n";
        std::cout << "3. ��í (���� ���: " << jewels << "��)\n";
        std::cout << "4. ������ ���� �� ��í ��� Ȯ��\n";
        std::cout << "5. ���� ����\n";

        bool cheat = false;
        std::string inputStr;
        int input = 0;
        while (true) {
            std::cout << "��ȣ�� �����ϼ���: ";
            std::cin >> inputStr;
            if (inputStr == "ġƮŰ") {
                CheatMenu();
                cheat = true;
                break;
            }
            try {
                input = std::stoi(inputStr);
            }
            catch (...) {
                std::cout << "�߸��� �Է��Դϴ�. ���ڸ� �Է����ּ���.\n";
                continue;
            }
            if (input < 1 || input > 5) {
                std::cout << "���� �� ���ڸ� �Է����ּ���.\n";
                continue;
            }
            break;
        }
        if (cheat) continue;

        switch (input) {
        case 1:
            ShowDescription();
            system("pause");
            break;
        case 2:
            return 2;
        case 3:
            GachaMenu();
            break;
        case 4:
            ChangeFighter();
            ShowGachaStats();
            system("pause");
            break;
        case 5:
            std::cout << "������ �����մϴ�.\n";
            exit(0);
        default:
            system("pause");
            break;
        }
    }
}

void Menu::ShowDescription() {
    std::cout << "\n���� ����:\n";
    std::cout << "W/S Ű�� �����⸦ ��/�Ʒ��� �̵��ϼ���.\n";
    std::cout << "�����̽��ٷ� �Ѿ��� �߻��� ���� �����ϼ���.\n";
    std::cout << "���� �浹�ϸ� ������ ����˴ϴ�.\n\n";
}

void Menu::GachaMenu() {
    gacha.ShowGachaMenu();
}

void Menu::ChangeFighter() {
    std::cout << "\n=== ������/���� ���� ===\n";
    std::cout << "������ ����:\n";
    std::cout << "1. �⺻ ������\n";
    if (gacha.GetStar5Plane() > 0) std::cout << "2. 5�� ������\n";
    int pChoice = 1;
    std::cin >> pChoice;
    selectedPlane = (pChoice == 2 && gacha.GetStar5Plane() > 0);

    std::cout << "���� ����:\n";
    std::cout << "1. �⺻ ����\n";
    if (gacha.GetStar5Weapon() > 0) std::cout << "2. 5�� ����\n";
    int wChoice = 1;
    std::cin >> wChoice;
    selectedWeapon = (wChoice == 2 && gacha.GetStar5Weapon() > 0);
}

bool Menu::SpendJewels(int amount) {
    if (jewels >= amount) {
        jewels -= amount;
        return true;
    }
    else {
        std::cout << "����� �����մϴ�.\n";
        return false;
    }
}

void Menu::ShowGachaStats() {
    std::cout << "\n=== ��í ��� ===\n";
    std::cout << "3��: " << gacha.GetStar3() << "��\n";
    std::cout << "4��: " << gacha.GetStar4() << "��\n";
    std::cout << "5�� ������: " << gacha.GetStar5Plane() << "��\n";
    std::cout << "5�� ����: " << gacha.GetStar5Weapon() << "��\n";
}

void Menu::CheatMenu() {
    int delta;
    std::cout << "\nġƮŰ ���: ��� ������ �����ϼ���: ";
    while (!(std::cin >> delta)) {
        std::cout << "�߸��� �Է��Դϴ�. ���ڸ� �Է����ּ���: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    jewels = delta;
    std::cout << "���� ���: " << jewels << "��\n";
    system("pause");
}