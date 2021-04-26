#include "Timer.h"
#include "TextureManager.h"

#include<bits/stdc++.h>
#include<SDL.h>
using namespace std;

Timer* Timer::sInstance = nullptr;

void Timer::Render()
{
    string id = Timer::GetInstance()->GetCurrentTime();
    int w = TextureManager::GetInstance()->mProsMap[id]->w;
    int h = TextureManager::GetInstance()->mProsMap[id]->h;
    //cout << w << ' ' << h << endl;
    TextureManager::GetInstance()->Render(id, 10, 10, w, h, 0);
}
