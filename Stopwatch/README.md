# StopWatch Project for AT89C51 Microcontroller

![image](https://github.com/user-attachments/assets/248a01b0-6a61-4a8a-8e63-e9f422b7b8ce)

## Overview
This project implements a simple stopwatch using the AT89C51 microcontroller with the following features:
- Start/Stop functionality
- Reset capability
- 4-digit 7-segment display showing minutes and seconds (MM:SS format)
- Accurate timing using Timer 0 interrupts

## Hardware Requirements
- AT89C51 microcontroller
- Four 7-segment common cathode displays
- Two push buttons (Start/Stop and Reset)

## Pin Configuration
- **P1**: 7-segment data lines (connected to segment pins)
- **P2**: Digit selection lines (active low)
- **P3.0**: Start/Stop button (active low)
- **P3.1**: Reset button (active low)

## Software Implementation
- Developed using Keil µVision IDE
- Written in C language 
- Uses Timer 0 interrupt for accurate timing
- Implements multiplexing for 7-segment displays

## Key Components
1. **Timer Configuration**:
   - Timer 0 in mode 1 (16-bit)
   - Interrupt every 10ms (100Hz)
   - 100 interrupts = 1 second

2. **Display Handling**:
   - Multiplexed display refresh
   - Segment codes stored in lookup table
   - Four digits show minutes and seconds (MM:SS)

3. **Button Handling**:
   - Debouncing implemented with simple delay
   - Start/Stop toggles counting
   - Reset clears all counters

## Simulation
The project has been simulated in Proteus with:
- Virtual AT89C51 microcontroller
- 7-segment display components
- Push button components

## How to Use
1. Press the Start/Stop button to begin counting
2. Press again to pause
3. Press Reset to clear the counter to 00:00

## Compilation and Burning
1. Open project in Keil µVision
2. Build the project to generate HEX file
3. Load HEX file into AT89C51 in Proteus simulation
4. For real hardware, program the HEX file onto the AT89C51 chip

> [!NOTE]
> Button debouncing is minimal - may need improvement for real hardware

## Future Enhancements
- [ ]  Add milliseconds display
- [ ]  Implement better button debouncing
- [ ]  Add lap time functionality
- [ ]  Include EEPROM for storing best times

___

This project demonstrates fundamental embedded concepts including:
- Timer programming
- Interrupt handling
- Display multiplexing
- Button input handling
