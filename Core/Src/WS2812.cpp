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

#include "WS2812.h"

#include <initializer_list>


auto WS2812::exportToMemory(uint16_t* memory) const -> uint16_t*
{
    const auto highPeriod = m_pwmCycles * 2 / 3;
    const auto lowPeriod = m_pwmCycles * 1 / 3;

    uint16_t* output = memory;
    for (const auto& channel: {color.g, color.r, color.b}) {
        for (auto i = sizeof(channel) * CHAR_BIT; i > 0; i--) {
            *output++ = channel & (1 << (i - 1)) ? highPeriod : lowPeriod;
        }
    }

    return memory;
}

