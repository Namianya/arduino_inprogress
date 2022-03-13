
#include "dht.h"

#define dht_apin A0
dht DHT;
float temp = 0.00;
float hum =0.00;
void setup() {
  // put your setup code here, to run once:


Serial.begin(9600);
  delay(500); //Delay to let system boot
  Serial.println("DHT11 Humidity & temperature Sensor\n\n");
}

void loop() {
  // put your main code here, to run repeatedly:
DHT.read11(dht_apin);
    hum = DHT.humidity;
    temp =DHT.temperature;
     Serial.print("Current humidity = ");
    Serial.print(hum);
    Serial.print("%  ");
    Serial.print("temperature = ");
    Serial.print(temp); 
    Serial.println("C  ");
    delay(4000);
    
}
