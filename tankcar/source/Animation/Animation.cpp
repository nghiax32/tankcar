#include "Animation.h"
#include "TextureManager.h"

void Animation::Update()
{
    mSpriteFrame = (SDL_GetTicks() / mAnimationSpeed) % mFrameCount;
}

void Animation::Render(double x, double y, int SpritWidth, int SpritHeight)
{
    TextureManager::GetInstance()->RenderFrame(mTextureID, x, y, SpritWidth, SpritHeight, mAngle, mSpriteRow, mSpriteFrame);
    //cout << mTextureID << ' ' << mSpriteRow << ' ' << mSpriteFrame << endl;
}

void Animation::SetProps(string _TextureID, int _SpriteRow, int _FrameCount, int _AnimationSpeed, int _Angle)
{
    mTextureID = _TextureID;
    mSpriteRow = _SpriteRow;
    mFrameCount = _FrameCount;
    mAnimationSpeed = _AnimationSpeed;
    mAngle = _Angle;
}
