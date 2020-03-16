#include<iostream>
#include<chrono>
#include<thread>
#include"i2c.hpp"
#include"BME680_driver/bme680.h"

using namespace std;

I2C *i2c;

int8_t read(uint8_t dev_id, uint8_t reg_addr, uint8_t *data, uint16_t len)
{
    return (int8_t)i2c->Read(dev_id, reg_addr, data, len);
}

int8_t write(uint8_t dev_id, uint8_t reg_addr, uint8_t *data, uint16_t len)
{
    return (int8_t)i2c->Write(dev_id, reg_addr, data, len);
}

void sleep(uint32_t delay_ms)
{
  this_thread::sleep_for(chrono::milliseconds(delay_ms));
}

int main()
{
    int res = 0;

    i2c = new I2C();
    i2c->Open();
    
    bme680_dev dev;
    dev.dev_id = BME680_I2C_ADDR_SECONDARY;
    dev.read = read;
    dev.write = write;
    dev.delay_ms = sleep;
    dev.intf = BME680_I2C_INTF;

    res = bme680_init(&dev);
    if(res != BME680_OK)
    {
        cout << "Error Initializing Sensor\n";
        return res;
    }

    // Configure oversampling settings 
    // As mentioned in ref manual quick start (3.2.1)
    dev.tph_sett.os_hum = BME680_OS_1X;
    dev.tph_sett.os_temp = BME680_OS_2X;
    dev.tph_sett.os_pres = BME680_OS_16X;

    dev.gas_sett.heatr_dur = 100;   // Milliseconds
    dev.gas_sett.heatr_temp = 300;  // Degree C
    // Number of conversions
    dev.gas_sett.nb_conv = BME680_NBCONV_MIN;       
    // Enable gas measurements
    dev.gas_sett.run_gas = BME680_ENABLE_GAS_MEAS;       
    
    // Set mode to forced mode
    dev.power_mode = BME680_FORCED_MODE;

    int desired_settings = BME680_OST_SEL | BME680_OSP_SEL | BME680_OSH_SEL | BME680_GAS_SENSOR_SEL;
    res = bme680_set_sensor_settings(desired_settings, &dev);
    if(res != BME680_OK)
    {
        cout << "Error occurred in Set Sensor Settings\n";
        return res;
    }

    // Get profile duration of the sensor
    uint16_t duration;
    bme680_get_profile_dur(&duration,&dev);

    int required_readings = 1;
    int valid_readings = 0;
    while(valid_readings < required_readings)
    {
        // Trigger Measurement
        bme680_set_sensor_mode(&dev);
        if(res != BME680_OK)
        {
            cout << "Error occurred in Set Sensor Mode\n";
            return res;
        }

        // Wait for profile duration
        sleep(duration);

        bme680_field_data data;
        res = bme680_get_sensor_data(&data, &dev);
        if(res != BME680_OK)
        {
            cout << "Error getting sensor data\n";
            return res;
        }

        // Display reading only when gasreading is valid and heater is stable
        if((data.status&(BME680_GASM_VALID_MSK|BME680_HEAT_STAB_MSK))==(BME680_GASM_VALID_MSK|BME680_HEAT_STAB_MSK))
        {        
            cout << "Temperatue\t\t" << data.temperature/100.0 << " degC\n"; 
            cout << "Pressure\t\t" << data.pressure/100.0 << " hPa\n"; 
            cout << "Humidity\t\t" << data.humidity/1000.0 << " rH\n"; 
            cout << "Gas Resistance\t\t" << data.gas_resistance << " Ohms\n";
            valid_readings++;
        }
    }

    delete i2c;
    return 0;
}