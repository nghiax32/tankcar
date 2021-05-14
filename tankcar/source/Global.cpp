#include "Global.h"
#include "TextureManager.h"
#include "MoveHandler.h"

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
    if(CheckCollision(TANK_ENEMY + convert(enemy_count)))
    {
        enemy.pop_back();
        SDL_DestroyTexture(mTextureMap[TANK_ENEMY + convert(enemy_count)]);
        delete(enemy.back());
        mTextureMap.erase(TANK_ENEMY + convert(enemy_count));
        mProsMap.erase(TANK_ENEMY + convert(enemy_count));
    }
    enemy_count++;
}

void Global::place()
{
    TextureManager::GetInstance()->Load("BLOCK_0", "images/block1.png");
    TextureManager::GetInstance()->Load("BLOCK_1", "images/block2.png");
    TextureManager::GetInstance()->Load("BLOCK_2", "images/block2.png");
    TextureManager::GetInstance()->Load("BLOCK_3", "images/block1.png");

    TextureManager::GetInstance()->Load("BLOCK_4", "images/block2.png");
    TextureManager::GetInstance()->Load("BLOCK_5", "images/block1.png");
    TextureManager::GetInstance()->Load("BLOCK_6", "images/block2.png");
    TextureManager::GetInstance()->Load("BLOCK_7", "images/block1.png");

    mProsMap["BLOCK_0"].x = 0; mProsMap["BLOCK_0"].y = 100;
    mProsMap["BLOCK_1"].x = 800 - 100 - 64; mProsMap["BLOCK_1"].y = 0;
    mProsMap["BLOCK_2"].x = 100; mProsMap["BLOCK_2"].y = 600 - 128;
    mProsMap["BLOCK_3"].x = 800 - 128; mProsMap["BLOCK_3"].y = 600 - 100 - 64;

    mProsMap["BLOCK_4"].x = 800/2 - 64/2; mProsMap["BLOCK_4"].y = 600/2 - 64/2 - 128;
    mProsMap["BLOCK_5"].x = 800/2 - 64/2 - 128; mProsMap["BLOCK_5"].y = 600/2 - 64/2;
    mProsMap["BLOCK_6"].x = 800/2 - 64/2; mProsMap["BLOCK_6"].y = 600/2 + 64/2;
    mProsMap["BLOCK_7"].x = 800/2 + 64/2; mProsMap["BLOCK_7"].y = 600/2 - 64/2;
}

void Global::render_block()
{
    TextureManager::GetInstance()->Render("BLOCK_0", mProsMap["BLOCK_0"].x, mProsMap["BLOCK_0"].y, mProsMap["BLOCK_0"].w, mProsMap["BLOCK_0"].h, 0);
    TextureManager::GetInstance()->Render("BLOCK_1", mProsMap["BLOCK_1"].x, mProsMap["BLOCK_1"].y, mProsMap["BLOCK_1"].w, mProsMap["BLOCK_1"].h, 0);
    TextureManager::GetInstance()->Render("BLOCK_2", mProsMap["BLOCK_2"].x, mProsMap["BLOCK_2"].y, mProsMap["BLOCK_2"].w, mProsMap["BLOCK_2"].h, 0);
    TextureManager::GetInstance()->Render("BLOCK_3", mProsMap["BLOCK_3"].x, mProsMap["BLOCK_3"].y, mProsMap["BLOCK_3"].w, mProsMap["BLOCK_3"].h, 0);

    TextureManager::GetInstance()->Render("BLOCK_4", mProsMap["BLOCK_4"].x, mProsMap["BLOCK_4"].y, mProsMap["BLOCK_4"].w, mProsMap["BLOCK_4"].h, 0);
    TextureManager::GetInstance()->Render("BLOCK_5", mProsMap["BLOCK_5"].x, mProsMap["BLOCK_5"].y, mProsMap["BLOCK_5"].w, mProsMap["BLOCK_5"].h, 0);
    TextureManager::GetInstance()->Render("BLOCK_6", mProsMap["BLOCK_6"].x, mProsMap["BLOCK_6"].y, mProsMap["BLOCK_6"].w, mProsMap["BLOCK_6"].h, 0);
    TextureManager::GetInstance()->Render("BLOCK_7", mProsMap["BLOCK_7"].x, mProsMap["BLOCK_7"].y, mProsMap["BLOCK_7"].w, mProsMap["BLOCK_7"].h, 0);
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
