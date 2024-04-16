#ifndef AK9723_H
#define AK9723_H
#include <Wire.h>

// I2C address of the AK9723 device
#define AK9723_I2C_ADDR 0x65

// Register addresses
#define AK9723_REG_WIA1           0x00  // Company code (read-only)
#define AK9723_REG_WIA2           0x01  // Device ID (read-only)
#define AK9723_REG_INFO1          0x02  // Information 1 (reserved, read-only)
#define AK9723_REG_INFO2          0x03  // Information 2 (reserved, read-only)
#define AK9723_REG_ST1            0x04  // Status 1
#define AK9723_REG_IR1L           0x05  // IR sensor 1 measurement data (lower 8 bits)
#define AK9723_REG_IR1M           0x06  // IR sensor 1 measurement data (middle 8 bits)
#define AK9723_REG_IR1H           0x07  // IR sensor 1 measurement data (upper 8 bits)
#define AK9723_REG_IR2L           0x08  // IR sensor 2 measurement data (lower 8 bits)
#define AK9723_REG_IR2M           0x09  // IR sensor 2 measurement data (middle 8 bits)
#define AK9723_REG_IR2H           0x0A  // IR sensor 2 measurement data (upper 8 bits)
#define AK9723_REG_TMPL           0x0B  // Temperature sensor data (lower 8 bits)
#define AK9723_REG_TMPH           0x0C  // Temperature sensor data (upper 8 bits)
#define AK9723_REG_VFL            0x0D  // LED forward voltage data (lower 8 bits)
#define AK9723_REG_VFH            0x0E  // LED forward voltage data (upper 8 bits)
#define AK9723_REG_CNTL1          0x0F  // Control 1
#define AK9723_REG_CNTL2          0x10  // Control 2
#define AK9723_REG_CNTL3          0x11  // Control 3
#define AK9723_REG_CNTL4          0x12  // Control 4
#define AK9723_REG_CNTL5          0x13  // Control 5
#define AK9723_REG_CNTL6          0x14  // Control 6
#define AK9723_REG_CNTL7          0x15  // Control 7
#define AK9723_REG_CNTL8          0x16  // Control 8
#define AK9723_REG_CNTL9          0x17  // Control 9
#define AK9723_REG_CNTL10         0x18  // Control 10

// Status 1 register bits
#define AK9723_OVCUR_DET_BIT      7 // Overcurrent error flag bit
#define AK9723_ERR_FLAG_BIT       6  // Error flag bit
#define AK9723_DRDY_BIT           5  // Data ready bit

// Control 1 register bits
#define AK9723_MLOOP_MASK         0xF  // Measurement loop setting bits

// Control 5 register bits
#define AK9723_ERR_DIS_BIT        1  // Error flag interrupt disable bit
#define AK9723_DRDY_DIS_BIT       0  // Data ready interrupt disable bit

// Control 6 register bits
#define AK9723_MODE_MASK          2  // Operating mode setting bits

class AK9723 {
public:
  AK9723(uint8_t address = AK9723_I2C_ADDR);
  ~AK9723();

  int begin();
  int controlLED(uint8_t command);  // Control LED (on/off likely)
  int setLEDIntensity(uint8_t intensity);  // Set LED intensity (brightness control)
  int hardwareReset();
  int softReset();
  int setOperatingMode(uint8_t mode);  // Set operation mode (standby, single measurement)
  int readIRSensorData(uint8_t sensorNumber, uint32_t& data);
  int readTemperatureSensorData(uint16_t& temperature);// Function to read temperature sensor data
  int readLEDForwardVoltage(uint16_t& voltage);// Function to read LED forward voltage data

private:
  uint8_t _address;
  int writeRegister(uint8_t reg, uint8_t value);
  int readRegister(uint8_t reg, uint8_t* data, uint8_t len);
};


int AK9723::begin() {
  Wire.begin();// Initialize the Wire library for I2C communication
  return 0; 
}

int AK9723::controlLED(uint8_t command) {
  return writeRegister(AK9723_REG_CNTL6, command);
}

