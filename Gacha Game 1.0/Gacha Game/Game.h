#pragma once
#include <vector>
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"

class Game {
private:
    Player player;
    Enemy enemy;
    std::vector<Bullet> bullets;
    int fireCooldown;
    const int fireRate;
    const int speed;
    char input;
    int lives;
    bool gameOver;
    int kills;             
public:
    Game();
    void Init();
    void Input();
    void Update();
    void Render();
    void Run();
    bool IsGameOver();
    void Reset();

private:
    void CheckHit();
    bool PlayerHit();
    bool IsBulletAt(int x, int y);
    void RenderLives();
};