#include <SPI.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <stdlib.h>

int temppin = 0 ;
Adafruit_SSD1306 display(4);
const int pin = 9 ;
const double dBAnalogQuiet = 10; 
const double dBAnalogModerate = 12;
const double dBAnalogLoud = 17;
float decibelsValueQuiet = 49.5;
float decibelsValueModerate = 65;
float decibelsValueLoud = 70;

void setup()
{
  pinMode(A0,INPUT) ;
  pinMode(A1,INPUT) ;
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(256, 0);
  pinMode(pin,OUTPUT) ;
}

int calcTemp(){
    float val = analogRead(A1);
    float mv = ( val/1024.0)*330; 
    float cel = mv/5;

    return cel ;
}

int calcDecibel(int val){
    float decibelsCalculated; 
    if(val<=13){
        decibelsCalculated = 20 * log10(val/dBAnalogQuiet);
        return decibelsCalculated + decibelsValueQuiet ;
    }
    if((val>13) && (val<=23)){
       decibelsCalculated = 20 * log10(val/dBAnalogModerate);
       return decibelsCalculated + decibelsValueModerate ;
    }
    if(val>23){
       decibelsCalculated = 20 * log10(val/dBAnalogLoud);
       return decibelsCalculated + decibelsValueLoud ;
    }
}

void loop() {
    char message[40] ;
    int val = analogRead(A0) ;
    Serial.println(val) ;
    val = calcDecibel(val) ;
    display.print("Sound in dB: ") ;
    sprintf(message,"%d",val) ;
    display.print(message);
    display.print(" dB\n");
    display.print("Temperature in C: ") ;
    sprintf(message,"%d",calcTemp()) ;
    display.print(message);
    display.print("C\n");
    display.display();
    delay(50) ;
    display.clearDisplay();
    display.setCursor(0,0);
}

