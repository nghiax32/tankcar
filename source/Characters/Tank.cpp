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
    mAnimation->Render(mTransform->X, mTransform->Y, mWidth, mHeight, mAngle);
}

void Tank::Update()
{

    if(EventHandler::GetInstance()->GetKeyDown(SDL_SCANCODE_A))
    {
        mAnimation->SetProps(mTextureID, 0, 1, 60, -90);
        mAnimation->mAngle = 180;
        mTransform->TranslateX(-2);
    }

    if(EventHandler::GetInstance()->GetKeyDown(SDL_SCANCODE_D))
    {
        mAnimation->SetProps(mTextureID, 0, 1, 60, 90);
        mTransform->TranslateX(2);
    }

    if(EventHandler::GetInstance()->GetKeyDown(SDL_SCANCODE_W))
    {
        mAnimation->SetProps(mTextureID, 0, 1, 60, 0);
        mTransform->TranslateY(-2);
    }

    if(EventHandler::GetInstance()->GetKeyDown(SDL_SCANCODE_S))
    {
        mAnimation->SetProps(mTextureID, 0, 1, 60, 180);
        mTransform->TranslateY(2);
    }

    mAnimation->Update();
}

void Tank::Clean()
{
    TextureManager::GetInstance()->Clean();
}

