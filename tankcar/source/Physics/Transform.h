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
            if (X > SCREEN_WIDTH - TANK_SIZE) X = SCREEN_WIDTH - TANK_SIZE;
            if (X < 0) X = 0;
        }

        inline void TranslateY(double y)
        {
            Y += y;
            if (Y > SCREEN_HEIGHT - TANK_SIZE) Y = SCREEN_HEIGHT - TANK_SIZE;
            if (Y < 0) Y = 0;
        }
};

#endif // TRANSFORM_H
