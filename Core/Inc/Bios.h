#pragma once

#include <cstdint>
#include <chrono>

#include "Gpio.hpp"

using namespace std::chrono_literals;
using Cycle = std::chrono::duration<int64_t, std::ratio<1, 72'000'000>>;

extern GPIO debugLed;

Cycle runtime();

inline void wait(Cycle timeout)
{
    const auto endTime = runtime() + timeout;
    while (runtime() < endTime);
}
