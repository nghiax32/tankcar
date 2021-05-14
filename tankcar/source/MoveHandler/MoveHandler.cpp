#include "MoveHandler.h"
#include "Global.h"

void TranslateX(string mTextureID, int mX)
{
    int X = Global::GetInstance()->mProsMap[mTextureID].x;
    int W = Global::GetInstance()->mProsMap[mTextureID].w;
    X += mX;
    if (X < 0) X = 0;
    if (X > SCREEN_WIDTH - W) X = SCREEN_WIDTH - W;
    Global::GetInstance()->mProsMap[mTextureID].x = X;
}

void TranslateY(string mTextureID, int mY)
{
    int Y = Global::GetInstance()->mProsMap[mTextureID].y;
    int H = Global::GetInstance()->mProsMap[mTextureID].h;
    Y += mY;
    if (Y < 0) Y = 0;
    if (Y > SCREEN_HEIGHT - H) Y = SCREEN_HEIGHT - H;
    Global::GetInstance()->mProsMap[mTextureID].y = Y;
}

bool CheckCollision(string id)
{
    SDL_Rect a = Global::GetInstance()->mProsMap[id];
    map<string, SDL_Rect> :: iterator it;
    for(it = Global::GetInstance()->mProsMap.begin(); it != Global::GetInstance()->mProsMap.end(); it++)
    {
        if(((it->first).substr(0, 5) == "TANK_" || (it->first).substr(0, 6) == "BLOCK_") && it->first != id)
        {
            SDL_Rect b = it->second;
            bool x_overlaps = (a.x <= b.x + b.w) && (a.x + a.w >= b.x);
            bool y_overlaps = (a.y <= b.y + b.h) && (a.y + a.h >= b.y);
            if(x_overlaps && y_overlaps) return true;
        }
    }
    return false;
}

int CheckBulletCollision(string id)
{
    SDL_Rect a = Global::GetInstance()->mProsMap[id];
    map<string, SDL_Rect> :: iterator it;
    int res = 0;
    for(it = Global::GetInstance()->mProsMap.begin(); it != Global::GetInstance()->mProsMap.end(); it++)
    {
        if(id.substr(0, 10) == "TANK_ENEMY")
        {
            if((it->first).substr(0, 13) == "BULLET_PLAYER")
            {
                SDL_Rect b = it->second;
                bool x_overlaps = (a.x <= b.x + b.w) && (a.x + a.w >= b.x);
                bool y_overlaps = (a.y <= b.y + b.h) && (a.y + a.h >= b.y);
                if(x_overlaps && y_overlaps) res++;
            }
        }
        else if(id.substr(0, 11) == "TANK_PLAYER")
        {
            if((it->first).substr(0, 12) == "BULLET_ENEMY")
            {
                SDL_Rect b = it->second;
                bool x_overlaps = (a.x <= b.x + b.w) && (a.x + a.w >= b.x);
                bool y_overlaps = (a.y <= b.y + b.h) && (a.y + a.h >= b.y);
                if(x_overlaps && y_overlaps) res++;
            }
        }
    }
    return res;
}

