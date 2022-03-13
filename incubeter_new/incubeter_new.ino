
#include "dht.h"
#include <OneWire.h>
#include <EEPROM.h>
#include <DallasTemperature.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128	// OLED display width, in pixels
#define SCREEN_HEIGHT 64	// OLED display height, in pixels
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
#include <Keypad.h>

#define OLED_RESET 4

#define small_fan A2	// small fan
#define air_heater 5	// 1st heater
#define water_heater A3 // water Heater
#define relay5 4		// power
#define relay6 3		// power
#define buzzer 2

// keypad
#define c1 6
#define c2 7
#define c3 8
#define r1 9
#define r2 10
#define r3 11
#define r4 12

#define ONE_WIRE_BUS A0 // temp sensor pin
#define dht_apin A1

Adafruit_SSD1306 display(OLED_RESET);

dht DHT;
float temp = 0.00;
float hum = 0.00;
unsigned long previousTimeTryTurn = 0;
unsigned long trayDelay = 3000; // time taken between tray turning

byte trayState = LOW;
OneWire oneWire(ONE_WIRE_BUS);
/********************************************************************/
// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);
unsigned long prevTime = millis();
unsigned long trayPrevTime = millis();
long main_interval = 2000;

// keypad code ##################################################
//  Constants for row and column sizes
const byte ROWS = 4;
const byte COLS = 3;

// Array to represent keys on keypad
char hexaKeys[ROWS][COLS] = {
	{
		'1',
		'2',
		'3',
	},
	{
		'4',
		'5',
		'6',
	},
	{
		'7',
		'8',
		'9',
	},
	{
		'*',
		'0',
		'#',
	},
};

// Connections to Arduino
byte rowPins[ROWS] = {
	r4,
	r3,
	r2,
	r1,
};
byte colPins[COLS] = {
	c3,
	c2,
	c1,
};

// Create keypad object
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);
// #################################################

uint8_t normalTempAddress = 130;
uint8_t normalHumAddress = 131;
float normTemp = EEPROM.read(normalTempAddress);
int normalHum = EEPROM.read(normalHumAddress);


void setup()
{
	pinMode(air_heater, OUTPUT);
	pinMode(water_heater, OUTPUT);
	pinMode(small_fan, OUTPUT);

	pinMode(relay5, OUTPUT);
	pinMode(buzzer, OUTPUT);
	Serial.begin(9600);
	delay(500); // Delay to let system boot
	sensors.begin();
	Serial.println("DHT11 Humidity & temperature Sensor\n\n");

	delay(1000); // Wait before accessing Sensor
	display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
	display.clearDisplay();
}

void loop()
{
	unsigned long currentTime = millis();
	display.setTextSize(2);
	display.setTextColor(WHITE);
	digitalWrite(relay5, HIGH);
	//  tray motion code

	if (currentTime - prevTime > 3000)
	{

		mainApp();
		prevTime = currentTime;
	}

	if (currentTime - trayPrevTime > 30000)
	{

		Serial.println("tray turning\n\n");
		trayOpen();
		trayPrevTime = currentTime;
	}

	char customKey = customKeypad.getKey();

	keyPadCode(customKey);

	display.clearDisplay();
}

void keyPadCode(char customKey){
	if (customKey)
	{
		// Print key value to serial monitor
		Serial.println(customKey);
		//    ###########################################################

		if (customKey == '*')
		{
			EEPROM.write(normalTempAddress, 37.0);
			EEPROM.write(normalHumAddress, 65);
			delay(100);
			display.clearDisplay();
			display.setCursor(0, 0);
			display.println("Reseting");
			display.display();
			delay(2000);
		}
		else if (customKey == '#')
		{
			EEPROM.write(normalTempAddress, 37.0);
			EEPROM.write(normalHumAddress, 70);
			delay(100);
			display.clearDisplay();
			display.setCursor(0, 0);
			display.println("Hatchery");
			display.display();
			delay(2000);
		}

		else if (customKey == '5')
		{
			// turn off the tray
			// digitalWrite(small_fan, LOW);
			display.clearDisplay();
			display.setCursor(0, 0);
			display.println("Turning");
			display.display();
			delay(20000);
		}
		else if (customKey == '6')
		{
			EEPROM.write(normalHumAddress, normalHum+1);
			delay(100);
			display.clearDisplay();
			display.setCursor(0, 0);
			display.println("H + 1");
			display.display();
			delay(2000);
		}

		else if (customKey == '4')
		{
			EEPROM.write(normalHumAddress, normalHum-1);
			delay(100);
			display.clearDisplay();
			display.setCursor(0, 0);
			display.println("H - 1");
			display.println(normalHum - 1);
			display.display();
			delay(20000);
		}
		else if (customKey == '9')
		{
			EEPROM.write(normalTempAddress, normTemp + 1);
			delay(100);
			display.clearDisplay();
			display.setCursor(0, 0);
			display.println("T + 1");
			display.display();
			delay(2000);
		}
		else if (customKey == '7')
		{
			EEPROM.write(normalTempAddress, normTemp - 1);
			delay(100);
			display.clearDisplay();
			display.setCursor(0, 0);
			display.println("T - 1");
			display.display();
			delay(2000);
		}
		
		else{
			// turn on the tray
			// digitalWrite(small_fan, HIGH);
			display.clearDisplay();
			display.setCursor(0, 0);
			display.println("Not Mapped");
			display.display();
			delay(1000);
		}
		delay(2000);
	}
}

void mainApp()
{

	DHT.read11(dht_apin);
	hum = DHT.humidity;
	sensors.requestTemperatures();
	temp = sensors.getTempCByIndex(0);
	delay(1000);
	display.setCursor(0, 0);
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

	if (temp < normTemp - 0.1)
	{
		digitalWrite(air_heater, LOW);

		//    if (temp <35){
		//    tone(buzzer, 1000);
		// delay(500);
		// noTone(buzzer);
		// }
	}
	else
	{
		digitalWrite(air_heater, HIGH);
	}

	if (temp > normTemp + 0.2 || hum > normalHum)
	{
		digitalWrite(small_fan, LOW);

		digitalWrite(air_heater, HIGH);
	}

	else
	{
		digitalWrite(small_fan, HIGH);
	}

	if (hum < normalHum)
	{
		digitalWrite(water_heater, LOW);
		// if (hum <normalHum-7){
		//    tone(buzzer, 2000);
		// delay(500);
		// noTone(buzzer);
		// }
	}
	else
	{
		digitalWrite(water_heater, HIGH);
	}
	delay(1000);
}


void trayOpen(){
	Serial.println("tray turning\n\n");
	digitalWrite(relay5, HIGH);
	digitalWrite(relay6, LOW);

	delay(1000);
}

void trayClose(){
	Serial.println("tray turning\n\n");
	digitalWrite(relay5, LOW);
	digitalWrite(relay6, HIGH);

	delay(1000);
}