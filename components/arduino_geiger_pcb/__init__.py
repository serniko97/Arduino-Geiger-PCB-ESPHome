import esphome.codegen as cg
from esphome.components import uart
import esphome.config_validation as cv
from esphome.const import CONF_ID
from esphome.types import ConfigType

CODEOWNERS = ["@serniko97"]
DOMAIN = "arduino_geiger_pcb"

DEPENDENCIES = ["uart"]

arduino_geiger_pcb_ns = cg.esphome_ns.namespace("arduino_geiger_pcb")
ArduinoGeigerPCBComponent = arduino_geiger_pcb_ns.class_(
    "ArduinoGeigerPCBComponent", uart.UARTDevice, cg.Component
)

CONF_ARDUINO_GEIGER_PCB_ID = "arduino_geiger_pcb_id"

CONFIG_SCHEMA = (
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(ArduinoGeigerPCBComponent),
        }
    )
    .extend(uart.UART_DEVICE_SCHEMA)
    .extend(cv.COMPONENT_SCHEMA)
)


async def to_code(config: ConfigType) -> None:
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await uart.register_uart_device(var, config)
