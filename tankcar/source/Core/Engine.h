#ifndef ENGINE_H
#define ENGINE_H

#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int TANK_SIZE = 64;

class Engine
{
    public:
        static Engine* GetInstance()
        {
            return sInstance = (sInstance != NULL)? sInstance : new Engine();
        }

        bool Init();
        void Update();
        void Render();
        void Events();
        bool Clean();
        void Quit();

        bool IsRunning()
        {
            return mIsRunning;
        }

        SDL_Renderer* GetRenderer()
        {
            return mRenderer;
        }

    private:
        Engine() {}
        static Engine* sInstance;
        bool mIsRunning;
        SDL_Window* mWindow = NULL;
        SDL_Renderer* mRenderer = NULL;
        TTF_Font *mFont = NULL;
        Mix_Music *mStartMenuMusic = NULL;
};

#endif // ENGINE_H
