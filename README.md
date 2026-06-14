# ARDUINO HOME SECURITY PROJECT:

## Description Of The Project :

My project consists of various modules to secure the home and protect it from intruders and fire accidents.  
I have used an RFID kit with a solenoid lock in this model. Only Authorized personnel, owning the authorized card may scan it and open the lock on the door.  
Further more the window of the house is protected by a laser tripwire (constructed with a laser module and a photoresistor). In case of any kind of home invasion or breach, the alarms will ring and the LCD screen will display a warning. The laser system can be turned off by using an authorized RFID tag which will allow the user to ARM / DISARM the laser system.  
My security system also includes a Flame sensor. If it detects any fire, the lock will open automatically to allow a swift escape; while the buzzer beeps alerting the residents.

## Components Used :

-  RFID kit
- Arduino Nano
- Solenoid Lock
- 5 Volt Active Relay
- Laser module
- Photoresistor
- 12 Volt power supply (adapter to power the solenoid lock)

## Phase 1 - Access authorization and management using RFID :

-  RFID Module
- Arduino Nano
- 16 x 2 LCD I2C Module

### RFID Connections : 

| Components | Pin      | Arduino Nano pin |
| ---------- | -------- | ---------------- |
| MFRC522    | SDA (SS) | Pin 10           |
|            | SCK      | Pin 13           |
|            | MOSI     | Pin 11           |
|            | MISO     | Pin 12           |
|            | GND      | GND              |
|            | RST      | Pin 9            |
|            | 3.3 V    | 3.3 V            |
| I2C LCD    | GND      | GND              |
|            | VCC      | 5V               |
|            | SDA      | A4               |
|            | SCL      | A5               |

The RFID scanner will scan authorized cards and display “ARMED”/ “DISARMED” or “DOOR UNLOCKED” on the LCD display.

## PHASE 2 : Making the Laser Tripwire:

- Laser Module
- Photoresistor
- Buzzer
### Connections of the Laser Trip wire : 

| Component    | Arduino Pin |
| ------------ | ----------- |
| Laser Module | D3          |
| LDR Module   | D4          |
| Buzzer       | D5          |

The Laser module and the LD module are attached across a window, creating a laser trip wire. In case of a security breach like home invasion through the windows, burglaries or robberies, the laser will detect the breach and the buzzer will ring as well as a Warning will be displayed on the LCD.

## PHASE 3 : Entry and solenoid lock unlocking for authorised personnel

- Solenoid Lock
- 5 Volt Active Relay
- 12 Volt power source (adapter)
### Connections of Solenoid Lock: 

| Arduino Nano | Relay |
| ------------ | ----- |
| 5 V          | VCC   |
| GND          | GND   |
| D7           | IN    |

| Some More Connections :    |                           |
| -------------------------- | ------------------------- |
| 12 V Adapter Positive (+)  | Relay COM                 |
| Relay NO (Normally Open)   | Solenoid Lock's red wire  |
| Solenoid Lock's Black wire | 12 V Adapter Negative (-) |

The RFID reader will read the RFID tag, and if it is authorized the solenoid lock will open. In the case of unauthorized tags, a beep will sound from the buzzer. And LCD will display access denied messages.

## PHASE 4 : Flame sensor for Fire Alarm:
- Flame Sensor
- Buzzer Module
- Solenoid Lock
### Connections of Flame Sensor : 

| Arduino Nano | Flame Sensor |
| ------------ | ------------ |
| 5V           | VCC          |
| GND          | GND          |
| D6           | DO           |

Whenever the flame sensor will detect a fire, the solenoid lock will automatically unlock for the easy escape of residents, as well as the buzzer will beep loudly until the fire alarm is manually turned off through the Arduino reset button.



  


 
