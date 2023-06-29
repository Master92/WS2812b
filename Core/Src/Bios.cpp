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

#include "Bios.h"

#include "stm32f1xx_hal.h"
#include "tim.h"

GPIO debugLed { DebugLed_GPIO_Port, DebugLed_Pin, true };

static volatile uint64_t _timerTicks {0};

Cycle runtime()
{
    return Cycle(_timerTicks * htim4.Init.Period + __HAL_TIM_GET_COUNTER(&htim4));
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* timerHandle)
{
    if (timerHandle == &htim4) {
        _timerTicks = _timerTicks + 1;
    }
}
