#ifndef AK9730_H
#define AK9730_H

#include <Wire.h>

#define AK9730_I2C_ADDR 0x68

#define AK9730_REG_PHOTODIODE_DATA 0x00

class AK9730 {
public:
  AK9730(); // Constructor
  void begin(); // Initialize AK9730
  uint16_t readPhotodiodeData(); // Read photodiode data

private:
  uint16_t readRegister(uint8_t reg); // Read value from register
};

#endif
