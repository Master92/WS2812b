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
    strip.fill({127, 0, 0 });
    HAL_TIM_Base_Start_IT(&htim4);
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
