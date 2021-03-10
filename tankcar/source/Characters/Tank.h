#ifndef TANK_H
#define TANK_H

#include "GameObject.h"
#include "Animation.h"

#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
using namespace std;

class Tank : public GameObject
{
    public:
        Tank(Properties* pros);

        virtual void Render();
        virtual void Update();
        virtual void Clean();

    private:
        Animation* mAnimation;
};

#endif // TANK_H
