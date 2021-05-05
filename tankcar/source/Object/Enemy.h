#ifndef ENEMY_H
#define ENEMY_H

#include<bits/stdc++.h>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<SDL_mixer.h>
using namespace std;

class Enemy
{
    public:
        Enemy(string _id, int _x, int _y, int _angle);

        void Update(int X, int Y);
        void Render();

        string mTextureID;
        int mWidth, mHeight;
        int mX, mY;
        int mAngle;

        int LastTimeFire = 0;
        int BulletCount = 0;
        int Speed = 1;
        int HP = 1;

        bool Del = false;
};

#endif // ENEMY_H
