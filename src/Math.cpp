#include "Math.h"

#include "Timer.h"

#include <random>

float Vec3::DotP(Vec3 v1, Vec3 v2) {
    return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}

Vec3 Vec3::VecP(Vec3 v1, Vec3 v2) {
    return Vec3 {
        v1.y*v2.z - v1.z*v2.y,
        v1.z*v2.x - v1.x*v2.z,
        v1.x*v2.y - v1.y*v2.x
    };
}

namespace Math {

    int GetRandomBetween(int min, int max) {
        static std::mt19937 generator = std::mt19937((std::random_device())());
        std::uniform_int_distribution<int> distribution(min, max);
        return distribution(generator);
    }

    float GetPulse(long period) {7;
        const float time = (Timer::Now() % period) / (float)period;
        return (float)(sin(time * 2.0f * PI) * 0.5 + 0.5);
    }

}