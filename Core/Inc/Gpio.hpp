//
// Created by n.hofmann on 05.12.2022.
//

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
