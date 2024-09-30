import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import i2c
from esphome.const import CONF_ID

CODEOWNERS = ["@micheldejongh"]
DEPENDENCIES = ["i2c"]

MULTI_CONF = True

CONF_M5MODULE_2RELAY_ID = "m5module_2relay_id"

m5module_2relay_ns = cg.esphome_ns.namespace("m5module_2relay")
M5SModule_2Relay = m5module_2relay_ns.class_("M5Module2Relay", cg.Component, i2c.I2CDevice)

CONFIG_SCHEMA = (
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(M5Module_2Relay),
        }
    )
    .extend(cv.COMPONENT_SCHEMA)
    .extend(i2c.i2c_device_schema(0x25))
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await i2c.register_i2c_device(var, config)
