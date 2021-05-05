#include "Bullet.h"
#include "TextureManager.h"
#include "EventHandler.h"
#include "MoveHandler.h"
#include "Timer.h"
#include "Global.h"

Bullet::Bullet(string _id, int _x, int _y, int _angle)
{
    mTextureID = _id;
    mWidth = Global::GetInstance()->mProsMap[_id].w;
    mHeight = Global::GetInstance()->mProsMap[_id].h;
    mX = _x;
    mY = _y;
    mAngle = _angle;
    Global::GetInstance()->mProsMap[_id].x = _x;
    Global::GetInstance()->mProsMap[_id].y = _y;
}

void Bullet::Update()
{
    if(mAngle == 0)
    {
        TranslateY(mTextureID, -Speed);
    }
    else if(mAngle == 90)
    {
        TranslateX(mTextureID, Speed);
    }
    else if(mAngle == 180)
    {
        TranslateY(mTextureID, Speed);
    }
    else if(mAngle == -90)
    {
        TranslateX(mTextureID, -Speed);
    }

    mX = Global::GetInstance()->mProsMap[mTextureID].x;
    mY = Global::GetInstance()->mProsMap[mTextureID].y;

    if(CheckCollision(mTextureID) || mX == 0 || mX == SCREEN_WIDTH - mWidth || mY == 0 || mY == SCREEN_HEIGHT - mHeight)
    {
        Del = true;
    }
}

void Bullet::Render()
{

    TextureManager::GetInstance()->Render(mTextureID, mX, mY, mWidth, mHeight, mAngle);
}
