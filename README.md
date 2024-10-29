# Smart Street Light Detection System Using NodeMCU

This project implements a smart street light system using a NodeMCU (ESP8266), ultrasonic sensor, light sensor, and the Blynk IoT platform. The system controls the LED street light based on ambient brightness and proximity detection, optimizing energy consumption. It also includes a panic button to notify users in case of an emergency.

## Table of Contents
- [Project Overview](#project-overview)
- [Features](#features)
- [Components Required](#components-required)
- [Circuit Diagram](#circuit-diagram)
- [Setup and Installation](#setup-and-installation)
- [Usage](#usage)
- [Code Explanation](#code-explanation)
- [License](#license)

---

## Project Overview

The smart street light system uses NodeMCU to control an LED light, which turns on based on ambient light and proximity detection. The project includes:
- **Automatic light control** using a light sensor and ultrasonic sensor.
- **Manual and automatic modes** controlled via the Blynk app.
- **Emergency notifications** through a panic button that sends alerts to the Blynk app.

## Features

- **Automatic LED Control**: LED adjusts based on ambient brightness and proximity detection.
- **Remote Control**: Control LED manually or set its brightness through the Blynk app.
- **Panic Button**: Sends a notification to the Blynk app if the panic button is pressed.

## Components Required

- NodeMCU (ESP8266)
- Ultrasonic Sensor (HC-SR04)
- Light Sensor (LDR)
- Relay Module (for controlling high-power LED)
- LED light (or small bulb for testing)
- Push Button (for panic notification)
- Jumper Wires
- Blynk App (installed on a smartphone)

## Circuit Diagram

![Circuit Diagram](#) <!-- Link to circuit diagram image if available -->

## Setup and Installation

### 1. Hardware Connections
- **LED Light**: Connect to NodeMCU pin D5.
- **Ultrasonic Sensor**: 
  - Trigger Pin to D3
  - Echo Pin to D4
- **Light Sensor (LDR)**: Connect to analog pin A0.
- **Panic Button**: Connect to pin D7.

### 2. Install Libraries
Ensure you have the following libraries installed in your Arduino IDE:
- [ESP8266WiFi](https://github.com/esp8266/Arduino) for Wi-Fi connectivity.
- [Blynk Library](https://github.com/blynkkk/blynk-library) for Blynk app integration.

### 3. Blynk App Setup
1. Create a new project in the Blynk app and select **NodeMCU** as the device.
2. Add the following widgets to the project:
   - **Slider (V3)**: To control LED intensity.
   - **Button (V2)**: To enable or disable automatic detection.
   - **LED (V1)**: To display the LED’s state.
3. Obtain the **Auth Token** from the Blynk app and add it to the code.

### 4. Code Setup
1. Clone or download this repository.
2. Open the code in your Arduino IDE.
3. Update the following in the code:
   - **Wi-Fi credentials**: Replace with your Wi-Fi SSID and password.
   - **Auth Token**: Replace with the Blynk Auth Token.
4. Upload the code to your NodeMCU.

## Usage

1. Power on the NodeMCU.
2. The LED light will turn on automatically at night and when a vehicle or object is detected within 10 cm.
3. Control the LED intensity and mode (manual/automatic) through the Blynk app.
4. Press the panic button to receive an emergency notification on the Blynk app.

## Code Explanation

The main parts of the code are:
1. **Wi-Fi and Blynk Initialization**: Connects NodeMCU to Wi-Fi and initializes the Blynk connection.
2. **Ultrasonic Sensor Measurement**: Measures distance using the ultrasonic sensor to detect nearby objects.
3. **Automatic Light Control**: Controls the LED brightness based on ambient light and proximity detection.
4. **Manual Control and Intensity Adjustment**: Allows LED control through the Blynk app, including setting brightness via a slider.
5. **Panic Button Notification**: Sends an alert to the Blynk app if the button is pressed.

For detailed code explanation, see the code comments in `SmartStreetLight.ino`.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
