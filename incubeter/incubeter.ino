
#include "dht.h"
#include <OneWire.h> 
#include <DallasTemperature.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

#define OLED_RESET  4 

#define relay4 A2 //4th big fan
#define relay3 A3 //3rd small fan
#define relay1 5 //1st heater
#define relay2 3 //2nd water Heater
#define relay5 4 //power
#define  buzzer 2

#define ONE_WIRE_BUS A0  // DHT11 sensor pin

Adafruit_SSD1306 display(OLED_RESET);

dht DHT;
float temp = 0.00;
float hum =0.00;
unsigned long previousTimeTryTurn=0;
unsigned long trayDelay = 3000; // time taken between tray turning

byte trayState=LOW;
OneWire oneWire(ONE_WIRE_BUS); 
/********************************************************************/
// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

void setup() {
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(relay4, OUTPUT);
  
  pinMode(relay5, OUTPUT);
  pinMode(buzzer,OUTPUT);
  Serial.begin(9600);
  delay(500); //Delay to let system boot
  sensors.begin(); 
  Serial.println("DHT11 Humidity & temperature Sensor\n\n");
   
  delay(1000);  //Wait before accessing Sensor
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.clearDisplay();
  

}

void loop() {
  display.setTextSize(2);
  display.setTextColor(WHITE);
  digitalWrite(relay4,HIGH);
  digitalWrite(relay5,HIGH);
//  tray motion code
  unsigned long timeNow = millis();
  
  if(timeNow-previousTimeTryTurn>trayDelay){

    previousTimeTryTurn+=trayDelay;
    if(trayState == LOW){ 
      trayState == HIGH;
      }else{
        trayState == LOW;
        }
         digitalWrite(relay5,trayState);
         delay(5000);
         digitalWrite(relay2,trayState);
         delay(5000);
    }
    //  tray motion code end


    
  
//    DHT.read11(dht_apin);
//    hum = DHT.humidity;
    hum=00;
    sensors.requestTemperatures(); 
    temp =sensors.getTempCByIndex(0);
    delay(1000);
    display.setCursor(0,0);
    display.print("T- ");
    display.println(temp);
    display.print("H- ");
    display.println(hum);
    display.display();
    
    Serial.print("Current humidity = ");
    Serial.print(hum);
    Serial.print("%  ");
    Serial.print("temperature = ");
    Serial.print(temp); 
    Serial.println("C  ");
    
   
  if (temp <37.8){
    digitalWrite(relay1,LOW);
//    if (temp <35){
//    tone(buzzer, 1000);
// delay(500);
//noTone(buzzer);
// delay(500);
//tone(buzzer, 1000);
// delay(500);
// noTone(buzzer);
// }
  }
  else{
    digitalWrite(relay1,HIGH);
  }

  if (temp >41||hum>65){
    digitalWrite(relay3,LOW);
    
    digitalWrite(relay1,HIGH);
  }
  
  else{
    digitalWrite(relay3,HIGH);
  }

  
  if (temp >37){
    digitalWrite(relay1,HIGH);
    
//    digitalWrite(relay4,LOW);
  }
  
  else{
    digitalWrite(relay1,HIGH);
  }
  

  if (hum < 67.00){
    digitalWrite(relay2,LOW);
// if (hum <60){
//    tone(buzzer, 2000);
// delay(500);
//noTone(buzzer);
// delay(500);
//tone(buzzer, 2000);
// delay(500);
// noTone(buzzer);
// }
  }
  else{
   digitalWrite(relay2,HIGH);
   
  }
  delay(1000);
  display.clearDisplay();
}


  
