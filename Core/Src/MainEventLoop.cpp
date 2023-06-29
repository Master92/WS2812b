#include "MainEventLoop.h"

#include "stm32f1xx_hal.h"
#include "tim.h"


void initSystem()
{
    HAL_TIM_Base_Start_IT(&htim4);
}

void loop()
{

}
