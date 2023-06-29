#pragma once

#include <cstdint>
#include <cstddef>
#include <climits>

struct WS2812 {
    struct Color {
        uint8_t r;
        uint8_t g;
        uint8_t b;
    };

    constexpr WS2812(uint16_t pwmCycles = 100);

    Color color;

    auto exportToMemory(uint16_t* memory) const -> uint16_t*;

    constexpr static auto output_bits = sizeof(Color) * CHAR_BIT;

private:
    uint16_t m_pwmCycles;
};

constexpr WS2812::WS2812(uint16_t pwmCycles)
        : color({0, 0, 0}), m_pwmCycles(pwmCycles)
{

}
