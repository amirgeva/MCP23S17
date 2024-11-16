#pragma once

#include <cstdint>

namespace ispi
{

    enum class Mode
    {
        MODE0, MODE1, MODE2, MODE3
    };

    enum class Policy
    {
        CPOL0_FALLING, CPOL0_RISING, CPOL1_RISING, CPOL1_FALLING
    };

    inline Policy mode_to_policy(const Mode& mode)
    {
        switch (mode)
        {
            case Mode::MODE0: return Policy::CPOL0_FALLING;
            case Mode::MODE1: return Policy::CPOL0_RISING;
            case Mode::MODE2: return Policy::CPOL1_RISING;
            case Mode::MODE3: return Policy::CPOL1_FALLING;
        }
        return Policy::CPOL0_FALLING;
    }

    enum class BitOrder
    {
        MSB, LSB
    };


    class SPI
    {
    public:
        virtual ~SPI() = default;
        //SPIClass(int sck, int mosi, int miso, int cs);
        //void set_settings(const SPISettings& settings);
        virtual void set_speed(uint32_t speed) = 0;
        virtual void set_settings(BitOrder order, Policy policy) = 0;
        virtual void start() = 0;
        virtual uint8_t transfer(uint8_t tx) = 0;
        virtual void stop() = 0;
    };


}
