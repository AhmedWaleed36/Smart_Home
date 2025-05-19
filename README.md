# 🏠💡 Smart Home System — Design & Implementation

This project showcases the complete implementation of a Smart Home system using the ATMega32 microcontroller. It demonstrates key embedded systems principles including:

    - 🌡️ Environmental monitoring and control
    
    - 🔔 Alert and notification systems
    
    - 🔌 Peripheral device integration
    
    - 🧠 Intelligent decision making
    

✅ Full smart home functionality ✅ Supports multiple sensors and actuators ✅ Designed for ATMega32 microcontroller ✅ Implements layered software architecture

## 🧩 Architecture Design

### 🔁 1. System Overview

The Smart Home system represents a complete embedded application:

    🚦 Uses ATMega32 microcontroller as the core processor
    
    🌡️ Monitors environmental conditions through sensors
    
    🔔 Provides alerts and notifications through buzzers
    
    🔌 Controls various home appliances and devices
    
    🧠 Makes intelligent decisions based on sensor readings
    

### 🧱 2. Hardware Components

The system is built around these key hardware components:

    - 🧠 ATMega32 Microcontroller
    
    - 🌡️ Temperature sensors
    
    - 💧 Humidity sensors
    
    - 🔆 Light sensors
    
    - 🔔 Buzzers for alerts
    
    - 💡 LEDs for status indication
    
    - 🔌 Relays for appliance control
    

### 🔧 3. Software Architecture

The software is organized in a layered architecture:

    - 📂 MCAL (Microcontroller Abstraction Layer)
    
        - GPIO: For digital input/output control
        
        - ADC: For analog sensor readings
        
        - EXIT: For external interrupt handling
        
        - GIE: For global interrupt control
        
    - 📂 HAL (Hardware Abstraction Layer)
    
        - BUZ: For buzzer control
        
        - LED: For LED control and indication
        
        - Sensors: For environmental monitoring
        
    - 📂 LIB (Libraries)
    
        - Standard types and bit manipulation
        
    - 📂 APP (Application Layer)
    
        - Main application logic
        - Decision making algorithms
        

## 🧠 Component Implementations

### 🌡️ 1. Sensor Monitoring System

    - Interfaces with multiple environmental sensors
    
    - 🔢 Converts analog readings to digital values
    
    - 🧮 Processes and interprets sensor data
    
    - 📊 Maintains thresholds for decision making
    

### 🔔 2. Alert System

    - Implements buzzer control for notifications
    
    - 🔄 Configures different alert patterns
    
    - 🚨 Triggers alerts based on sensor thresholds
    
    - 🔇 Provides methods to enable/disable alerts
    

### 🔌 3. Device Control

    - Manages home appliances through relays
    
    - 🔄 Implements on/off functionality
    
    - 🧮 Handles device state management
    
    - ⏱️ Supports timed operations
    

### 💡 4. Status Indication

    - Provides visual feedback through LEDs
    
    - 🔄 Indicates system state and operation modes
    
    - 🚦 Shows alert levels and conditions
    
    - 📊 Displays sensor reading status
    

## 💻 Implementation Details

### 🌡️ 1. Sensor Reading Logic

The ADC module handles sensor readings:

```c
void ADC_Init(ADC_Type ADC_Configuration) {
    // Configure ADC reference voltage
    switch(ADC_Configuration.Reference) {
        case AREF:
            CLR_BIT(ADMUX, REFS0);
            CLR_BIT(ADMUX, REFS1);
            break;
        case AVCC:
            SET_BIT(ADMUX, REFS0);
            CLR_BIT(ADMUX, REFS1);
            break;
        case INTERNAL:
            SET_BIT(ADMUX, REFS0);
            SET_BIT(ADMUX, REFS1);
            break;
    }
    
    // Configure ADC adjustment
    if(ADC_Configuration.Adjustment == LEFT) {
        SET_BIT(ADMUX, ADLAR);
    } else {
        CLR_BIT(ADMUX, ADLAR);
    }
    
    // Configure prescaler
    ADCSRA &= 0xF8;
    ADCSRA |= ADC_Configuration.Prescaler;
    
    // Enable ADC
    SET_BIT(ADCSRA, ADEN);
}
```

