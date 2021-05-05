#ifndef BULLET_H
#define BULLET_H

#include<bits/stdc++.h>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<SDL_mixer.h>
using namespace std;

class Bullet
{
    public:
        Bullet(string _id, int _x, int _y, int _angle);

        void Update();
        void Render();

        string mTextureID;
        int mWidth, mHeight;
        int mX, mY;
        int mAngle;

        int Speed = 4;

        bool Del = false;
};

#endif // TANK_H
