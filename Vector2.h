#ifndef VECTOR2_HPP_INCLUDED
#define VECTOR2_HPP_INCLUDED

#include <cmath>

const float PI = 3.14159265359;

class Vec2f
{
public:

    Vec2f() {}
    Vec2f(float x, float y) : x(x), y(y) {}

    float x = 0;
    float y = 0;

    Vec2f operator+(const Vec2f& rhv) const;
    Vec2f operator-(const Vec2f& rhv) const;
    Vec2f operator/(const Vec2f& rhv) const;
    Vec2f operator*(const Vec2f& rhv) const;
    Vec2f& operator=(const Vec2f& rhv);

    Vec2f operator*(float f) const;

    void rotateAroundPoint(const Vec2f& center, float angleInDegrees);

    void normalize();

    void limit(float maxVal);

    float length();
};

#endif //VECTOR2_HPP_INCLUDED
