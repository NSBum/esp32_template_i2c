// FreeRTOS includes
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

// I2C driver
#include "driver/i2c.h"

// Error library
#include "esp_err.h"

#include "nvs_flash.h"
#include "esp_log.h"
#include "esp_system.h"
#include <stdio.h>

//  setup I2C pins
#define I2C_SDA	    21	//	GPIO_NUM_21
#define I2C_SCL     22	//	GPIO_NUM_22

//  setup I2C port number
#define I2C_PORT    I2C_NUM_0

void query_sensor_task(void *pvParameter) {
    while(1) {
        float temp = si7021_read_temperature();
        float hum = si7021_read_humidity();

        printf("%0.2f degrees C, %0.2f%% RH\n", temp, hum);
        vTaskDelay(5000 / portTICK_RATE_MS);
    }
}

//  initialize the I2C driver
//  if this is done in the device initialization
//  this can be deleted.
void init_i2c(void) {
    esp_err_t ret;
	_port = port;

	// setup i2c controller
	i2c_config_t conf;
	conf.mode = I2C_MODE_MASTER;
	conf.sda_io_num = sda_pin;
	conf.scl_io_num = scl_pin;
	conf.sda_pullup_en = sda_internal_pullup;
	conf.scl_pullup_en = scl_internal_pullup;
	conf.master.clk_speed = 100000;
    ESP_ERROR_CHECK( i2c_param_config(port, &conf) );
}

//	application entry point
int app_main(void) {
	//Initialize NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES) {
      ESP_ERROR_CHECK(nvs_flash_erase());
      ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    init_i2c();
}
