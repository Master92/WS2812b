/*
 * WS2812b - An STM32 DMA-based PWM generator
 * Copyright (C) 2023  Nils Hofmann
 *
 * This file is part of WS2812b.
 *
 * WS2812b is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * WS2812b is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with WS2812b.  If not, see <http://www.gnu.org/licenses/>.
 */

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
