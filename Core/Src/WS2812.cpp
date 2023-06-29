#include "WS2812.h"

#include <initializer_list>


auto WS2812::exportToMemory(uint16_t* memory) const -> uint16_t*
{
    const auto highPeriod = m_pwmCycles * 2 / 3;
    const auto lowPeriod = m_pwmCycles * 1 / 3;

    uint16_t* output = memory;
    for (const auto& channel: {color.g, color.r, color.b}) {
        for (auto i = sizeof(channel) * CHAR_BIT; i > 0; i--) {
            *output++ = channel & (1 << (i - 1)) ? highPeriod : lowPeriod;
        }
    }

    return memory;
}

