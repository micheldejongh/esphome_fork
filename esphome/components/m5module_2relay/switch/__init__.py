import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import i2c, switch
from esphome.const import CONF_CHANNEL

from .. import m5module_2relay_ns, M5Module_2Relay, CONF_M5MODULE_2RELAY_ID

DEPENDENCIES = ["m5module_2relay"]

M5ModuleSwitch = m5module_2relay_ns.class_(
    "M5Module2RelaySwitch", cg.Component, i2c.I2CDevice, switch.Switch
)

CONF_INTERLOCK_WAIT_TIME = "interlock_wait_time"

CONFIG_SCHEMA = (
    switch.switch_schema(M5ModuleSwitch)
    .extend(
        {
            cv.GenerateID(): cv.declare_id(M5ModuleSwitch),
            cv.GenerateID(CONF_M5MODULE_2RELAY_ID): cv.use_id(M5Module_2Relay),
            cv.Required(CONF_CHANNEL): cv.int_range(min=1, max=2),
        }
    )
    .extend(cv.COMPONENT_SCHEMA)
)


async def to_code(config):
    var = await switch.new_switch(config)
    await cg.register_component(var, config)
    await cg.register_parented(var, config[CONF_M5MODULE_2RELAY_ID])

    cg.add(var.set_channel(config[CONF_CHANNEL]))
