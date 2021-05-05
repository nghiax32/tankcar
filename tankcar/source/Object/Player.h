#ifndef PLAYER_H
#define PLAYER_H

#include<bits/stdc++.h>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<SDL_mixer.h>
using namespace std;

class Player
{
    public:
        Player(string _id, int _x, int _y, int _angle);

        void Update();
        void Render();

        string mTextureID;
        int mWidth, mHeight;
        int mX, mY;
        int mAngle;

        int LastTimeFire = 0;
        int BulletCount = 0;
        int Speed = 3;
        int HP = 30;

        int Score = 0;

        bool Del = false;
};



#endif // PLAYER_H
