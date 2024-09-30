#include "m5module_2relay.h"
#include "esphome/core/log.h"

namespace esphome {
namespace m5module_2relay {

static const char *const TAG = "m5module_2_relay";

void M5Module2Relay::dump_config() {
  ESP_LOGCONFIG(TAG, "M5Module 2 Relays:");
  LOG_I2C_DEVICE(this);
}

/*! @brief Turn off all relays, restore the switches with restore mode. */
void M5Module2Relay::init_(bool mode) {
  this->write1_byte_((MODULE_2RELAY_REG + 0), 0); // Relay 0
  this->write1_byte_((MODULE_2RELAY_REG + 1), 0); //   ..  1
}

/*! @brief Read a certain length of data to the specified register address. */
uint8_t M5Module2Relay::read1_byte_(uint8_t register_address) {
  uint8_t data;
  if (!this->read_byte(register_address, &data)) {
    ESP_LOGW(TAG, "Read from relay failed!");
    this->status_set_warning();
    return uint8_t(0);
  }
  return data;
}

/*! @brief Control the on/off of the specified relay.
 *  @param channel Relay number (0~1).
    @param state OFF = 0, ON = 1 . */
void M5Module2Relay::relay_write(uint8_t channel, bool state) {
  uint8_t value = 0;
//  if (channel > 1) {
//    ESP_LOGW(TAG, "M5Module_2Relay - Channel Overflow!");
//    this->status_set_warning();
//    return;
//  }
  if (state) value = 1;
  this->write1_byte_((MODULE_2RELAY_REG + channel), value);
}

void M5Module2Relay::setup() {
  ESP_LOGCONFIG(TAG, "Setting up M5Module_2Relay...");
  uint8_t setupmode = 1;
  this->init_(setupmode);
}

/*! @brief Write a certain length of data to the specified register address. */
void M5Module2Relay::write1_byte_(uint8_t register_address, uint8_t data) {
  if (!this->write_byte(register_address, data)) {
    ESP_LOGW(TAG, "Write to M5Module_2Relay failed!");
    this->status_set_warning();
    return;
  }
}

}  // namespace m5module_2relay
}  // namespace esphome
