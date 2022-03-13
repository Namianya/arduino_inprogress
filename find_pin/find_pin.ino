
#define MY_PIN 5 

void setup() {
 pinMode(MY_PIN, OUTPUT);

}

void loop() {
  digitalWrite(MY_PIN, LOW); 
  delay(1000);                       
//  digitalWrite(MY_PIN, HIGH); 
//  delay(1000); 
}
