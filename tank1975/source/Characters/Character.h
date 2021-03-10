#ifndef CHARACTER_H
#define CHARACTER_H

#include "GameObject.h"

#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
using namespace std;

class Character : public GameObject
{
    public:
        Character(Properties* props) : GameObject(props) {}

        virtual void Render() = 0;
        virtual void Update() = 0;
        virtual void Clean() = 0;

    public:
        string m_Name;
};

#endif // CHARACTER_H
