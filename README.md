# ESP32_NDIR

 Utilizing the AK9723 LED driver and AK9730 photodiode to control the operation and intensity of an infrared LED (AK9703) based on ambient light conditions.
 
# AK9723AJ LED driver and Sensor AFE

AK9723AJ is an IR LED driver and Analog Front End (AFE) IC designed for signal processing of IR photo detectors. It features a dual-channel AFE and an ADC for digital output, enabling IR photo detector output signals to be obtained simultaneously. The AK9723AJ is suitable for NDIR (Non-Dispersive Infrared) gas sensing applications using IR LED and IR photo detectors.

## General Description

- Integrated LED Driver with Programmable Constant Current Circuit
- Dual-Channel Input AFE
- Communication via I2C bus with HOST MCU
- Suitable for NDIR gas sensing applications

## Features

- Oscillator (OSC)
- Reference voltage and reference current generator (VIREF)
- Temperature sensor (TSENS)
- Sigma-delta analog-to-digital converter (ADC1/2)
- LED constant current driver (LED DRIVER)
- Register (REGISTER) to store measurement data, operation mode, and timing value

## Pin Functions

- I2C communication, interrupt, power-down, test, IR photo detector connections, LED driver output, power supply, and ground

## Operating Conditions

- Operating temperature range: -40°C to 85°C
- Power Supply Voltage Range: 2.7V to 3.6V

## Electrical Characteristics

- Analog, digital, and AC characteristics specified
- Supports I2C bus interface with standard mode (up to 100kHz) and fast mode (up to 400kHz)

# AK9703AJ IR LED

AK9703AJ is a small mid-infrared quantum photodiode optimized for NDIR gas sensing applications. It features high sensitivity, high-speed response, and high reliability.

## Features

- High sensitivity with a signal-to-noise ratio three times higher than conventional thermopiles
- High-speed response of approximately 100kHz
- Built-in optical band-pass filter with a centre wavelength (CWL) of 3.32μm
- Compact 3mm x 3mm surface-mount plastic package

## Applications

- NDIR gas sensing applications, including methane (CH4), R32, etc.

## Operating Conditions

- Operating temperature range: -40°C to 85°C

## Electrical Characteristics

- Output current ranges from 2.9nA to 14.2nA
- Internal resistance ranges from 15kΩ to 250kΩ

# AK9730AJF21 IR Sensor

AK9730AJF21 is a miniaturized mid-infrared light-emitting diode optimized for NDIR gas sensing applications. It operates at room temperature and offers high radiant intensity, high-speed response, and high reliability.

## Features

- High radiant intensity with a peak wavelength (λp) of 3.6μm
- Angle of half intensity (Φ) is 60°
- Suitable for high-speed pulse current operation
- Compact 2.6mm x 1.9mm x 0.4mm surface-mount package

## Applications

- NDIR gas sensing applications, including methane (CH4), R32, etc.

## Absolute Maximum Ratings

- Reverse Voltage (VR): 1V
- Forward Current (IF): 0.5A
- Power Dissipation (PV): 110mW
- Operating Temperature: -40°C to 85°C

## Recommended Operating Conditions

- Forward Current (IF): 100mA to 125mA (Duty cycle: 0.15%, Pulse width: 0.25ms)

## Electrical Characteristics

- Output Current (Ip) of the calibrated infrared sensor ranges from 1.43nA to 5.73nA
- Internal Resistance (Ro) of the calibrated infrared sensor ranges from 18kΩ to 589kΩ

# Algorithm Outlining the Thought Process for the Code

## 1. Initialize Hardware
   - Set up the microcontroller and establish communication with the AK9723 LED driver and AK9730 photodiode using the Wire library.

## 2. Define Constants
   - Define necessary constants such as I2C addresses, register addresses, LED control commands, LED on/off time, and maximum LED intensity.

## 3. Control LED
   - Implement functions to control the LED. These functions should include commands to turn the LED on/off and set its intensity.

## 4. Read Photodiode Data
   - Implement a function to read data from the AK9730 photodiode. This function should request data from the photodiode and interpret the response to obtain ambient light intensity.

## 5. Main Loop
   - Turn on the LED for a specified duration.
   - Turn off the LED for an equal duration.
   - Read data from the photodiode to measure ambient light intensity.
   - Adjust the LED intensity based on the ambient light level measured by the photodiode.
   - Serially print photodiode data and LED intensity for monitoring purposes.
   - Continuous Execution: Repeat the main loop continuously to maintain LED operation and intensity control.

# Description of Main Code

The main code consists of functions and a main loop to control the AK9723 LED driver and AK9730 photodiode. It initializes the hardware, defines constants, controls the LED, reads photodiode data, and adjusts LED intensity based on ambient light levels. The code utilizes the Wire library for I2C communication and includes comments for clarity and understanding.

# Description of Header Files

The header files include declarations for functions and constants related to the AK9723 LED driver and AK9730 photodiode. They provide an interface for the main code to interact with the hardware components, abstracting the implementation details and promoting modularity and reusability.


