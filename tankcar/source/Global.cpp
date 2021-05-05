#include "Global.h"
#include "TextureManager.h"

Global* Global::sInstance = nullptr;

string Global::convert(int x)
{
    stringstream ss;
    ss << x;
    string res = ss.str();
    return res;
}

void Global::print(string id, int y)
{
    TextureManager::GetInstance()->Render(id,
                                          (SCREEN_WIDTH - Global::GetInstance()->mProsMap[id].w) / 2,
                                          y,
                                          Global::GetInstance()->mProsMap[id].w,
                                          Global::GetInstance()->mProsMap[id].h,
                                          0);
}

string TANK_ENEMY = "TANK_ENEMY";
string BULLET_PLAYER = "BULLET_PLAYER";
string BULLET_ENEMY = "BULLET_ENEMY";

void Global::spawn(int x, int y, int angle)
{
    TextureManager::GetInstance()->Load(TANK_ENEMY + convert(enemy_count), "images/tank2.png");
    enemy.push_back(new Enemy(TANK_ENEMY + convert(enemy_count), x, y, angle));
    enemy_count++;
}

void Global::player_fire(int x, int y, int angle)
{
    TextureManager::GetInstance()->Load(BULLET_PLAYER + convert(bullet_player_count), "images/bullet.png");
    bullet.push_back(new Bullet(BULLET_PLAYER + convert(bullet_player_count), x, y, angle));
    bullet_player_count++;
}

void Global::enemy_fire(int x, int y, int angle)
{
    TextureManager::GetInstance()->Load(BULLET_ENEMY + convert(bullet_enemy_count), "images/bullet.png");
    bullet.push_back(new Bullet(BULLET_ENEMY + convert(bullet_enemy_count), x, y, angle));
    bullet_enemy_count++;
}
