# ESPHome component for Arduino-Geiger-PCB
This is a custom component for ESPHome to integrate the Geiger counter [Arduino-Geiger-PCB](https://arduino-geiger-pcb.blogspot.com) made by [@impexeris](https://github.com/impexeris).

It simply uses the serial interface to read the CPM value, convert it to an integrer and expose it as a sesnor that can then be integrated into Home Assistant.

> [!WARNING]
> This project currently works with ESPHome 2025.1.x or an earlier verison.
