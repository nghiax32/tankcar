#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <bits/stdc++.h>
using namespace std;

class Transform
{
    public:
        double X, Y;

    public:
        Transform(double x = 0, double y = 0) : X(x), Y(y) {}

        inline void TranslateX(double x) {X += x;}
        inline void TranslateY(double y) {Y += y;}
};

#endif // TRANSFORM_H
