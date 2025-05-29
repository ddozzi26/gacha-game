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
        std::cout << "\n===== 슈팅 게임 메뉴 =====\n\n";
        std::cout << "1. 게임 설명\n";
        std::cout << "2. 슈팅 게임 시작\n";
        std::cout << "3. 가챠 (현재 쥬얼: " << jewels << "개)\n";
        std::cout << "4. 전투기 변경 및 가챠 기록 확인\n";
        std::cout << "5. 게임 종료\n";

        bool cheat = false;
        std::string inputStr;
        int input = 0;
        while (true) {
            std::cout << "번호를 선택하세요: ";
            std::cin >> inputStr;
            if (inputStr == "치트키") {
                CheatMenu();
                cheat = true;
                break;
            }
            try {
                input = std::stoi(inputStr);
            }
            catch (...) {
                std::cout << "잘못된 입력입니다. 숫자를 입력해주세요.\n";
                continue;
            }
            if (input < 1 || input > 5) {
                std::cout << "범위 내 숫자를 입력해주세요.\n";
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
            std::cout << "게임을 종료합니다.\n";
            exit(0);
        default:
            system("pause");
            break;
        }
    }
}

void Menu::ShowDescription() {
    std::cout << "\n게임 설명:\n";
    std::cout << "W/S 키로 전투기를 위/아래로 이동하세요.\n";
    std::cout << "스페이스바로 총알을 발사해 적을 격추하세요.\n";
    std::cout << "적과 충돌하면 게임이 종료됩니다.\n\n";
}

void Menu::GachaMenu() {
    gacha.ShowGachaMenu();
}

void Menu::ChangeFighter() {
    std::cout << "\n=== 전투기/무기 변경 ===\n";
    std::cout << "전투기 선택:\n";
    std::cout << "1. 기본 전투기\n";
    if (gacha.GetStar5Plane() > 0) std::cout << "2. 5성 전투기\n";
    int pChoice = 1;
    std::cin >> pChoice;
    selectedPlane = (pChoice == 2 && gacha.GetStar5Plane() > 0);

    std::cout << "무기 선택:\n";
    std::cout << "1. 기본 무기\n";
    if (gacha.GetStar5Weapon() > 0) std::cout << "2. 5성 무기\n";
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
        std::cout << "쥬얼이 부족합니다.\n";
        return false;
    }
}

void Menu::ShowGachaStats() {
    std::cout << "\n=== 가챠 기록 ===\n";
    std::cout << "3성: " << gacha.GetStar3() << "개\n";
    std::cout << "4성: " << gacha.GetStar4() << "개\n";
    std::cout << "5성 전투기: " << gacha.GetStar5Plane() << "개\n";
    std::cout << "5성 무기: " << gacha.GetStar5Weapon() << "개\n";
}

void Menu::CheatMenu() {
    int delta;
    std::cout << "\n치트키 모드: 쥬얼 갯수를 조정하세요: ";
    while (!(std::cin >> delta)) {
        std::cout << "잘못된 입력입니다. 숫자를 입력해주세요: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    jewels = delta;
    std::cout << "현재 쥬얼: " << jewels << "개\n";
    system("pause");
}