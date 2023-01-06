// Comments found in "vector.cpp"
#pragma once
#include <iostream>

struct vector
{
    float x;
    float y;

    // Constructors
    vector()
    {
        x = 0.0f;
        y = 0.0f;
    }

    vector(float x, float y)
    {
        this->x = x;
        this->y = y;
    }

    // Basic operations
    vector &add(const vector &vec)
    {
        this->x += vec.x;
        this->y += vec.y;

        return *this;
    }

    vector &subtract(const vector &vec)
    {
        this->x -= vec.x;
        this->y -= vec.y;

        return *this;
    }

    vector &multiply(const vector &vec)
    {
        this->x *= vec.x;
        this->y *= vec.y;

        return *this;
    }

    vector &divide(const vector &vec)
    {
        this->x /= vec.x;
        this->y /= vec.y;

        return *this;
    }

    // + - * / operators
    friend const vector &operator+(vector &v1, vector &v2)
    {
        const vector &r_v2d = vector(v1.x + v2.x, v1.y + v2.y);
        return r_v2d;
    }

    friend const vector &operator-(vector &v1, vector &v2)
    {
        const vector &r_v2d = vector(v1.x - v2.x, v1.y - v2.y);
        return r_v2d;
    }

    friend const vector &operator*(vector &v1, vector &v2)
    {
        const vector &r_v2d = vector(v1.x * v2.x, v1.y * v2.y);
        return r_v2d;
    }

    friend const vector &operator/(vector &v1, vector &v2)
    {
        const vector &r_v2d = vector(v1.x / v2.x, v1.y / v2.y);
        return r_v2d;
    }

    // += -= *= /= operators
    vector &
    operator+=(const vector &vec)
    {
        return this->add(vec);
    }

    vector &operator-=(const vector &vec)
    {
        return this->subtract(vec);
    }

    vector &operator*=(const vector &vec)
    {
        return this->multiply(vec);
    }

    vector &operator/=(const vector &vec)
    {
        return this->divide(vec);
    }

    vector &operator*(const int &i)
    {
        this->x *= i;
        this->y *= i;

        return *this;
    }

    vector &Zero()
    {
        this->x = 0;
        this->y = 0;

        return *this;
    }

    friend std::ostream &operator<<(std::ostream &stream, const vector &vec)
    {
        stream << "(" << vec.x << "," << vec.y << ")";
        return stream;
    }
};