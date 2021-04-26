#include "Enemy.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "EventHandler.h"

Enemy::Enemy(Properties* props) : GameObject(props)
{
    mAnimation = new Animation();
    mAnimation->SetProps(mTextureID, 0, 1, 60, 0);
}

void Enemy::Update(int X, int Y)
{
    const int Speed = 2;
    int dx = mTransform->X - X, dy = mTransform->Y - Y;
    if(dx != 0)
    {
        if(dx <= 0)
        {
            mAnimation->SetProps(mTextureID, 0, 1, 60, 90);
            mTransform->TranslateX(Speed);
        }
        else
        {
            mAnimation->SetProps(mTextureID, 0, 1, 60, -90);
            mTransform->TranslateX(-Speed);
        }
    }
    else if(dy != 0)
    {
        if(dy <= 0)
        {
            mAnimation->SetProps(mTextureID, 0, 1, 60, 180);
            mTransform->TranslateY(Speed);
        }
        else
        {
            mAnimation->SetProps(mTextureID, 0, 1, 60, 0);
            mTransform->TranslateY(-Speed);
        }
    }
}

void Enemy::Render()
{
    mAnimation->Render(mTransform->X, mTransform->Y, mWidth, mHeight);
}

void Enemy::Clean()
{
    TextureManager::GetInstance()->Clean();
}
