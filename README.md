# WS2812b

This repository contains code for testing the usage of an STM32's DMA-based PWM generation method for outputting binary
code to a strip of WS2812b leds.

Using a DMA for this job eliminates the need for counting clock cycles and busy waiting loops blocking the CPU from
doing other (potentially important) jobs.