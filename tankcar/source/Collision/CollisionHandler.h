#ifndef COLLISIONHANDLER_H
#define COLLISIONHANDLER_H

#include<bits/stdc++.h>
#include<SDL.h>
using namespace std;

class CollisionHandler
{
    public:
        static CollisionHandler* GetInstance()
        {
            return sInstance = (sInstance != nullptr)? sInstance : new CollisionHandler();
        }

        bool MapCollision(SDL_Rect a);
        bool CheckCollision(SDL_Rect a, SDL_Rect b);

    private:
        CollisionHandler();
        static CollisionHandler* sInstance;
};

#endif // COLLISIONHANDLER_H
