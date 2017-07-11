/*
 * This is the code for an electronic STROBOSCOPE
 */

#include <LCD5110_Basic.h>

int down = 2;
int up = 3;
int down2 = 4;
int up2 = 5; 
int led = 13;

float freq = 100; 
float period = 1000 / freq; // This is the period in milliseconds
float rate = 1;

LCD5110 myGLCD(8,9,10,11,12);
extern uint8_t SmallFont[];
extern uint8_t MediumNumbers[];
extern uint8_t BigNumbers[];
extern uint8_t arduino_logo[];


void setup() {

  // Setup

  pinMode(led, OUTPUT);
  pinMode(up, INPUT);
  pinMode(down2, INPUT);
  pinMode(up2, INPUT);
  digitalWrite(led, LOW);
  Serial.begin(9600);
  myGLCD.InitLCD();
  
  // Intro
  
  myGLCD.drawBitmap(0, 0, arduino_logo, 84, 48);
  delay(2000);
  myGLCD.clrScr();
  myGLCD.setFont(SmallFont);
  myGLCD.print("ARDUINO", CENTER, 16);
  myGLCD.print("STROBOSCOPE", CENTER, 24);
  delay(2000);
  myGLCD.clrScr();
  myGLCD.print("DESIGNED", CENTER, 0);
  myGLCD.print("AND", CENTER, 8);
  myGLCD.print("MADE", CENTER, 16);
  myGLCD.print("BY", CENTER, 32);
  delay(2000);
  myGLCD.clrScr();
  myGLCD.print("AHMET AKIF", CENTER, 16);
  myGLCD.print("KAYA", CENTER, 24);
  delay(2000);
  myGLCD.clrScr();
  myGLCD.print("VERSION", CENTER, 0);
  myGLCD.setFont(BigNumbers);
  myGLCD.printNumF(1, 2, CENTER, 16);
  delay(2000);
  myGLCD.clrScr();
}

void loop() {

  period = 1000 / freq;

  if (digitalRead(up) == HIGH and digitalRead(up2) == HIGH) {
    Serial.println("Rate multiplyed by 2");
    myGLCD.setFont(SmallFont);
    myGLCD.print("x2", LEFT, 32);
    rate = rate * 2;
  }
  else if (digitalRead(down2) == HIGH and digitalRead(down) == HIGH) {
    Serial.println("Rate divided by 2");
    myGLCD.setFont(SmallFont);
    myGLCD.print("/2", LEFT, 32);
    rate = rate / 2;
  }
  else if (digitalRead(up) == HIGH) {
    freq = freq + 1;
  }
  else if (digitalRead(down) == HIGH) {
    freq = freq - 1;
  }
  else if (digitalRead(up2) == HIGH) {
    Serial.println("Frequency divided by 2");
    myGLCD.setFont(SmallFont);
    myGLCD.print("/2", LEFT, 8);
    freq = freq / 2;
  }
  else if (digitalRead(down2) == HIGH) {
    Serial.println("Frequency multiplyed by 2");
    myGLCD.setFont(SmallFont);
    myGLCD.print("x2", LEFT, 8);
    freq = freq * 2;
  }

  if (period < 0) {
    period = 0;
  }

  period = 1000 / freq;

  Serial.println("======================");
  Serial.print("Period =  ");
  Serial.print(period);
  Serial.println(" ms");
  
  Serial.println("----------------------");
  Serial.print("Frequancy =  ");
  Serial.print(freq);
  Serial.println(" Hz");

  myGLCD.setFont(SmallFont);
  myGLCD.print("Freq(Hz)=  ", LEFT, 0);
  myGLCD.setFont(MediumNumbers);
  myGLCD.printNumF(freq, 2, CENTER, 8);

  Serial.println("----------------------");
  Serial.print("Rate (on time divided by of time) = ");
  Serial.println(rate);
  Serial.println("======================");

  myGLCD.setFont(SmallFont);
  myGLCD.print("Rate(on/off)=  ", LEFT, 24);
  myGLCD.setFont(MediumNumbers);
  myGLCD.printNumF(rate, 2, CENTER, 32);
  
  digitalWrite(led, HIGH);
  delay(period * rate);
  digitalWrite(led, LOW);
  delay(period);
}
