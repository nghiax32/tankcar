#ifndef ENGINE_H
#define ENGINE_H

#include<bits/stdc++.h>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
using namespace std;

class Engine
{
    public:
        static Engine* GetInstance()
        {
            return sInstance = (sInstance != nullptr)? sInstance : new Engine();
        }

        bool Init();
        void Load();
        void Menu();
        void Pause();
        void End();
        void Events();
        void Update();
        void Render();
        bool Clean();
        void Quit();

        SDL_Renderer* GetRenderer()
        {
            return mRenderer;
        }

        bool mIsRunning = false;
        bool mIsMenu = false;
        bool mIsPlaying = false;
        bool mIsPaused = false;
        bool mIsEnded = false;

    private:
        Engine() {}
        static Engine* sInstance;
        SDL_Window* mWindow = nullptr;
        SDL_Renderer* mRenderer = nullptr;
};

#endif // ENGINE_H
