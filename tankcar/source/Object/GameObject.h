#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Transform.h"
#include "TextureManager.h"

#include<bits/stdc++.h>
using namespace std;

struct Properties
{
    public:
    Properties(string _TextureID, double _X, double _Y)
    {
        TextureID = _TextureID;
        X = _X;
        Y = _Y;
        Width = TextureManager::GetInstance()->mProsMap[_TextureID]->w;
        Height = TextureManager::GetInstance()->mProsMap[_TextureID]->h;
    }

    public:
        string TextureID;
        double X, Y;
        int Width, Height;
};

class GameObject
{
    public:
        GameObject(Properties* props) : mTextureID(props->TextureID)
        {
            mWidth = TextureManager::GetInstance()->mProsMap[props->TextureID]->w;
            mHeight = TextureManager::GetInstance()->mProsMap[props->TextureID]->h;
            mTransform = new Transform(props->X, props->Y);
        }

    public:
        Transform* mTransform;
        string mTextureID;
        int mWidth, mHeight;
};

#endif // GAMEOBJECT_H
