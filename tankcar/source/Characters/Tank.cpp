#include "Tank.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "EventHandler.h"

Tank::Tank(Properties* props) : Character(props)
{
    mAnimation = new Animation();
    mAnimation->SetProps(mTextureID, 0, 1, 60, 0);
}

void Tank::Render()
{
    mAnimation->Render(mTransform->X, mTransform->Y, mWidth, mHeight);
}

void Tank::Update()
{
    const int Speed = 3;

    if(EventHandler::GetInstance()->GetKeyDown(SDL_SCANCODE_A))
    {
        mAnimation->SetProps(mTextureID, 0, 1, 60, -90);
        mTransform->TranslateX(-Speed);
    }

    if(EventHandler::GetInstance()->GetKeyDown(SDL_SCANCODE_D))
    {
        mAnimation->SetProps(mTextureID, 0, 1, 60, 90);
        mTransform->TranslateX(Speed);
    }

    if(EventHandler::GetInstance()->GetKeyDown(SDL_SCANCODE_W))
    {
        mAnimation->SetProps(mTextureID, 0, 1, 60, 0);
        mTransform->TranslateY(-Speed);
    }

    if(EventHandler::GetInstance()->GetKeyDown(SDL_SCANCODE_S))
    {
        mAnimation->SetProps(mTextureID, 0, 1, 60, 180);
        mTransform->TranslateY(Speed);
    }

    mAnimation->Update();
}

void Tank::Clean()
{
    TextureManager::GetInstance()->Clean();
}

