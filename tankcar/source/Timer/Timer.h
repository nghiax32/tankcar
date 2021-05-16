#ifndef TIMER_H
#define TIMER_H

#include<bits/stdc++.h>
#include<SDL.h>
using namespace std;

class Timer
{
    public:
        static Timer* GetInstance()
        {
            return sInstance = (sInstance != nullptr)? sInstance : new Timer();
        }

        void Render();

        int start_time;
        int pause_time;

        inline int GetTime()
        {
            return SDL_GetTicks() - start_time;
        }

        inline string GetCurrentTime()
        {
            stringstream ss;
            ss << int(SDL_GetTicks()) / 1000 - start_time;
            string res = ss.str();
            res = string(4 - res.size(), '0') + res;
            return res;
        }

    private:
        Timer() {}
        static Timer* sInstance;
};

#endif // TIMER_H
