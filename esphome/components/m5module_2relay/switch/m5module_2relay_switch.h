#pragma once

#include "esphome/core/component.h"
#include "esphome/components/switch/switch.h"

#include "esphome/components/m5module_2relay/m5module_2relay.h"

namespace esphome {
namespace m5module_2relay {

class M5Module2RelaySwitch : public Component, public switch_::Switch, public Parented<M5Module2Relay> {
 public:
  float get_setup_priority() const override;

  void setup() override;
  void dump_config() override;
  void write_state(bool state) override;

  void set_channel(uint8_t channel) { this->channel_ = channel; }

  void set_interlock(const std::vector<Switch *> &interlock);
  void set_interlock_wait_time(uint32_t interlock_wait_time) { interlock_wait_time_ = interlock_wait_time; }

 protected:
  uint8_t channel_;
  std::vector<Switch *> interlock_;
  uint32_t interlock_wait_time_{0};
};

}  // namespace m5module_2relay
}  // namespace esphome