### 🔔 2. Buzzer Control System

The buzzer module provides alert functionality:

```c
void BUZ_Init(BUZ_Type BUZ_Configuration) {
    GPIO_SetPinDirection(BUZ_Configuration.Port, BUZ_Configuration.Pin, 
                         PIN_OUTPUT);
}

void BUZ_On(BUZ_Type BUZ_Configuration) {
    if (BUZ_Configuration.Active_Status == ACTIVE_HIGH) {
        GPIO_SetPinValue(BUZ_Configuration.Port, BUZ_Configuration.Pin, 
                         LOGIC_HIGH);
    } else if (BUZ_Configuration.Active_Status == ACTIVE_LOW) {
        GPIO_SetPinValue(BUZ_Configuration.Port, BUZ_Configuration.Pin, 
                         LOGIC_LOW);
    }
}

void BUZ_Off(BUZ_Type BUZ_Configuration) {
    if (BUZ_Configuration.Active_Status == ACTIVE_HIGH) {
        GPIO_SetPinValue(BUZ_Configuration.Port, BUZ_Configuration.Pin, 
                         LOGIC_LOW);
    } else if (BUZ_Configuration.Active_Status == ACTIVE_LOW) {
        GPIO_SetPinValue(BUZ_Configuration.Port, BUZ_Configuration.Pin, 
                         LOGIC_HIGH);
    }
}
```

### 🧠 3. Decision Making Logic

The main application implements intelligent decision making:

```c
// Example decision making logic (conceptual)
void ProcessSensorData() {
    u16 temperature = ADC_GetReading(TEMP_SENSOR_CHANNEL);
    u16 humidity = ADC_GetReading(HUMIDITY_SENSOR_CHANNEL);
    u16 light = ADC_GetReading(LIGHT_SENSOR_CHANNEL);
    
    // Temperature control
    if (temperature > TEMP_HIGH_THRESHOLD) {
        // Turn on cooling
        Device_TurnOn(COOLING_DEVICE);
        // Activate alert if very high
        if (temperature > TEMP_CRITICAL_THRESHOLD) {
            BUZ_On(tempAlertBuzzer);
        }
    } else if (temperature < TEMP_LOW_THRESHOLD) {
        // Turn on heating
        Device_TurnOn(HEATING_DEVICE);
    } else {
        // Normal temperature range
        Device_TurnOff(COOLING_DEVICE);
        Device_TurnOff(HEATING_DEVICE);
        BUZ_Off(tempAlertBuzzer);
    }
    
    // Similar logic for humidity and light control
    // ...
}
```

## 🔧 Development Environment

    - 🔌 Atmel Studio — for code development
    
    - 📟 Proteus — for circuit simulation
    
    - 🔄 AVR-GCC — for compilation
    
    - 📥 AVRDUDE — for microcontroller programming
    

## 🚀 How to Use

### 🔧 1. Hardware Setup

    - Connect sensors to ADC pins as specified in the configuration
    
    - Connect buzzers and LEDs to the designated GPIO pins
    
    - Connect relay modules to control pins for appliance control
    
    - Power the ATMega32 with appropriate voltage (5V)
    

### 💻 2. Software Setup

    - Clone the repository
    
    - Open the project in Atmel Studio
    
    - Configure sensor thresholds in the configuration files
    
    - Build the solution
    
    - Program the ATMega32 using a suitable programmer
    

### 🎮 3. Operation

    - The system starts monitoring automatically after power-on
    
    - LEDs indicate the current status of the system
    
    - Buzzers activate when sensor readings exceed thresholds
    
    - Appliances are controlled automatically based on environmental conditions
    
    - Manual override is possible through connected switches
    

## 👨‍💻 Author

    🧑‍💻 Ahmed Waleed Ahmed
    

## 📜 License

This project was developed as an embedded systems application using the ATMega32 microcontroller.

📘 Note: For full implementation details and circuit diagrams, please refer to the simulation files and source code.
