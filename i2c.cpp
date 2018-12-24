#include "i2c.h"

/*****************************************************************
Used to create an I2C object and also set the I2C mode
******************************************************************/
i2c::i2c(uint8_t mode)
{
  _mode = mode;
}

/*****************************************************************
Set the TWI slave-clock frequency and prescaler
******************************************************************/
void i2c::init()
{
  /* The SCL Frequency is set by:
   SCL Freq = F_CPU/(16+(2*TWBR*(4^TWPS))) */
  
  TWSR = 0x00; /* Don't need additional prescalers so set to 0x00 */
  TWBR = TWI_BIT_RATE; /* Sets SCL Frequency */
  
  /* Enable TWI(I2C) */
  TWCR = (1<<TWEN);
}

/*****************************************************************
AVR MCU (TWI Master) sends start condition and expects a status 
code of 0x08 to be returned.
******************************************************************/
void i2c::start()
{
  volatile uint16_t timeOut = TWI_TIMEOUT; //Track if wait is too long for transmission
  
  /* Generates START signal */
  TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
  
  /* Wait until START condition is transmitted */
  while(!(TWCR & (1<<TWINT)) && timeOut > 0)
    timeOut--;
}

/*****************************************************************
AVR MCU (TWI Master) sends stop condition
******************************************************************/
void i2c::stop()
{
  volatile uint16_t timeOut = TWI_TIMEOUT; //Track if wait is too long for transmission
  
  // Generates STOP signal
  TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
  
  // Wait for STOP signal to transmit
  while(!(TWCR & (1<<TWSTO)) && timeOut > 0)
    timeOut--;
}

/*****************************************************************
Write a single byte of data into the two-wire data register (TWDR)
******************************************************************/
void i2c::write(int u8address)
{
  volatile uint16_t timeOut = TWI_TIMEOUT; //Track if wait is too long for transmission
  
  // Load I2C slave address into TWDR
  TWDR = u8address; 
  
  // Initiate send
  TWCR = (1<<TWINT)|(1<<TWEN);
  
  // Wait for command to go through
  while(!(TWCR & (1<<TWINT)) && timeOut > 0)
    timeOut--;
}

/*****************************************************************
Checks to see if acknowledge bit is sent by I2C slave device.
******************************************************************/
uint8_t i2c::readAck()
{
  volatile uint16_t timeOut = TWI_TIMEOUT; //Track if wait is too long for transmission
  
  TWCR = (1<<TWINT)|(1<<TWEA)|(1<<TWEN);
  
  while(!(TWCR & (1<<TWINT)) && timeOut > 0)
    timeOut--;
  
  if(timeOut <= 0)
    return 0;
  else
    return TWDR;
}

/*****************************************************************
Checks to see if not-acknowledge bit is sent by I2C slave device.
******************************************************************/
uint8_t i2c::readNack()
{
  volatile uint16_t timeOut = TWI_TIMEOUT; //Track if wait is too long for transmission
  
  TWCR = (1<<TWINT)|(1<<TWEN);
  
  // Wait for transmission to complete
  while(!(TWCR & (1<<TWINT)) && timeOut > 0)
    timeOut--;
  
  if(timeOut <= 0)
    return 0;
  else
    return TWDR;
}
