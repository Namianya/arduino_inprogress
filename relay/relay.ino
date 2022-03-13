int relay = 4;

void setup()
{
	pinMode(relay, OUTPUT);
	digitalWrite(relay, HIGH);
}

void loop()
{

	digitalWrite(relay, HIGH);
	delay(3000);
	digitalWrite(relay, LOW);
	delay(3000);
}
