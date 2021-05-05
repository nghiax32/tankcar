#include "Timer.h"
#include "TextureManager.h"
#include "Global.h"

#include<bits/stdc++.h>
#include<SDL.h>
using namespace std;

Timer* Timer::sInstance = nullptr;

void Timer::Render()
{
    string id = Timer::GetInstance()->GetCurrentTime();
    int w = Global::GetInstance()->mProsMap[id].w;
    int h = Global::GetInstance()->mProsMap[id].h;
    TextureManager::GetInstance()->Render(id, 10, 10, w, h, 0);
}
