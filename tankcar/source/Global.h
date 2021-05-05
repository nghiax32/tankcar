#ifndef GLOBAL_H
#define GLOBAL_H

#include "Enemy.h"
#include "Bullet.h"

#include <bits/stdc++.h>
using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int TANK_SIZE = 64;
const int BULLET_SIZE = 16;

class Global
{
    public:
        static Global* GetInstance()
        {
            return sInstance = (sInstance != nullptr)? sInstance : new Global();
        }

        map<string, SDL_Texture*> mTextureMap;
        map<string, SDL_Rect> mProsMap;

        vector<Enemy*> enemy;
        int enemy_count = 0;

        vector<Bullet*> bullet;
        int bullet_player_count = 0;
        int bullet_enemy_count = 0;

        int Point = 0;

        string convert(int x);

        void print(string id, int y);

        void spawn(int x, int y, int angle);

        void player_fire(int x, int y, int angle);

        void enemy_fire(int x, int y, int angle);

        void print_point();

    private:
        Global() {}
        static Global* sInstance;
};

#endif // GLOBAL_H
