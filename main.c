#include <Wire.h>
#include <AK9723.h>
#include <AK9730.h>

// Define LED pin
const int LED_PIN = 13;

// Define Photodiode pin
const int PHOTODIODE_PIN = A0;

// Create instances of LED driver and Photodiode classes
AK9723 ledDriver;
AK9730 photodiode;

void setup() {
  // Initialize LED pin as output
  pinMode(LED_PIN, OUTPUT);

  // Initialize I2C communication
  Wire.begin();

  // Set LED driver to power-down mode
  ledDriver.setOperatingMode(PDN_MODE);

  // Initialize LED driver
  ledDriver.init();

  // Initialize Photodiode
  photodiode.init();
}

void loop() {
  //Turn ON the LED for 4 seconds and Turn OFF the LED for another 4 seconds
  digitalWrite(LED_PIN, HIGH); // Turn ON the LED
  delay(4000); // Wait for 4 seconds
  digitalWrite(LED_PIN, LOW); // Turn OFF the LED
  delay(4000); // Wait for another 4 seconds

  //Control the intensity of the LED wrt ambient light intensity
  int ambientLight = photodiode.getAmbientLight(); // Read ambient light intensity
  int ledIntensity = map(ambientLight, 0, 1023, 0, 255); // Map ambient light intensity to LED intensity

  // Set LED intensity
  ledDriver.setLEDIntensity(ledIntensity);

  // Add some delay for stability
  delay(1000);
}
