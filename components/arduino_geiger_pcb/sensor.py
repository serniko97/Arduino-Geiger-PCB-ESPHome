import esphome.codegen as cg
from esphome.components import sensor
import esphome.config_validation as cv
from esphome.const import STATE_CLASS_MEASUREMENT
from esphome.types import ConfigType

from . import ArduinoGeigerPCBComponent, CONF_ARDUINO_GEIGER_PCB_ID

DEPENDENCIES = ["arduino_geiger_pcb"]

CONF_CPM = "cpm"

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(CONF_ARDUINO_GEIGER_PCB_ID): cv.use_id(ArduinoGeigerPCBComponent),
        cv.Required(CONF_CPM): sensor.sensor_schema(
            unit_of_measurement="CPM",
            state_class=STATE_CLASS_MEASUREMENT,
            icon="mdi:radioactive",
        ),
    }
)


async def to_code(config: ConfigType) -> None:
    hub = await cg.get_variable(config[CONF_ARDUINO_GEIGER_PCB_ID])
    sensors = sensor.sub_sensors(config)
    await sensors(CONF_CPM, hub.set_cpm_sensor)
