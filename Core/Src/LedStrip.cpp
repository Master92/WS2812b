/**
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

#include "LedStrip.h"

auto LedStrip::fill(const WS2812::Color& color) -> void
{
    for (auto& pixel: pixels()) {
        pixel.color = color;
    }

    updateBuffer();
}

auto LedStrip::setPixel(size_t index, const WS2812::Color& color) -> void
{
    m_pixels[index].color = color;

    updateBuffer();
}

void LedStrip::createBuffer()
{
    free(m_buffer);
    m_buffer = reinterpret_cast<uint16_t*>(std::malloc(m_pixels.size() * WS2812::output_bits * sizeof(*m_buffer)));
}

void LedStrip::updateBuffer()
{
    if (m_buffer == nullptr) {
        createBuffer();
    }

    size_t i = 0;
    for (const auto& pixel : pixels()) {
        pixel.exportToMemory(&m_buffer[i++ * WS2812::output_bits]);
    }
}

void LedStrip::activate()
{
    HAL_TIM_PWM_Start_DMA(m_timer, m_timerChannel, reinterpret_cast<uint32_t*>(m_buffer), bufferSize());
}

void LedStrip::reset()
{
    HAL_TIM_PWM_Stop_DMA(m_timer, m_timerChannel);
    m_stopTime = runtime();
}

