#pragma once

#include <chrono>

class Timer final {
    public:
        inline Timer() {
            Reset();
        }

        inline void Reset() {
            lastTick = Now();
        }

        inline long GetElapsedMillis() {
            return Now() - lastTick;
        }

        inline bool HasTimeElapsed(long millis) {
            return GetElapsedMillis() >= millis;
        }

        inline static long Now() {
            return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        }

    private:
        long lastTick;
};