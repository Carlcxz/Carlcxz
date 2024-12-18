#include <virtuabotixRTC.h>
#include <LiquidCrystal_I2C.h>
#include <MFRC522.h> 
#include <Servo.h>
#include <EEPROM.h>

#define I2C_ADDR 0x27 //LCD i2c stuff
#define BACKLIGHT_PIN 3
#define En_pin 2
#define Rw_pin 1
#define Rs_pin 0
#define D4_pin 4
#define D5_pin 5
#define D6_pin 6
#define D7_pin 7

#define RST_PIN 9
#define SS_PIN 10

LiquidCrystal_I2C lcd(I2C_ADDR, 16, 2); // Assuming you have a 16x2 LCD
virtuabotixRTC myRTC(6, 7, 8); 
MFRC522 rfid(SS_PIN, RST_PIN); 

Servo key1;
Servo key2;
Servo key3;
Servo key4;
Servo door1;
Servo door2;

int keyPins[] = {2, 3, 4, 5}; 
int doorPins[] = {A2, A3}; 

byte superAdminUID[] = {0xDE, 0x96, 0x37, 0x03}; 
byte teacherUID[] = {0x3D, 0x27, 0xBB, 0x02}; 

const int SCHEDULE_START_ADDR = 0; 
const int SCHEDULE_SIZE = 7; // 7 days in a week

byte teacherSchedule[SCHEDULE_SIZE]; 


void setup() {
  Serial.begin(9600);
  SPI.begin(); 
  rfid.PCD_Init(); 

  lcd.begin (16,2); 
  lcd.setBacklight(true); 
  lcd.setBacklight(HIGH);
  lcd.home ();
  myRTC.setDS1302Time(13, 30, 0, 0, 19, 12, 2024); 

  key1.attach(keyPins[0]);
  key2.attach(keyPins[1]);
  key3.attach(keyPins[2]);
  key4.attach(keyPins[3]);
  door1.attach(doorPins[0]);
  door2.attach(doorPins[1]);

  for (int i = 0; i < SCHEDULE_SIZE; i++) {
    teacherSchedule[i] = 0; // Initialize all days to off (0)
  }
  teacherSchedule[1] = 0; // Monday (off)
  teacherSchedule[2] = 1; // Tuesday (on)
  teacherSchedule[3] = 0; // Wednesday (off)
  teacherSchedule[4] = 1; // Thursday (on)
  teacherSchedule[5] = 0; // Friday (off)
  teacherSchedule[6] = 1; // Saturday (on)

  // Write initial schedule to EEPROM
  writeTeacherScheduleToEEPROM(); 

  lockAll(); 
}

void loop() {
  lcd.clear(); 
  myRTC.updateTime();
  lcd.setCursor(0,0);
  lcd.print(myRTC.dayofmonth);
  lcd.print("/");
  lcd.print(myRTC.month);
  lcd.print("/");
  lcd.print(myRTC.year);
  lcd.setCursor(0,1);
  lcd.print(myRTC.hours);
  lcd.print(":");
  lcd.print(myRTC.minutes);
  lcd.print(":");
  lcd.print(myRTC.seconds);

  if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
    lcd.clear();
    lcd.print("Card Scanned");

    if (checkUID(rfid.uid.uidByte, superAdminUID)) {
      lcd.setCursor(0, 1);
      lcd.print("Admin Access");
      superAdminControl();
    } else if (checkUID(rfid.uid.uidByte, teacherUID) && checkTeacherSchedule()) { 
      lcd.setCursor(0, 1);
      lcd.print("Teacher Access");
      teacherControl();
    } else {
      lcd.setCursor(0, 1);
      lcd.print("Access Denied");
    }
    delay(2000);
    lcd.clear();
    lcd.print("System Ready");
    rfid.PICC_HaltA();
  }

  delay(1000); 
}

void lockAll() {
  key1.write(0);
  key2.write(0);
  key3.write(0);
  key4.write(0);
  door1.write(0);
  door2.write(0);
}

void superAdminControl() {
  Serial.println("Super Admin Access Granted");
  key1.write(180); 
  key2.write(180); 
  key3.write(180); 
  key4.write(180); 
  door1.write(180); 
  door2.write(180); 
  delay(5000);
  lockAll(); 
}

void teacherControl() {
  Serial.println("Teacher Access Granted");
  door1.write(180); 
  door2.write(180); 
  delay(5000);
  door1.write(0); 
  door2.write(0); 
}

bool checkUID(byte *cardUID, byte *validUID) {
  for (byte i = 0; i < 4; i++) {
    if (cardUID[i] != validUID[i]) return false;
  }
  return true;
}

bool checkTeacherSchedule() {
  int currentDay = myRTC.dayofweek; 
  Serial.print("Current day: ");
  Serial.println(currentDay);

  for (int i = 0; i < sizeof(teacherSchedule) / sizeof(teacherSchedule[0]); i++) {
    Serial.print("Schedule for day ");
    Serial.print(i);
    Serial.print(": ");
    Serial.println(teacherSchedule[i]);
    if (currentDay == teacherSchedule[i]) {
      return true;
    }
  }
  return false;
}
void writeTeacherScheduleToEEPROM() {
  for (int i = 0; i < SCHEDULE_SIZE; i++) {
    EEPROM.write(SCHEDULE_START_ADDR + i, teacherSchedule[i]);
  }
}

void loadTeacherSchedule() {
  for (int i = 0; i < SCHEDULE_SIZE; i++) {
    teacherSchedule[i] = EEPROM.read(SCHEDULE_START_ADDR + i);
  }
}