#include <Wire.h> // Include the Wire library for I2C communication

// Define the I2C addresses of the devices
#define LED_DRIVER_ADDR 0x65 // Address of the LED driver IC
#define PHOTODIODE_ADDR 0x68 // Address of the photodiode sensor

// Define register addresses for LED driver
#define REG_LED_CONTROL 0x00 // Register address for LED control
#define REG_LED_INTENSITY 0x01 // Register address for LED intensity control

// Define register addresses for photodiode
#define REG_PHOTODIODE_DATA 0x00 // Register address for photodiode data

// Define LED control commands
#define LED_ON 0x01 // Command to turn on the LED
#define LED_OFF 0x00 // Command to turn off the LED

// Define constants
#define LED_ON_TIME_MS 4000 // Time duration for LED ON in milliseconds
#define LED_OFF_TIME_MS 4000 // Time duration for LED OFF in milliseconds
#define MAX_LED_INTENSITY 255 // Maximum LED intensity value

// Function to initialize the I2C communication
void setup() {
  Wire.begin(); // Initialize the I2C communication
  Serial.begin(9600); // Initialize serial communication for debugging
}

// Function to control the LED
void controlLED(uint8_t command) {
  Wire.beginTransmission(LED_DRIVER_ADDR); // Begin transmission to LED driver IC
  Wire.write(REG_LED_CONTROL); // Send LED control register address
  Wire.write(command); // Send LED control command
  Wire.endTransmission(); // End transmission
}

// Function to set LED intensity
void setLEDIntensity(uint8_t intensity) {
  Wire.beginTransmission(LED_DRIVER_ADDR); // Begin transmission to LED driver IC
  Wire.write(REG_LED_INTENSITY); // Send LED intensity register address
  Wire.write(intensity); // Send LED intensity value
  Wire.endTransmission(); // End transmission
}

// Function to read photodiode data
uint16_t readPhotodiodeData() {
  Wire.beginTransmission(PHOTODIODE_ADDR); // Begin transmission to photodiode sensor
  Wire.write(REG_PHOTODIODE_DATA); // Send photodiode data register address
  Wire.endTransmission(false); // End transmission without releasing the bus

  Wire.requestFrom(PHOTODIODE_ADDR, 2); // Request 2 bytes of data from photodiode
  if (Wire.available()) { // Check if data is available to read
    byte msb = Wire.read(); // Read most significant byte
    byte lsb = Wire.read(); // Read least significant byte
    uint16_t data = (msb << 8) | lsb; // Combine bytes to form 16-bit data
    return data; // Return photodiode data
  }
  return 0; // Return 0 if data is not available
}

void loop() {
  // Turn on the LED
  controlLED(LED_ON); // Send command to turn on the LED
  delay(LED_ON_TIME_MS); // Wait for LED ON time

  // Turn off the LED
  controlLED(LED_OFF); // Send command to turn off the LED
  delay(LED_OFF_TIME_MS); // Wait for LED OFF time

  // Read photodiode data and adjust LED intensity
  uint16_t photodiodeData = readPhotodiodeData(); // Read photodiode data
  // Assuming ambient light intensity is proportional to photodiode data
  uint8_t ledIntensity = map(photodiodeData, 0, 1023, 0, MAX_LED_INTENSITY); // Map photodiode data to LED intensity range
  setLEDIntensity(ledIntensity); // Set LED intensity based on ambient light intensity

  // Print photodiode data and LED intensity for debugging
  Serial.print("Photodiode Data: ");
  Serial.println(photodiodeData);
  Serial.print("LED Intensity: ");
  Serial.println(ledIntensity);

  delay(1000); // Delay of 1 second for stability
}
