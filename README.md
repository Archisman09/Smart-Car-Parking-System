# Smart Car Parking System

## Overview

The Smart Car Parking System is an innovative project that leverages IoT and RFID technologies to create an efficient, human-less parking management system. This project utilizes an ESP32 microcontroller to automate the management of parking spaces while ensuring security and ease of use for authorized vehicles.

## Features

- **Automated Gate Operation**: Entry and exit gates controlled by RFID authorization.
- **Parking Slot Monitoring**: Real-time tracking of parking slot availability using Infrared (IR) sensors.
- **Data Logging**: Automatic logging of vehicle entry and exit times into a Google Sheet.
- **Visual Indicators**: Clear status indicators for gate operations using LEDs.
- **Mobile Control**: Remote control and monitoring via the Blynk app.

## Technology Stack

- **Microcontroller**: ESP32
- **Authentication**: RFID technology
- **Integration**: Google Sheets for data logging
- **Mobile App**: Blynk for remote control

## Components Used

- ESP32 Microcontroller
- RFID Reader
- Infrared (IR) Sensors (6 total)
- Servo Motors (for gate operation)
- LEDs (Green and Red for visual status)
- LCD Display
- Buzzer (for authorization feedback)
- Jumper Wires and Breadboard for connections

## File Structure

- `parking.ino`: Arduino code for the Smart Car Parking System.
- `Google Sheet Integration.txt`: Instructions and information on integrating Google Sheets for data logging.

## Installation

1. **Clone the Repository**:
   To clone this repository, use the following command:
   git clone https://github.com/Archisman09/Smart-Car-Parking-System.git

2. **Upload Code**:
   - Open the `SmartCarParking.ino` file in the Arduino IDE.
   - Upload the code to the ESP32 microcontroller.

3. **Google Sheets Integration**:
   - Follow the instructions in `GoogleSheetIntegration.txt` to set up data logging.

4. **Mobile App Setup**:
   - Download the Blynk app and set up the necessary controls as per your requirements.

## Usage

- The system will automatically manage parking slots and control gate operations based on RFID authorization.
- Users can monitor and control the parking system remotely using the Blynk app.

## Contributing

Contributions are welcome! Please feel free to submit a pull request or open an issue if you find any bugs or have suggestions for improvements.

## License

This project is open-source and available under the [MIT License](LICENSE).

## Contact

For any inquiries, please reach out to [Archisman09](https://github.com/Archisman09).
