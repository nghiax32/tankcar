#ifndef MOVEHANDLER_H
#define MOVEHANDLER_H

#include "TextureManager.h"

#include<bits/stdc++.h>
using namespace std;

void TranslateX(string mTextureID, int mX);

void TranslateY(string mTextureID, int mY);

bool CheckCollision(string id);

int CheckBulletCollision(string id);

#endif // MOVEHANDLER_H
