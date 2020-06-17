# BME680
Program to read temperature, pressure, humidity and gas resistance from BME680 using Bosch's open source sensor API.

## Getting the source code
1. Clone this repository.
   ```console
   $ git clone https://github.com/chaitanyamehta/Bosch-BME680.git
   ```
2. Get inside Bosch-BME680 directory.
   ```console
   $ cd Bosch-BME680/
   ```
3. Update submodules.
   ```console
   $ git submodule update --init
   ``` 

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
<img src="/screenshots/bme680_test.PNG" alt="Terminal screenshot" width="500">

[Link](https://github.com/BoschSensortec/BME680_driver) to Bosch's Sensor API.
