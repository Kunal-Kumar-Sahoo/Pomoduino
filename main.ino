/*
	Author: Kunal Kumar Sahoo
    Project: Pomodoro clock
    Date: 22nd January 2022
*/

#include <LiquidCrystal.h>

// Pin declarations:
const int led = 8;
const int buzz = 13;
const int button = 11;
const int lcd_rs = 10, lcd_e = 9;
const int lcd_pins[4] = {7, 6, 5, 4};

const int workTime = 25 * 60;
const int breakTime = 5 * 60;
bool workSession;

LiquidCrystal lcd(lcd_rs, lcd_e, lcd_pins[0], lcd_pins[1], lcd_pins[2], lcd_pins[3]);

void setup() {
	pinMode(led, OUTPUT);
  	pinMode(buzz, OUTPUT);
  	pinMode(button, INPUT_PULLUP);
   	
  	printLCD("POMODORO CLOCK", 2000);
  	workSession = false;
	alert(1000);
  	toggle();
}

void loop() {
  	if(workSession) {
      	digitalWrite(button, LOW);
      	printLCD("WORK SESSION", 2000);
      
      	for(int i = workTime; i >= 0; i--) {
      		printLCD(getTime(i), 1000);
        }
      	
      	alert(1000);
      	printLCD("TIME'S UP", 2000);	
  	}
  	if(!workSession) {
    	digitalWrite(button, LOW);
      	printLCD("BREAK SESSION", 2000);
      	
      	for(int i = breakTime; i >= 0; i--)
          	printLCD(getTime(i), 1000);
      
      	alert(1000);
      	printLCD("BACK TO WORK", 2000);
      	alert(1000);
    }
  	toggle();
}

void printLCD(String s, int microsecs) {
	lcd.begin(16,2);
  	lcd.setCursor(0,0);
  	lcd.print(s);
  	delay(microsecs);
  	lcd.clear();
}

String getTime(int seconds) {
  	return String(seconds/60) + ":" + String(seconds%60);
}

void alert(int microsecond) {
	digitalWrite(buzz, HIGH);
  	digitalWrite(led, HIGH);
  	delay(microsecond);
  	digitalWrite(buzz, LOW);
  	digitalWrite(led, LOW);
}

void toggle() {
  	printLCD("Press Button", 1000);
  	while(true) {
  		if(digitalRead(button) == HIGH){
      		workSession = !workSession;
      		break;
    	}
      	else continue;
    }
}
