#pragma once

#include "../ISPI.h"
#include <hardware/spi.h>
#include <hardware/gpio.h>

namespace ispi
{
    class PicoHardwareSPI : public SPI
    {
        spi_inst_t* _hardware;
        int         _cs_pin;
        uint32_t    _speed;
        BitOrder    _order;
        Policy      _policy;
    public:
        PicoHardwareSPI(int spi_instance, uint32_t speed, int sck, int mosi, int miso, int cs);
        PicoHardwareSPI(PicoHardwareSPI& shared, int alternative_cs);
        virtual void start() override;
        virtual void stop() override;
        virtual void set_speed(uint32_t speed) override;
        virtual void set_settings(BitOrder order, Policy policy) override;
        virtual uint8_t transfer(uint8_t tx) override;
    };

}