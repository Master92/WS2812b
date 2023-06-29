#pragma once

#include <vector>

#include "stm32f1xx_hal.h"

#include "Array.h"
#include "WS2812.h"
#include "Bios.h"

extern TIM_HandleTypeDef htim2;

class LedStrip {
public:
    constexpr LedStrip();

    constexpr LedStrip(size_t count, uint16_t pwmCycles = 100, TIM_HandleTypeDef* timer = &htim2, uint32_t timerChannel = TIM_CHANNEL_1);

    virtual ~LedStrip() = default;

    constexpr auto pixels() -> Array<WS2812>& { return m_pixels; }

    constexpr auto pixels() const -> const Array<WS2812>& { return m_pixels; }

    auto fill(const WS2812::Color& color) -> void;
    auto setPixel(size_t index, const WS2812::Color& color) -> void;

    constexpr auto bufferSize() { return WS2812::output_bits * m_pixels.size(); }

    void createBuffer();
    void updateBuffer();

    void activate();
    void reset();

    [[nodiscard]] inline auto inReset() const { return runtime() - m_stopTime < 50us; }

private:
    Array<WS2812> m_pixels;
    TIM_HandleTypeDef* m_timer { nullptr };
    uint32_t m_timerChannel { 0 };
    bool bufferValid { false };
    uint16_t* m_buffer { nullptr };
    Cycle m_stopTime {0 };
};

constexpr LedStrip::LedStrip(size_t count, uint16_t pwmCycles, TIM_HandleTypeDef* timer, uint32_t timerChannel)
        : m_pixels(count)
        , m_timer(timer)
        , m_timerChannel(timerChannel)
{
    m_pixels.fill(count, pwmCycles);
}

constexpr LedStrip::LedStrip()
        : m_pixels(0)
{

}

