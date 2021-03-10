#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Engine.h"

#include <bits/stdc++.h>
using namespace std;

class Transform
{
    public:
        double X, Y;

    public:
        Transform(double x = 0, double y = 0) : X(x), Y(y) {}

        inline void TranslateX(double x)
        {
            X += x;
            if (X + TANK_SIZE > SCREEN_WIDTH) X = SCREEN_WIDTH;
            if (X < 0) X = 0;
        }

        inline void TranslateY(double y)
        {
            Y += y;
            if (Y + TANK_SIZE > SCREEN_HEIGHT) Y = SCREEN_HEIGHT;
            if (Y < 0) Y = 0;
        }
};

#endif // TRANSFORM_H
