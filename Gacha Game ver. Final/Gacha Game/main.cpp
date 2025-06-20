#include <iostream>
#include "Game.h"
#include "Menu.h"

int main() {
    Menu menu;
    int choice = 0;

    while (true) {
        choice = menu.Show();

        switch (choice) {
        case 1:
            menu.ShowDescription();
            system("pause");
            break;
        case 2: {
            Game game(menu.GetSelectedPlane(), menu.GetSelectedWeapon(), menu.GetJewelsRef());
            bool gameRunning = true;
            while (gameRunning) {
                game.Run();

                if (game.IsGameOver()) {
                    int postChoice;
                    std::cout << "\n1. 다시하기\n2. 메인화면으로 돌아가기\n선택: ";
                    std::cin >> postChoice;
                    if (postChoice == 2) {
                        system("cls");
                        gameRunning = false;
                    }
                    else {
                        game.Reset();
                    }
                }
            }
            break;
        }
        case 3:
            menu.GachaMenu();
            break;
        case 4:
            menu.HandleChangeOrStats();
            break;
        case 5:
            std::cout << "게임을 종료합니다.\n";
            return 0;
        default:
            std::cout << "잘못된 입력입니다.\n";
        }
    }
    return 0;
}