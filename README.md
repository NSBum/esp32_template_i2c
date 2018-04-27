## Template for ESP32 I2C-based projects

This is just a simple component-based template for ESP32 projects that use the I2C driver. Clone this repository to start a new project.

### To customize

- Change the name of your project in the Makefile
- Modify the outer `component.mk` with the name of any component directories you are using.
- Modify the `I2C_SDA` and `I2C_SCL` in main.c to correspond to your hardware connections.