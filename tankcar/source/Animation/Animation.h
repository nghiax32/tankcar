#ifndef ANIMATION_H
#define ANIMATION_H

#include<bits/stdc++.h>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<SDL_mixer.h>
using namespace std;

class Animation
{
    public:
        Animation() {}

        void Update();
        void Render(double x, double y, int SpritWidth, int SpritHeight);
        void SetProps(string _TextureID, int _SpriteRow, int _FrameCount, int _AnimationSpeed, int _Angle);

    public:
        int mSpriteRow, mSpriteFrame;
        int mAnimationSpeed, mFrameCount;
        string mTextureID;
        int mAngle;
};

#endif // ANIMATION_H
