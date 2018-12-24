#include "i2c.h"

// Address and commands for i2c device. 
// Replace values with ones from the device datasheet of your choice
const uint8_t ADDRESS_READ_BIT = 0x00;
const uint8_t ADDRESS_WRITE_BIT = 0x01;
const uint8_t WRITE_COMMAND = 0x02;
const uint8_t READ_COMMAND = 0x03;

// Create an I2C device
i2c i2cDevice(HOLD_MASTER); 

void setup() {
  // Initialize the I2C device
  i2cDevice.init();
}

// Read from Device
void loop() {

  // An example of initializing data for a i2c device 
  // that outputs a 16 bit integer with a crc byte
  uint8_t msb = 0;
  uint8_t lsb = 0;
  uint8_t crc = 0;
  uint16_t value = 0;
  
  // i2c Start Command
  i2cDevice.start();

  // i2c Write Command
  i2cDevice.write(ADDRESS_WRITE_BIT);

  i2cDevice.write(WRITE_COMMAND);

  // Repeated Start
  i2cDevice.start();

  // Set the I2C device to read
  i2cDevice.write(ADDRESS_READ_BIT);

  // Read the MSB with an ACK bit
  msb = i2cDevice.readAck();

  // Read the LSB with an ACK bit
  lsb = i2cDevice.readAck();

  // Read the CRC byte with a NACK bit
  crc = i2cDevice.readNack();

  // i2c Stop Command
  i2cDevice.stop();

  // Combine the msb and lsb for the final value.
  // Depending on your device datasheet, an equation may be provided to process the data.
  value = ((uint16_t)msb << 8)|(lsb);

  delay(1000);
}
