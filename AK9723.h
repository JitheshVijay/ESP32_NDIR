#ifndef AK9723_H
#define AK9723_H

#include <Wire.h>

#define AK9723_I2C_ADDR 0x65

#define AK9723_REG_LED_CONTROL 0x00
#define AK9723_REG_LED_INTENSITY 0x01

#define AK9723_LED_ON 0x01
#define AK9723_LED_OFF 0x00

class AK9723 {
public:
  AK9723(); // Constructor
  void begin(); // Initialize AK9723
  void controlLED(uint8_t command); // Control LED (ON/OFF)
  void setLEDIntensity(uint8_t intensity); // Set LED intensity

private:
  void writeRegister(uint8_t reg, uint8_t value); // Write value to register
};

#endif
