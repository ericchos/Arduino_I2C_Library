#ifndef I2C_h
#define I2C_h

#include <avr/io.h>

/* Define the twi timeout */
#define TWI_TIMEOUT          0xFFFF
#define HOLD_MASTER          1
#define NO_HOLD_MASTER       0

/* Macros to Define TWI Bit Rate which is set in TWBR */
#define TWI_SPEED         100000UL /* 100KHz */
#define TWI_BIT_RATE      ((F_CPU/TWI_SPEED)-16)/2
#define TWI_PRESCALER     0x00

#define TW_START          0xA4 /* Send start condition */
#define TW_READY          (TWCR & 0x80) /* Ready when TWINT returns 1 */
#define TWI_START         (1<<TWINT)|(1<<TWSTA)|(1<<TWEN)
#define TWI_STOP          (1<<TWINT)|(1<<TWSTO)|(1<<TWEN)

/* I2C Status codes in TWSR register */
/* Master Transmitter/Receiver status codes in TWSR */
#define TW_STATUS             (TWSR & 0xF8) /* Returns value of status register */
#define START_TRANSMITTED     0x08 /* Start condition transmitted */
#define REPEATED_START        0X10 /* Repeated start condition transmitted */
#define SLA_W_TX_ACK          0X18 /* SLA+W transmitted & ACK received */
#define SLA_W_TX_NACK         0X20 /* SLA+W transmitted & NACK received */
#define DATA_TX_ACK           0X28 /* Data byte transmitted & ACK received */
#define DATA_TX_NACK          0X30 /* Data byte transmitted & NACK received */
#define ARBITRATION_LOST_SLA_W    0x38 /* Arbitration lost in SLA+W or data bytes */
#define SLA_R_TX_ACK          0x40 /* SLA+R transmitted & ACK received */
#define SLA_R_TX_NACK         0x48 /* SLA+R transmitted & NACK received */
#define DATA_RX_ACK           0x50 /* Data byte received & ACK returned */
#define DATA_RX_NACK          0x58 /* Data byte received & NACK returned */

class i2c
{
  public:
    i2c(uint8_t mode);
    void init();
    void start();
    void stop();
    void write(int u8address);
    uint8_t readAck();
    uint8_t readNack();
  private:
    uint8_t _mode;
};

#endif
