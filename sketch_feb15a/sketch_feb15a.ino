#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
#include <Servo.h>
Servo myservo1;
#define ir1 4 // IR Sensor 1
#define ir2 7 // IR Sensor 2
int Slot = 4; // Enter Total number of parking Slots
int flag1 = 0;
int flag2 = 0;
void setup()
{
  lcd.begin();
  lcd.backlight();
  pinMode(ir1, INPUT);
  pinMode(ir2, INPUT);
  myservo1.attach(9);
  myservo1.write(100);
  lcd.setCursor(0, 0);
  lcd.print("   ARDUINO  ");
  lcd.setCursor(0, 1);
  lcd.print(" PARKING SYSTEM ");
  delay(2000);
  lcd.clear();
}
void loop()
{
  if (digitalRead(ir1) == LOW && flag1 == 0)
  {
    if (Slot > 0)
    {
      flag1 = 1;
      if (flag2 == 0)
      {
        myservo1.write(0);
        Slot = Slot - 1;
      }
    }
    else
    {
      lcd.setCursor(0, 0);
      lcd.print("  SORRY 🙁  ");
      lcd.setCursor(0, 1);
      lcd.print(" Parking Full ");
      delay(3000);
      lcd.clear();
    }
  }
  if (digitalRead(ir2) == LOW && flag2 == 0)
  {
    flag2 = 1;
    if (flag1 == 0)
    {
      myservo1.write(0);
      Slot = Slot + 1;
    }
  }
  if (flag1 == 1 && flag2 == 1)
  {
    delay(1000);
    myservo1.write(100);
    flag1 = 0, flag2 = 0;
  }
  lcd.setCursor(0, 0);
  lcd.print("  WELCOME!  ");
  lcd.setCursor(0, 1);
  lcd.print("Slot Left: ");
  lcd.print(Slot);
}
