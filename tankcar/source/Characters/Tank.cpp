#include "Tank.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "EventHandler.h"

Tank::Tank(Properties* props) : GameObject(props)
{
    mAnimation = new Animation();
    mAnimation->SetProps(mTextureID, 0, 1, 60, 0);
}

void Tank::Update()
{
    const int Speed = 4;

    if(EventHandler::GetInstance()->GetKeyDown(SDL_SCANCODE_A))
    {
        mAnimation->SetProps(mTextureID, 0, 1, 60, -90);
        mTransform->TranslateX(-Speed);
    }

    else if(EventHandler::GetInstance()->GetKeyDown(SDL_SCANCODE_D))
    {
        mAnimation->SetProps(mTextureID, 0, 1, 60, 90);
        mTransform->TranslateX(Speed);
    }

    else if(EventHandler::GetInstance()->GetKeyDown(SDL_SCANCODE_W))
    {
        mAnimation->SetProps(mTextureID, 0, 1, 60, 0);
        mTransform->TranslateY(-Speed);
    }

    else if(EventHandler::GetInstance()->GetKeyDown(SDL_SCANCODE_S))
    {
        mAnimation->SetProps(mTextureID, 0, 1, 60, 180);
        mTransform->TranslateY(Speed);
    }

    if(EventHandler::GetInstance()->GetKeyDown(SDL_SCANCODE_SPACE))
    {

    }

    mAnimation->Update();
}

void Tank::Render()
{
    mAnimation->Render(mTransform->X, mTransform->Y, mWidth, mHeight);
}

void Tank::Clean()
{
    TextureManager::GetInstance()->Clean();
}

