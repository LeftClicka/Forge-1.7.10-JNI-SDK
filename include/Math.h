#pragma once

#include <cmath>

/**
 * Vec3 struct consisting of three double values.
 */
struct Vec3 {
    double x, y, z;
    /** 
     * Scales this vector by a factor.
     */
    inline void Scale(double factor) {
        x *= factor;
        y *= factor;
        z *= factor;
    }
    /**
     * Computes the squared length of this vector.
     */
    inline double MagnitudeSq() {
        return x*x + y*y + z*z;
    }
    /**
     * Computes the length of this vector.
     */
    inline double Magnitude() {
        return sqrt(MagnitudeSq());
    }

    /**
     * Computes the dot product two vectors.
     */
    static float DotP(Vec3 v1, Vec3 v2);

    /**
     * Computes the vector product of two vectors.
     */
    static Vec3 VecP(Vec3 v1, Vec3 v2);

};

/**
 * Alias for Vec3.
 */
using Position = Vec3;

/**
 * Vec2 struct consisting of two float values.
 */
struct Vec2 {
    float a, b;
    /**
     * Scales this vector by a factor.
     */
    inline void Scale(float factor) {
        a *= factor;
        b *= factor;
    }
    /**
     * Computes the squared length of this vector.
     */
    inline float MagnitudeSq() {
        return a*a + b*b;
    }
    /**
     * Computes the length of this vector.
     */
    inline float Magnitude() {
        return sqrt(MagnitudeSq());
    }
};

/**
 * Alias for Vec2.
 */
using Angles = Vec2;

/**
 * BoundingBox struct defined as two diagonally opposing points.
 * 
 * Unused thus far.
 */
struct BoundingBox {
    Vec3 p1, p2;
};

namespace Math {

    /**
     * 13 digit approximation of Pi
     */
    constexpr double PI = 3.141592653589;

    /**
     * Returns a random integer between min and max (inclusive);
     */
    int GetRandomBetween(int min, int max);

    /**
     * Returns a sine-based pulse. Pulse period is passed as parameter (milliseconds).
     */
    float GetPulse(long periodMilliseconds);

}