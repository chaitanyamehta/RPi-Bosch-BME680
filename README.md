# BME680
Program to read temperature, pressure, humidity and gas resistance from BME680 using Bosch's open source sensor API.

## Getting the source code
1. Clone this repository.
   ```console
   $ git clone https://github.com/chaitanyamehta/RPi-Bosch-BME680.git
   ```
2. Get inside RPi-Bosch-BME680 directory.
   ```console
   $ cd RPi-Bosch-BME680/
   ```
3. Update submodules.
   ```console
   $ git submodule update --init
   ``` 

## Interfacing with Raspberry Pi
<img src="/images/connections.png" alt="Schematic" width="500">

## Running the program
1. Compile using make.
   ```console
   $ make
   ```
2. Run program.
   ```console
   $ ./bme680
   ```

## Output
<img src="/images/console_output.png" alt="Console Output" width="500">

[Link](https://github.com/BoschSensortec/BME680_driver) to Bosch's Sensor API.
