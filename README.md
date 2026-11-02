# ESPHome component for Arduino-Geiger-PCB

This is an [external component](https://esphome.io/components/external_components) for ESPHome to integrate the Geiger counter [Arduino-Geiger-PCB](https://arduino-geiger-pcb.blogspot.com) made by [@impexeris](https://github.com/impexeris).

It simply uses the serial interface to read the CPM value, convert it to an integer and expose it as a sensor that can then be integrated into Home Assistant.

> [!NOTE]
> This project requires **ESPHome 2025.2.0 or later**, which replaced the old *custom components* with *external components*.

## Installation

Add the component from GitHub to your ESPHome configuration:

```yaml
external_components:
  - source: github://serniko97/Arduino-Geiger-PCB-ESPHome
    components: [arduino_geiger_pcb]
```

Alternatively, copy the [`components/`](components) folder next to your `.yaml` file and use a local source instead:

```yaml
external_components:
  - source: .   # or the path to the copied `components` folder
    components: [arduino_geiger_pcb]
```

## Configuration

Wire the Geiger PCB's TX pin to an ESP32 RX pin (GPIO16 in this example) and add the following to your configuration. The component reads the CPM value at 9600 baud, so make sure the UART bus matches:

```yaml
uart:
  id: uart_bus
  rx_pin: GPIO16
  baud_rate: 9600

arduino_geiger_pcb:
  id: geiger_bus
  uart_id: uart_bus

sensor:
  - platform: arduino_geiger_pcb
    cpm:
      name: "Arduino Geiger PCB"
      unit_of_measurement: CPM
      state_class: measurement
      icon: mdi:radioactive
```

A complete example, including Wi-Fi and API settings, is available in [`arduino-geiger-pcb.yaml`](arduino-geiger-pcb.yaml).
