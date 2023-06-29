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
#include <cstddef>
#include <climits>

struct WS2812 {
    struct Color {
        uint8_t r;
        uint8_t g;
        uint8_t b;
    };

    constexpr WS2812(uint16_t pwmCycles = 100);

    Color color;

    auto exportToMemory(uint16_t* memory) const -> uint16_t*;

    constexpr static auto output_bits = sizeof(Color) * CHAR_BIT;

private:
    uint16_t m_pwmCycles;
};

constexpr WS2812::WS2812(uint16_t pwmCycles)
        : color({0, 0, 0}), m_pwmCycles(pwmCycles)
{

}
