#pragma once

#include "esphome/core/component.h"
#include "esphome/components/i2c/i2c.h"

namespace esphome {
namespace m5module_2relay {

static constexpr uint8_t MODULE_2RELAY_REG = 0X00;

class M5Module2Relay : public Component, public i2c::I2CDevice {
 public:

  void relay_write(uint8_t channel, bool state);

 protected:
  void write1_byte_(uint8_t register_address, uint8_t data);
  uint8_t read1_byte_(uint8_t register_address);

  void dump_config() override;

  void init_(bool mode);

  void setup() override;
};

}  // namespace m5module_2relay
}  // namespace esphome
