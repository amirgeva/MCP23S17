#include "pico.h"

namespace ispi
{

        PicoHardwareSPI::PicoHardwareSPI(int spi_instance, uint32_t speed, int sck, int mosi, int miso, int cs)
        : _cs_pin(cs)
        , _speed(speed)
        , _order(BitOrder::MSB)
        , _policy(mode_to_policy(Mode::MODE0))
        {
            if (spi_instance==0) _hardware=(spi_inst_t*)spi0_hw;
            else
            if (spi_instance==1) _hardware=(spi_inst_t*)spi1_hw;
            else
            return;
            spi_init(_hardware, speed);
            gpio_set_function(miso, GPIO_FUNC_SPI);
            gpio_set_function(_cs_pin,   GPIO_FUNC_SIO);
            gpio_set_function(sck,  GPIO_FUNC_SPI);
            gpio_set_function(mosi, GPIO_FUNC_SPI);
            
            gpio_set_dir(_cs_pin, GPIO_OUT);
            gpio_put(_cs_pin, 1);
        }
    
        void PicoHardwareSPI::start()
        {
            gpio_put(_cs_pin, 0);
        }

        void PicoHardwareSPI::stop()
        {
            gpio_put(_cs_pin, 1);
        }

        void PicoHardwareSPI::set_speed(uint32_t speed)
        {
            if (_speed!=speed)
            {
                _speed=speed;
                spi_set_baudrate(_hardware,speed);
            }
        }

        void PicoHardwareSPI::set_settings(BitOrder order, Policy policy)
        {
            if (order != _order || policy != _policy)
            {
                _order=order;
                _policy=policy;
                spi_cpol_t pico_cpol;
                spi_cpha_t pico_cpha;
                spi_order_t pico_order = (order == BitOrder::MSB ? SPI_MSB_FIRST : SPI_LSB_FIRST);
                switch (policy)
                {
                    case Policy::CPOL0_FALLING: pico_cpol=SPI_CPOL_0; pico_cpha=SPI_CPHA_0; break;
                    case Policy::CPOL0_RISING:  pico_cpol=SPI_CPOL_0; pico_cpha=SPI_CPHA_1; break;
                    case Policy::CPOL1_RISING:  pico_cpol=SPI_CPOL_1; pico_cpha=SPI_CPHA_0; break;
                    case Policy::CPOL1_FALLING: pico_cpol=SPI_CPOL_1; pico_cpha=SPI_CPHA_1; break;
                }
                spi_set_format(_hardware,8,pico_cpol,pico_cpha,pico_order);
            }
        }

        uint8_t PicoHardwareSPI::transfer(uint8_t tx)
        {
            uint8_t rx;
            spi_write_read_blocking(_hardware,&tx,&rx,1);
            return rx;
        }

};