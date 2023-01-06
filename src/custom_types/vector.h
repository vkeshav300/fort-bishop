// Comments found in "vector.cpp"
#pragma once
#include <iostream>

struct Vector2D
{
    float x;
    float y;

    // Constructors
    Vector2D()
    {
        x = 0.0f;
        y = 0.0f;
    }

    Vector2D(float x, float y)
    {
        this->x = x;
        this->y = y;
    }

    // Basic operations
    Vector2D &add(const Vector2D &vec)
    {
        this->x += vec.x;
        this->y += vec.y;

        return *this;
    }

    Vector2D &subtract(const Vector2D &vec)
    {
        this->x -= vec.x;
        this->y -= vec.y;

        return *this;
    }

    Vector2D &multiply(const Vector2D &vec)
    {
        this->x *= vec.x;
        this->y *= vec.y;

        return *this;
    }

    Vector2D &divide(const Vector2D &vec)
    {
        this->x /= vec.x;
        this->y /= vec.y;

        return *this;
    }

    // + - * / operators
    friend const Vector2D &operator+(Vector2D &v1, Vector2D &v2)
    {
        const Vector2D &r_v2d = Vector2D(v1.x + v2.x, v1.y + v2.y);
        return r_v2d;
    }

    friend const Vector2D &operator-(Vector2D &v1, Vector2D &v2)
    {
        const Vector2D &r_v2d = Vector2D(v1.x - v2.x, v1.y - v2.y);
        return r_v2d;
    }

    friend const Vector2D &operator*(Vector2D &v1, Vector2D &v2)
    {
        const Vector2D &r_v2d = Vector2D(v1.x * v2.x, v1.y * v2.y);
        return r_v2d;
    }

    friend const Vector2D &operator/(Vector2D &v1, Vector2D &v2)
    {
        const Vector2D &r_v2d = Vector2D(v1.x / v2.x, v1.y / v2.y);
        return r_v2d;
    }

    // += -= *= /= operators
    Vector2D &
    operator+=(const Vector2D &vec)
    {
        return this->add(vec);
    }

    Vector2D &operator-=(const Vector2D &vec)
    {
        return this->subtract(vec);
    }

    Vector2D &operator*=(const Vector2D &vec)
    {
        return this->multiply(vec);
    }

    Vector2D &operator/=(const Vector2D &vec)
    {
        return this->divide(vec);
    }

    Vector2D &operator*(const int &i)
    {
        this->x *= i;
        this->y *= i;

        return *this;
    }

    Vector2D &Zero()
    {
        this->x = 0;
        this->y = 0;

        return *this;
    }

    friend std::ostream &operator<<(std::ostream &stream, const Vector2D &vec)
    {
        stream << "(" << vec.x << "," << vec.y << ")";
        return stream;
    }
};