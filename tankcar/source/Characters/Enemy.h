#ifndef ENEMY_H
#define ENEMY_H

#include "GameObject.h"
#include "Animation.h"

#include<bits/stdc++.h>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<SDL_mixer.h>
using namespace std;

class Enemy : public GameObject
{
    public:
        Enemy(Properties* pros);

        void Update(int X, int Y);
        void Render();
        void Clean();
    private:
        Animation* mAnimation;
};

#endif // ENEMY_H
