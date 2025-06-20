#include "Gacha.h"
#include <iostream>
#include <ctime>
#include <limits>
#include <random>

Gacha::Gacha(int& jewelsRef)
    : jewels(jewelsRef),
    pityBody(0), guardBody(0),
    pityWeapon(0), guardWeapon(0),
    bodyCount(0), weaponCount(0),
    star3(0), star4(0),
    star5Plane(0), star5Weapon(0), star5Fail(0),
    rng(static_cast<unsigned>(time(nullptr))) {
}

int Gacha::GetUserInput(int min, int max) {
    int choice;
    while (true) {
        std::cout << "腰硲研 識澱馬室推: ";
        if (!(std::cin >> choice)) {
            std::cout << "設公吉 脊径脊艦陥. 収切研 脊径背爽室推.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        if (choice < min || choice > max) {
            std::cout << "骨是 鎧 収切研 脊径背爽室推.\n";
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return choice;
    }
}

void Gacha::ShowGachaMenu() {
    while (true) {
        system("cls");
        std::cout << "\n===== 亜鱈 五敢 =====\n";
        std::cout << "相杖: " << jewels << "鯵\n";
        if (!currentResults.empty()) {
            std::cout << "\n--- 戚穿 亜鱈 衣引 ---\n";
            PrintResults();
            std::cout << "\n恥 嗣奄 判呪: "
                << (bodyCount + weaponCount)
                << "噺\n";
        }
        std::cout << "\n1. 穿燈奄 郊巨 亜鱈\n2. 穿遂 巷奄 亜鱈\n3. 宜焼亜奄\n";
        int choice = GetUserInput(1, 3);
        if (choice == 3) { currentResults.clear(); system("cls"); return; }

        while (true) {
            system("cls");
            std::cout << (choice == 1 ? "\n=== 穿燈奄 郊巨 亜鱈 ===\n" : "\n=== 穿遂 巷奄 亜鱈 ===\n");
            std::cout << "相杖: " << jewels << "鯵\n";
            if (!currentResults.empty()) {
                std::cout << "\n--- 刊旋 亜鱈 衣引 ---\n";
                PrintResults();
                std::cout << "\n恥 嗣奄 判呪: "
                    << (bodyCount + weaponCount)
                    << "噺\n";
            }
            std::cout << "\n1. 1噺 亜鱈 (1 相杖)\n2. 10噺 亜鱈 (10 相杖)\n3. 宜焼亜奄\n";
            int sub = GetUserInput(1, 3);
            if (sub == 3) { currentResults.clear(); system("cls"); break; }
            RunGacha(sub == 1 ? 1 : 10, choice == 1);
        }
    }
}

void Gacha::RunGacha(int count, bool isBody) {
    int start = currentResults.size();
    int& pity = isBody ? pityBody : pityWeapon;
    int& guarantee = isBody ? guardBody : guardWeapon;
    int& gCount = isBody ? bodyCount : weaponCount;

    for (int i = 0; i < count && jewels > 0; ++i) {
        --jewels; ++pity; ++gCount;
        bool wasG = (guarantee == 1);
        auto raw = Roll(pity, isBody, wasG);
        if (raw.find("5失") != std::string::npos)
            PrintSpecialMessage(raw);

        if (raw == "奄歳 疏精 4失")   ++star4;
        else if (raw == "承乞 蒸澗 3失")    ++star3;
        else if (raw == "置壱厭 5失 穿燈奄") ++star5Plane;
        else if (raw == "5失 巷奄")         ++star5Weapon;
        else if (raw == "歌 5失")           ++star5Fail;

        currentResults.push_back(raw);
        if (raw == "置壱厭 5失 穿燈奄" || raw == "5失 巷奄") {
            guarantee = 0; pity = 0;
        }
        else if (raw == "歌 5失") {
            guarantee = 1; pity = 0;
        }
    }
    if (count == 10) {
        bool ok = false;
        for (int i = start; i < (int)currentResults.size(); ++i) {
            auto& r = currentResults[i];
            if (r == "奄歳 疏精 4失" || r.find("5失") != std::string::npos) { ok = true; break; }
        }
        if (!ok && !currentResults.empty()) {
            auto& last = currentResults.back();
            last = "奄歳 疏精 4失";
            --star3; ++star4;
        }
    }
}

std::string Gacha::Roll(int pity, bool isBody, bool guaranteed) {
    const double b5 = 0.008, b4 = 0.06;
    double p = pity <= 55 ? b5 : pity < 80 ? b5 + (pity - 55) * (1 - b4 - b5) / 25 : 1;
    std::uniform_real_distribution<double> d(0, 1);
    double r = d(rng);
    if (r < p) {
        if (isBody) {
            if (guaranteed) return "置壱厭 5失 穿燈奄";
            std::uniform_int_distribution<int> f(0, 1);
            return f(rng) ? "歌 5失" : "置壱厭 5失 穿燈奄";
        }
        return "5失 巷奄";
    }
    else if (r < p + b4) return "奄歳 疏精 4失";
    return "承乞 蒸澗 3失";
}

void Gacha::PrintResults() {
    for (auto& i : currentResults) std::cout << "- " << i << "\n";
}

void Gacha::PrintSpecialMessage(const std::string& r) {
    if (r.find("5失") != std::string::npos)
        std::cout << "\n***** " << (r == "歌 5失" ? "ばばばばばば 焼戚壱 舷社紫 焼襲陥 焼猿趨虞!!!!!! 歌 5失戚革推~~~ 益掘亀 5失昔汽 逐馬廃陥革 ばばばばばばせ" : "逐馬杯艦陥! " + r + " 雁歎!") << " *****\n";
    system("pause");
}