#include "Vector2.h"

Vec2f Vec2f::operator+(const Vec2f& rhv) const
{
    return Vec2f{x + rhv.x, y + rhv.y};
}

Vec2f Vec2f::operator-(const Vec2f& rhv) const
{
    return Vec2f{x - rhv.x, y - rhv.y};
}

Vec2f Vec2f::operator/(const Vec2f& rhv) const
{
    return Vec2f{x / rhv.x, y / rhv.y};
}

Vec2f Vec2f::operator*(const Vec2f& rhv) const
{
    return Vec2f{x * rhv.x, y * rhv.y};
}

Vec2f& Vec2f::operator=(const Vec2f& rhv)
{
    x = rhv.x;
    y = rhv.y;
    return *this;
}

Vec2f Vec2f::operator*(float f) const
{
    return Vec2f{x * f, y * f};
}

float Vec2f::length()
{
    return sqrt(x*x + y*y);
}

void Vec2f::normalize()
{
    float length = this->length();

    if (length != 0)
    {
        x /= length;
        y /= length;
    }
}

void Vec2f::limit(float maxVal)
{
    if (x > maxVal)
    {
        x = maxVal;
    }
    else if (x < -maxVal)
    {
        x = -maxVal;
    }

    if (y > maxVal)
    {
        y = maxVal;
    }
    else if (y < -maxVal)
    {
        y = -maxVal;
    }
}

// Rotates this point around center by angleInDegrees
void Vec2f::rotateAroundPoint(const Vec2f& center, float angleInDegrees)
{
    float rad = angleInDegrees * PI / 180.f;

    float co = cos(rad);
    float si = sin(rad);

    float newX = (co * (x - center.x) - si * (y - center.y)) + center.x;
    float newY = (si * (x - center.x) + co * (y - center.y)) + center.y;

    x = newX;
    y = newY;
}
