#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//PIN DEFINITIONS

#define SS_PIN 10
#define RST_PIN 9
#define IR_PIN 2       // Infrared Sensor
#define FLAME_PIN 3    // Flame Sensor
#define RELAY_PIN 4    // Relay Module

// OBJECT INITIALIZATION 

MFRC522 mfrc522(SS_PIN, RST_PIN);   
LiquidCrystal_I2C lcd(0x27, 16, 2); 

// SYSTEM VARIABLES

bool isArmed = false; 
bool alarmTriggered = false; // To track if alarm is currently ringing

// THE MASTER KEY UID = (8E DA 6E 5)

byte masterTag[4] = {0x8E, 0xDA, 0x6E, 0x05};

void setup() {
  Serial.begin(9600);   
  SPI.begin();          
  mfrc522.PCD_Init();   
  
  lcd.init();
  lcd.backlight();

  // SETUP SENSOR PINS

  pinMode(IR_PIN, INPUT);
  pinMode(FLAME_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
  
  digitalWrite(RELAY_PIN, HIGH); 
  
  updateLCD();
  Serial.println("System Ready. Waiting for Master Key...");
}

void loop() {
  // PHASE 1 : SECURITY LOGIC (Only runs if ARMED)
  if (isArmed) {
    checkSensors();
  }

  // PHASE 2 : RFID KEYPAD LOGIC
  // Look for new cards
  if (!mfrc522.PICC_IsNewCardPresent()) return;
  if (!mfrc522.PICC_ReadCardSerial()) return;

  // Check Tag
  if (checkMasterTag(mfrc522.uid.uidByte)) {
    // TOGGLE ARM STATE
    isArmed = !isArmed; 
    
    // If we disarm, silence the alarm immediately
    if (!isArmed) {
      digitalWrite(RELAY_PIN, HIGH); // Turn Relay OFF
      alarmTriggered = false;
    }
    
    updateLCD();        
    delay(1000);        
  } else {
    denyAccess();
  }

  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
}

//Check Sensors
void checkSensors() {
  // Note: IR sensors usually send LOW when obstacle detected
  // Flame sensors usually send LOW when fire detected
  // You may need to change == LOW to == HIGH depending on your specific sensor calibration
  
  int irStatus = digitalRead(IR_PIN);
  int flameStatus = digitalRead(FLAME_PIN);

  if (irStatus == LOW || flameStatus == LOW) {
    triggerAlarm();
  }
}

//Trigger Alarm
void triggerAlarm() {
  // Only update screen/relay if we haven't already triggered to avoid screen flickering
  if (!alarmTriggered) {
    alarmTriggered = true;
    digitalWrite(RELAY_PIN, LOW); // Turn Relay ON (Active Low)
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("!!! ALERT !!!");
    lcd.setCursor(0, 1);
    lcd.print("BREACH DETECTED");
    
    Serial.println("!!! ALARM TRIGGERED !!!");
  }
}

// Compare the tag scanned to Master Tag by UID
boolean checkMasterTag(byte *scannedTag) {
  for (int i = 0; i < 4; i++) {
    if (scannedTag[i] != masterTag[i]) return false;
  }
  return true; 
}

// Show Access Denied message on the LCD display
void denyAccess() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("ACCESS DENIED!");
  
  Serial.println("!!! ACCESS DENIED !!!");
  
  delay(2000); 
  updateLCD(); 
}

// Update Main Status Screen on serial monitor
void updateLCD() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("System Status:");
  lcd.setCursor(0, 1);
  
  Serial.print("System Status: ");
  
  if (isArmed) {
    lcd.print(">> ARMED <<");
    Serial.println(">> ARMED <<");
  } else {
    lcd.print(">> DISARMED <<");
    Serial.println(">> DISARMED <<");
  }
}
