#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Transform.h"

#include <bits/stdc++.h>
#include <SDL.h>
using namespace std;

struct Properties
{
    public:
    Properties(string _TextureID, double _X, double _Y, int _Width, int _Height)
    {
        TextureID = _TextureID;
        X = _X;
        Y = _Y;
        Width = _Width;
        Height = _Height;
    }

    public:
        string TextureID;
        double X, Y;
        int Width, Height;
};

class GameObject
{
    public:
        GameObject(Properties* props) : mTextureID(props->TextureID), mWidth(props->Width), mHeight(props->Height)
        {
            mTransform = new Transform(props->X, props->Y);
        }

        virtual void Render() = 0;
        virtual void Update() = 0;
        virtual void Clean() = 0;

    public:
        Transform* mTransform;
        string mTextureID;
        int mWidth, mHeight;
};

#endif // GAMEOBJECT_H
