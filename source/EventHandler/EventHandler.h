#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
using namespace std;

class EventHandler
{
    public:
        static EventHandler* GetInstance()
        {
            return sInstance = (sInstance != NULL)? sInstance : new EventHandler();
        }

        void Input();
        bool GetKeyDown(SDL_Scancode key);

    private:
        EventHandler()
        {
            mKeyStates = SDL_GetKeyboardState(nullptr);
        }
        static EventHandler* sInstance;
        void KeyUp();
        void KeyDown();
        const Uint8* mKeyStates;

};

#endif // EVENTHANDLER_H
