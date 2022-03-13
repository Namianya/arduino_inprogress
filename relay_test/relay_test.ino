#define relay4 A2 //4th big fan
#define relay3 A3 //3rd small fan
#define relay1 3 //1st heater
#define relay2 4 //2nd water Heater
#define relay5 5 //2nd water Heater
void setup() {
  // put your setup code here, to run once:
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(relay4, OUTPUT);
  
  pinMode(relay5, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
// digitalWrite(relay5,LOW);
// delay(3000);
//  digitalWrite(relay5,HIGH);
//  delay(2000);
}
