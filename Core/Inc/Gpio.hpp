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

#include "stm32f103xb.h"
#include "stm32f1xx_hal.h"

struct GPIO {
    GPIO_TypeDef* bank;
    uint16_t pin;
    bool inverted {false};

    inline void set(GPIO_PinState state)
    {
        if (state == GPIO_PIN_SET) {
            set();
        } else {
            unset();
        }
    }

    inline void setHigh() { set(); }
    inline void setLow() { unset(); }

    inline void set() { HAL_GPIO_WritePin(bank, pin, setState()); }
    inline void unset() { HAL_GPIO_WritePin(bank, pin, unsetState()); }
    inline void toggle()
    {
        if (get() == setState()) {
            unset();
        } else {
            set();
        }
    }

    [[nodiscard]] GPIO_PinState get() const { return HAL_GPIO_ReadPin(bank, pin); }

private:
    constexpr GPIO_PinState setState() const { return inverted ? GPIO_PIN_RESET : GPIO_PIN_SET; }
    constexpr GPIO_PinState unsetState() const { return inverted ? GPIO_PIN_SET : GPIO_PIN_RESET; }
};
