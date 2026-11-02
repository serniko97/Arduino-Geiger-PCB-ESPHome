#include "arduino_geiger_pcb.h"

#include <cstdlib>

#include "esphome/core/log.h"

namespace esphome::arduino_geiger_pcb {

ESPHOME_LOG_TAG(TAG, "arduino_geiger_pcb");

void ArduinoGeigerPCBComponent::setup() {
  ESP_LOGCONFIG(TAG, "Setting up Arduino Geiger PCB...");
}

void ArduinoGeigerPCBComponent::dump_config() {
  ESP_LOGCONFIG(TAG, "Arduino Geiger PCB:");
#ifdef USE_SENSOR
  LOG_SENSOR("  ", "CPM", this->cpm_sensor_);
#endif
}

void ArduinoGeigerPCBComponent::loop() {
  while (this->available()) {
    uint8_t byte;
    if (!this->read_byte(&byte))
      break;
    const char c = static_cast<char>(byte);

    // Accumulate the digits of a CPM reading.
    if ((c >= '0') && (c <= '9') && (this->index_ < MAX_BUFFER_LENGTH) && !this->wait_new_line_) {
      buffer_[this->index_] = c;
      this->index_++;
    } else if ((this->index_ > 0) && ((c == '\n') || (c == '\r')) && !this->wait_new_line_) {
      // End of a valid reading: publish it and reset the buffer.
#ifdef USE_SENSOR
      if (this->cpm_sensor_ != nullptr) {
        if (this->index_ < MAX_BUFFER_LENGTH)
          buffer_[this->index_] = '\0';
        this->cpm_sensor_->publish_state(static_cast<float>(std::atoi(buffer_)));
      }
#endif
      for (size_t j = 0; j < this->index_; j++) {
        buffer_[j] = '\0';
      }
      this->index_ = 0;
    } else {
      // A non-digit character: either a line break that ends the wait, or corrupted data.
      if ((c == '\n') || (c == '\r'))
        this->wait_new_line_ = false;
      else
        this->wait_new_line_ = true;  // discard the rest of the line until a new one starts

      for (size_t j = 0; j < this->index_; j++) {
        buffer_[j] = '\0';
      }
      this->index_ = 0;
    }
  }
}

}  // namespace esphome::arduino_geiger_pcb
