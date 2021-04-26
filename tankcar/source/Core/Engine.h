#ifndef ENGINE_H
#define ENGINE_H

#include<bits/stdc++.h>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int TANK_SIZE = 64;

class Engine
{
    public:
        static Engine* GetInstance()
        {
            return sInstance = (sInstance != nullptr)? sInstance : new Engine();
        }

        bool Init();
        void Events();
        void Update();
        void Render();
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
        SDL_Window* mWindow = nullptr;
        SDL_Renderer* mRenderer = nullptr;
};

#endif // ENGINE_H
