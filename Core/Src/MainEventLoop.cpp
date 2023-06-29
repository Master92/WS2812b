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

#include "MainEventLoop.h"

#include "stm32f1xx_hal.h"
#include "tim.h"

#include "Bios.h"
#include "LedStrip.h"

static LedStrip strip(2, 90, &htim2, TIM_CHANNEL_1);

void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{
    if (htim == &htim2) {
        strip.reset();
    }
}

void initSystem()
{
    HAL_TIM_Base_Start_IT(&htim4);
    strip.fill({127, 0, 0 });
}

void loop()
{
    if (HAL_TIM_PWM_GetState(&htim2) == HAL_TIM_STATE_READY and not strip.inReset()) {
        if (strip.inReset()) {
            debugLed.set();
        } else {
            debugLed.unset();
            strip.activate();
        }
    }
}
