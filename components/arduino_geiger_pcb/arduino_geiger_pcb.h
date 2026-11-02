#pragma once

#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"
#ifdef USE_SENSOR
#include "esphome/components/sensor/sensor.h"
#endif

namespace esphome::arduino_geiger_pcb {

// The Geiger PCB streams the current CPM value as a plain decimal number followed by a
// line break. We accumulate the digits of one line and publish them when the line ends.
static constexpr size_t MAX_BUFFER_LENGTH = 16;

class ArduinoGeigerPCBComponent : public uart::UARTDevice, public Component {
#ifdef USE_SENSOR
  SUB_SENSOR(cpm)
#endif

 public:
  void setup() override;
  void dump_config() override;
  void loop() override;

 private:
  char buffer_[MAX_BUFFER_LENGTH] = {};
  size_t index_{0};
  bool wait_new_line_{false};
};

}  // namespace esphome::arduino_geiger_pcb
