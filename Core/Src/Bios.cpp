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
