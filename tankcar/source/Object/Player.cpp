#include "Player.h"
#include "TextureManager.h"
#include "EventHandler.h"
#include "MoveHandler.h"
#include "Timer.h"
#include "Bullet.h"
#include "Global.h"

Player::Player(string _id, int _x, int _y, int _angle)
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

void Player::Update()
{
    if(EventHandler::GetInstance()->GetKeyDown(SDL_SCANCODE_A))
    {
        mAngle = -90;
        TranslateX(mTextureID, -Speed);

        if(CheckCollision(mTextureID))
            TranslateX(mTextureID, Speed);
    }

    else if(EventHandler::GetInstance()->GetKeyDown(SDL_SCANCODE_D))
    {
        mAngle = 90;
        TranslateX(mTextureID, Speed);

        if(CheckCollision(mTextureID))
            TranslateX(mTextureID, -Speed);
    }

    else if(EventHandler::GetInstance()->GetKeyDown(SDL_SCANCODE_W))
    {
        mAngle = 0;
        TranslateY(mTextureID, -Speed);

        if(CheckCollision(mTextureID))
            TranslateY(mTextureID, Speed);
    }

    else if(EventHandler::GetInstance()->GetKeyDown(SDL_SCANCODE_S))
    {
        mAngle = 180;
        TranslateY(mTextureID, Speed);

        if(CheckCollision(mTextureID))
            TranslateY(mTextureID, -Speed);
    }

    mX = Global::GetInstance()->mProsMap[mTextureID].x;
    mY = Global::GetInstance()->mProsMap[mTextureID].y;

    if(EventHandler::GetInstance()->GetKeyDown(SDL_SCANCODE_SPACE))
    {
        int CurrentTime = Timer::GetInstance()->GetTime();
        if(CurrentTime - LastTimeFire >= 500)
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

            Global::GetInstance()->player_fire(_x, _y, _angle);

            LastTimeFire = CurrentTime;
        }
    }

    HP -= CheckBulletCollision(mTextureID);

    if(HP <= 0) Del = true;
}

void Player::Render()
{
    TextureManager::GetInstance()->Render(mTextureID, mX, mY, mWidth, mHeight, mAngle);
}