int AK9723::setLEDIntensity(uint8_t intensity) {
  return writeRegister(AK9723_REG_CNTL7, intensity);
}

int AK9723::hardwareReset()  {
  Wire.beginTransmission(_address);
  Wire.write(AK9723_REG_CNTL10); // Select the control 10 register
  Wire.write(0x80); // Set the SRST bit to 1 for hardware reset
  Wire.endTransmission();
  delay(10); // Delay to allow the reset to take effect
  return 0; // Return 0 for success, you can modify this based on the actual implementation
}

int AK9723::softReset()  {
  Wire.beginTransmission(_address);
  Wire.write(AK9723_REG_CNTL10); // Select the control 10 register
  Wire.write(0x40); // Set the SRST bit to 1 for soft reset
  Wire.endTransmission();
  delay(10); // Delay to allow the reset to take effect
  return 0; // Return 0 for success, you can modify this based on the actual implementation
}

int AK9723::setOperatingMode(uint8_t mode) {
  // Set operating mode implementation
  if (mode == 0) {
    // Power Down Mode
    // Write to Control 6 register (CNTL6) to set MODE[1:0] bits to "00"
    return writeRegister(AK9723_REG_CNTL6, 0b00000000);
  } else if (mode == 1) {
    // Stand-by Mode
    // Write to Control 6 register (CNTL6) to set MODE[1:0] bits to "00"
    return writeRegister(AK9723_REG_CNTL6, 0b00000000);
  } else if (mode == 2) {
    // Single Measurement Mode
    // Write to Control 6 register (CNTL6) to set MODE[1:0] bits to "10"
    return writeRegister(AK9723_REG_CNTL6, 0b00000010);
  } else {
    return -1; // Error: Invalid mode
  }
}

int AK9723::writeRegister(uint8_t reg, uint8_t value) {
  // Start the I2C communication
  Wire.beginTransmission(_address);
  
  // Send the register address
  Wire.write(reg);
  
  // Send the value to write
  Wire.write(value);
  
  // End the transmission
  int error = Wire.endTransmission();

  // Check if transmission was successful
  if (error != 0) {
    // Transmission error
    return -1; // Error: Transmission failed
  }
  return 0; 
}

int AK9723::readRegister(uint8_t reg, uint8_t* data, uint8_t len) {
  // Start the I2C communication
  Wire.beginTransmission(_address);
  
  // Send the register address
  Wire.write(reg);
  
  // End the transmission
  int error = Wire.endTransmission(false); // Send repeated start

  // Check if transmission was successful
  if (error != 0) {
    // Transmission error
    return -1; // Error: Transmission failed
  }
  
  // Request data from the device
  Wire.requestFrom(_address, len);
  
  // Check if data was received
  if (Wire.available() != len) {
    // Data reception error
    return -2; // Error: Data reception failed
  }
  
  // Read the received data
  for (int i = 0; i < len; i++) {
    data[i] = Wire.read();
  }
  
  return 0; 
}
int AK9723::readTemperatureSensorData(uint16_t& temperature) {
  uint8_t temp_lsb, temp_msb;
  int result = readRegister(AK9723_REG_TEML, &temp_lsb, 1); // Read lower 8 bits of temperature data
  if (result != 0) return result;
  result = readRegister(AK9723_REG_TEMH, &temp_msb, 1); // Read upper 8 bits of temperature data
  if (result != 0) return result;
  
  temperature = (static_cast<uint16_t>(temp_msb) << 8) | temp_lsb; // Combine upper and lower bytes
  return 0; 
}

int AK9723::readLEDForwardVoltage(uint16_t& voltage) {
  uint8_t vf_lsb, vf_msb;
  int result = readRegister(AK9723_REG_VFL, &vf_lsb, 1); // Read lower 8 bits of LED forward voltage data
  if (result != 0) return result;
  result = readRegister(AK9723_REG_VFH, &vf_msb, 1); // Read upper 8 bits of LED forward voltage data
  if (result != 0) return result;
  
  voltage = (static_cast<uint16_t>(vf_msb) << 8) | vf_lsb; // Combine upper and lower bytes
  return 0; 
}

#endif
