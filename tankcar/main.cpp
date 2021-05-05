#include "Engine.h"

#include<bits/stdc++.h>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<SDL_mixer.h>
using namespace std;

int main(int argc, char* args[])
{
    Engine::GetInstance()->Init();
    Engine::GetInstance()->Load();

    while(Engine::GetInstance()->mIsRunning)
    {
        Engine::GetInstance()->Events();

        if(Engine::GetInstance()->mIsMenu)
        {
            Engine::GetInstance()->Menu();
        }
        else if(Engine::GetInstance()->mIsPlaying)
        {
            Engine::GetInstance()->Update();
            Engine::GetInstance()->Render();
        }
        else if(Engine::GetInstance()->mIsPaused)
        {
            Engine::GetInstance()->Pause();
        }
        else if(Engine::GetInstance()->mIsEnded)
        {
            Engine::GetInstance()->End();
        }
    }

    Engine::GetInstance()->Clean();

    return 0;
}
