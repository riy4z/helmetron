# Helmetron

IoT-based smart helmet system with LeNet CNN for drowsiness detection, blind spot monitoring, accident detection, and GPS tracking. Built with Arduino Uno.

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Hardware Requirements](#hardware-requirements)
- [Software Requirements](#software-requirements)
- [System Architecture](#system-architecture)
- [Installation](#installation)
- [Usage](#usage)
- [Performance Metrics](#performance-metrics)
- [Project Structure](#project-structure)
- [Future Work](#future-work)
- [License](#license)
- [Acknowledgments](#acknowledgments)

## Overview

Helmetron is a prototype smart helmet safety system that combines live drowsiness detection, ultrasonic blind spot monitoring, accident sensing, and GSM alerting. This repository contains the code for the current implementation:

- Python-based drowsiness detection using eye aspect ratio
- Arduino firmware for the vehicle and helmet units
- Ultrasonic range sensing helpers and test sketches
- GSM SMS alert support
- Project documentation and paper in `docs/`

## Features

Helmet Status Monitoring

Helmet unit firmware checks a helmet status switch and displays a warning if the helmet is not worn.

Drowsiness Detection

The Python script detects driver fatigue using facial landmarks and eye aspect ratio. It displays alerts and can activate the external safety system via serial input.

Blind Spot Monitoring

Ultrasonic sensor code and vehicle firmware support obstacle detection with a rotating servo mechanism.

Accident Detection

Vibration input is used to detect collision or impact conditions and trigger emergency behavior in the vehicle controller.

GSM Emergency Alerts

The vehicle unit can send SMS alerts via a SIM800L module when a critical condition is detected.

Obstacle Warning

Ultrasonic scanning helps identify nearby obstacles; the vehicle firmware can disable outputs when proximity thresholds are exceeded.

## Hardware Requirements

Component                     Specification
----------------------------  ------------------------------
Microcontroller               Arduino Uno
Webcam or USB camera          Standard webcam
Ultrasonic Sensor             HC-SR04
Servo Motor                   SG90 or equivalent
Vibration Sensor              SW-420
GSM Module                    SIM800L
Push Button                   Tactile switch
Power Supply                  12V to 5V DC converter
Connecting Wires              Male-to-female jumper wires

## Software Requirements

Software                      Version
----------------------------  ----------
Arduino IDE                   1.8.x or higher
Python                        3.7 or higher
OpenCV                        4.x
dlib                          19.x
imutils                       0.5.x
scipy                         1.7.x
pyserial                      3.x

## System Architecture

The codebase is organized into two main functional areas:

Helmet Unit

  - Helmet status input
  - Vibration-based impact detection
  - Local status display and alert logic

Vehicle Unit

  - Ultrasonic blind spot sensing
  - Servo control for sensor scanning
  - GSM SMS alerting via SIM800L
  - Serial communication with the helmet unit / PC

## Installation

1. Clone the repository

   git clone https://github.com/riy4z/helmetron.git
   cd helmetron

2. Install Python dependencies

   pip install -r requirements.txt

3. Download facial landmark predictor

   wget http://dlib.net/files/shape_predictor_68_face_landmarks.dat.bz2
   bunzip2 shape_predictor_68_face_landmarks.dat.bz2

4. Upload Arduino firmware

   Open `Helmet_Arduino/HELM.ino` in Arduino IDE for the vehicle unit.
   Open `Helmet_Arduino/helmet_ruino.ino` in Arduino IDE for the helmet unit.
   Select Board: Arduino Uno
   Select Port: (your COM port)
   Click Upload

5. Configure GSM module

   Insert an active SIM card into the SIM800L module
   Update the recipient phone number in `Helmet_Arduino/gsm.h` if needed
   Set APN settings for your mobile network provider if required

6. Run the drowsiness detection system

   python "Drowsiness Detection/drowsiness_detection_live.py" --shape-predictor shape_predictor_68_face_landmarks.dat

## Usage

Starting the System

1. Power on the helmet unit and vehicle unit.
2. Run the Python drowsiness detection script.
3. Ensure the SIM800L module is connected and powered.
4. Present the webcam to the driver for live monitoring.

Normal Operation

- Helmet status is monitored by the helmet unit.
- Drowsiness detection runs from the Python script.
- Ultrasonic sensors monitor obstacles in the vehicle unit.
- GSM alerts are sent when an accident condition is detected.

Emergency Response

When an accident is detected:

1. Vibration sensor triggers the emergency sequence
2. Vehicle unit sends an SMS alert via GSM
3. The system can display warnings and disable outputs as configured

## Performance Metrics

Metric                                    Accuracy
---------------------------------------  ----------
Helmet status monitoring                 N/A
Drowsiness detection (EAR-based)         N/A
Blind spot vehicle detection             N/A
Accident detection (prototype)           N/A
GSM message delivery time                5-10 seconds

## Project Structure

helmetron/
│
├── Drowsiness Detection/
│   ├── drowsiness_detection_live.py   # Live drowsiness detection script
│   ├── LENET.h5                       # Pre-trained model weights
│   └── LENET.ipynb                    # Notebook for model experiments
│
├── Helmet_Arduino/
│   ├── HELM.ino                       # Vehicle unit firmware
│   ├── helmet_ruino.ino               # Helmet unit firmware
│   └── gsm.h                          # GSM helper functions
│
├── Ultrasonic Ranging/
│   ├── ultrasonic.cpp                 # Ultrasonic sensor implementation
│   ├── ultrasonic.h                   # Ultrasonic sensor header
│   └── ultrasonic.ino                 # Ultrasonic test sketch
│
├── docs/
│   └── IEEE smart helmet.pdf         # Project research paper
│
├── LICENSE
└── README.md

## Documentation

- `docs/IEEE smart helmet.pdf`: project research paper and design summary

## Future Work

Bioelectric Sensors

Integration of sensors to monitor battery level, tire pressure, and fuel status.

Onboard Camera

Installation of camera on motorcycle or helmet to monitor rider behavior and enforce route restrictions.

Vehicle-to-Vehicle Communication

Implementation of sensors to enable motorcycles to share information about traffic congestion, accidents, and road hazards with other vehicles.

Solar Power Integration

Addition of solar panels to helmet for charging rider's mobile devices.

Enhanced Security Sensors

Inclusion of temperature sensors and MQ-2 alcohol detection sensors.

Phone Usage Detection

Implementation of microphone sensors to detect if rider is engaged in phone conversations while riding.

## Contributing

Contributions to Helmetron are welcome. Please follow these steps:

1. Fork the repository
2. Create a feature branch (git checkout -b feature/YourFeature)
3. Commit your changes (git commit -m 'Add YourFeature')
4. Push to the branch (git push origin feature/YourFeature)
5. Open a Pull Request

## License

This project is licensed under the MIT License. See the LICENSE file for details.

## Acknowledgments

This project is based on the research paper:

"IoT based smart helmet with Frequency based vehicle control"
Abdur Rahmaan Syed, Mrs.Valarmathi P, Dr.I.Karthiga, Abdullah M, Riyas Ahamed J
BS Abdur Rahman Crescent Institute of Science and Technology, Chennai, India

Research referenced from:
- Mohammad Ehsanul Alim et al. - Design & Implementation of IoT Based Smart Helmet for Road Accident Detection
- Pranav Pathak - IoT based Helmet with Motor vehicle Unit for Enhanced Safety
- A. Jesudoss et al. - Smart helmet for accident avoidance (ICCSP 2019)

Special thanks to the Arduino and dlib open-source communities.

The included research paper is available in `docs/IEEE smart helmet.pdf`.

## Contact

For questions, suggestions, or collaboration inquiries:

- Open an issue on GitHub

## Disclaimer

Helmetron is a safety assistance system and does not replace attentive and responsible riding. Always follow local traffic laws and safety regulations. The authors are not liable for any accidents, damages, or injuries resulting from the use or misuse of this system.