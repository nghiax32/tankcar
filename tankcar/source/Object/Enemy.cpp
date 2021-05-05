#include "Enemy.h"
#include "TextureManager.h"
#include "EventHandler.h"
#include "MoveHandler.h"
#include "Timer.h"
#include "Global.h"

Enemy::Enemy(string _id, int _x, int _y, int _angle)
{
    mTextureID = _id;
    mWidth = Global::GetInstance()->mProsMap[_id].w;
    mHeight = Global::GetInstance()->mProsMap[_id].h;
    mX = _x;
    mY = _y;
    mAngle = 0;
    Global::GetInstance()->mProsMap[_id].x = _x;
    Global::GetInstance()->mProsMap[_id].y = _y;
}

void Enemy::Update(int X, int Y)
{
    int dx = Global::GetInstance()->mProsMap[mTextureID].x - X;
    int dy = Global::GetInstance()->mProsMap[mTextureID].y - Y;
    bool moved = false;

	int CurrentTime = Timer::GetInstance()->GetTime() / 1000;

    if(dx != 0 && CurrentTime % 3 != 0 && !moved)
    {
        if(dx <= 0)
        {
            mAngle = 90;
            TranslateX(mTextureID, Speed);
            moved = true;

            if(CheckCollision(mTextureID))
            {
                TranslateX(mTextureID, -Speed);
                moved = false;
            }
        }
        else if(!moved)
        {
            mAngle = -90;
            TranslateX(mTextureID, -Speed);
            moved = true;

            if(CheckCollision(mTextureID))
            {
                TranslateX(mTextureID, Speed);
                moved = false;
            }
        }
    }

    if(dy != 0 && (CurrentTime % 3 == 0 || !moved) )
    {
        if(dy <= 0)
        {
            mAngle = 180;
            TranslateY(mTextureID, Speed);
            moved = true;

            if(CheckCollision(mTextureID))
            {
                TranslateY(mTextureID, -Speed);
                moved = false;
            }
        }
        else if(!moved)
        {
            mAngle = 0;
            TranslateY(mTextureID, -Speed);
            moved = true;

            if(CheckCollision(mTextureID))
            {
                TranslateY(mTextureID, Speed);
                moved = false;
            }
        }
    }

    mX = Global::GetInstance()->mProsMap[mTextureID].x;
    mY = Global::GetInstance()->mProsMap[mTextureID].y;

    CurrentTime = Timer::GetInstance()->GetTime();
    if(CurrentTime - LastTimeFire >= 1000)
    {
        int _x, _y, _angle;

        if(mAngle == 0)
        {
            _x = mX + (TANK_SIZE - BULLET_SIZE) / 2;
            _y = mY - BULLET_SIZE;
        }
        else if(mAngle == 90)
        {
            _x = mX + TANK_SIZE;
            _y = mY + (TANK_SIZE - BULLET_SIZE) / 2;
        }
        else if(mAngle == 180)
        {
            _x = mX + (TANK_SIZE - BULLET_SIZE) / 2;
            _y = mY + TANK_SIZE;
        }
        else if(mAngle == -90)
        {
            _x = mX - BULLET_SIZE;
            _y = mY + (TANK_SIZE - BULLET_SIZE) / 2;
        }

        _angle = mAngle;

        Global::GetInstance()->enemy_fire(_x, _y, _angle);

        LastTimeFire = CurrentTime;
    }

    HP -= CheckBulletCollision(mTextureID);
    if(HP <= 0) Del = true;
}

void Enemy::Render()
{
    TextureManager::GetInstance()->Render(mTextureID, mX, mY, mWidth, mHeight, mAngle);
}
