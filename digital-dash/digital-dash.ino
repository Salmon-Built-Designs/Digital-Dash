//////////////////////
// Digital Dash     // 
// David T          //
//////////////////////

// include the library code:
#include <LiquidCrystal.h>


const int ledCount = 14;    // the number of digital pin LEDs in the bar graph
int ledPins[] = { 
  41, 43, 45, 47, 49, 51, 53, 40, 42, 44, 46, 48, 50, 52 };   // an array of digital pin numbers to which LEDs are attached
int oldscreen = 0;
int screen = 0;
int sampleperiod = 500;
unsigned long sampleold = 0;
int logperiod = 1000;
unsigned long logold = 0;
int watertemp = 0;
int watertempmin = 0;
int watertempmax = 0;
int watertempmaxalarm = 95;
int oiltemp = 0;
int oiltempmin = 0;
int oiltempmax = 0;
int oiltempmaxalarm = 100;
int airtemp = 0;
int airtempmin = 0;
int airtempmax = 0;
int battvolt = 0;
int battvoltmin = 0;
int battvoltmax = 0;
int battvoltminalarm = 130;    // voltage *10 to avoid using float arithmetic 
int battvoltmaxalarm = 145;    // voltage *10 to avoid using float arithmetic 
int g = 0;
int gmin = 0;
int gmax = 0;
int rpm = 0;
volatile int rpmcount = 0;
int rpmmax = 0;
int rpmredline = 6000;
int alarmreason = 0;
boolean leftkeydown = false;
boolean rightkeydown = false;
unsigned long strobeledsold = 0;
int strobeledsperiod = 100;
boolean strobeleds = false;

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(36, 34, 32, 30, 28, 26);

void setup() {

// attachInterrupt(0, tachpulse, RISING);  
  
// loop over the pin array and set them all to output:
  for (int thisLed = 0; thisLed < ledCount; thisLed++) {
    pinMode(ledPins[thisLed], OUTPUT);
  }
  lcd.begin(16, 2);
  lcdstartup();        // display welcome message
  ledstartup();        // sweep leds
}

void loop() {
  
  // refresh parameters
  if (millis() > (sampleold + sampleperiod)); {
    //  readwatertemp();
    //  readoiltemp();
    //  readairtemp();
    readbatteryvolt();
    //  readaccelerometer();
    readrpm();
  }
  
  // log parameters
  if (millis() > (logold + logperiod)) {
    logtosdcard();
  }  

  // refresh screen
  if (screen == 0) {
    displayscreenhome();
  } 
  else if (screen == 1) {
    displayscreenwater();
  }
  else if (screen == 2) {
    displayscreenoil();
  }
  else if (screen == 3) {
    displayscreenair();
  }
  else if (screen == 4) {
    displayscreenbatt();
  }
  else if (screen == 5) {
    displayscreenaccel();
  }
  else if (screen == 6) {
    displayscreenrpm();
  }
  else if (screen == 7) {
    displayscreenalarm();
  }
  //refresh leds
  if (alarmreason != 0) {  // light all leds for alarm
    displayleds (65535);
  }  
  else {
    
    if (rpm > rpmredline) {  // strobe leds for redline rpm

      if ((strobeleds == false) && (millis() > (strobeledsold + strobeledsperiod))) {
        displayleds (0);
        strobeleds == true;
      }
      else if ((strobeleds == true) && (millis() > (strobeledsold + strobeledsperiod))) {
        displayleds (65535);
        strobeleds == false;
      }

    else {
      displayleds (rpm);
    }
    }
    
  }    
}  // end of main loop

void lcdstartup() {
  lcd.setCursor(0, 0);
  lcd.print("*  TIGER AVON  *");
  lcd.setCursor(0, 1);
  lcd.print("*  2.0 ZETEC   *");
return;
}

void ledstartup() {
  for (int thisLed = 0; thisLed < ledCount; thisLed++) {
    digitalWrite(ledPins[thisLed], HIGH);
    delay(30); 
  }
   for (int thisLed = 0; thisLed < ledCount; thisLed++) {
   digitalWrite(ledPins[thisLed], LOW);
   delay(30); 
  }
return;
}

void readbatteryvolt() {
  int battvalue = analogRead(A0);      // read the input on analoge pin 1
  battvolt = battvalue * (5 / 102.3);  // convert to a voltage (0-5V) multiplied by 10 (i.e. (0-50V)
  battvolt = battvolt * (47 / 22);     // multiply up by ratio of voltage divider resistors
  battvolt = battvolt + 3;             // add back in 0.3V voltage drop due to diode on 12V input
return;
}

void readrpm() {
  rpm = (((rpmcount*4)*60)/2);
  rpmcount = 0;  
return;
}

void logtosdcard() {
return;
}

void displayscreenhome() {
  char line0[17] = {"WT:      OT:    "};
  lcd.setCursor(0, 0);
  lcd.print(line0);
  char line1[17] = {"AT:      BV:    "};
  lcd.setCursor(0, 1);
  lcd.print(line1);
  lcd.setCursor(0, 12);
  lcd.print(battvolt);
return;
}

void displayscreenwater() {
return;
}

void displayscreenoil() {
return;
}

void displayscreenair() {
return;
}

void displayscreenbatt() {
return;
}

void displayscreenaccel() {
return;
}

void displayscreenrpm() {
return;
}

void displayscreenalarm() {
return;
}

void displayleds(int revs) {
return;
}

void tachpulse() {
rpmcount++;
}
