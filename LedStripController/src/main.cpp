/*
 * LED strip controller
 * 19 Sep 2018
 * Author: Egor Tamarin
 */

#include <Arduino.h>

// function declarations
int getDimmerValue();
int scaleColor(int intensity);
void setRGB(int r,int g, int b);
void setColor(int type, int intensity);
void setRGB(int r,int g, int b);

// pin definitions
int dimmer = A0;
int PWM_Color[3] = {D1,D2,D3};
int colorValues[3] = {0,0,0};
int brightnessScaler = 0;

void setup() {
  for (int i=0;i<3;i++){
    pinMode(PWM_Color[i],OUTPUT);
  }
  Serial.begin(9600);
}

void loop() {
  // pot value determines brightness
  brightnessScaler = getDimmerValue();
  //setRGB(255,0,0);
  analogWrite(D1,255);
  analogWrite(D2,0);
  analogWrite(D3,0);
  Serial.println("Red");
  delay(100);
  /*
  setRGB(0,255,0);
  Serial.println("Green");
  delay(100); 
  setRGB(0,0,255);
  Serial.println("Blue");
  delay(100); 
  */
}

// get the value from the potentiometer'
int getDimmerValue(){
  int dimmerVal = analogRead(dimmer);
  Serial.println(dimmerVal);
  return dimmerVal;
}

// adjust the color input to match PWM range
// and global brightness setting
int scaleColor(int intensity){
  // scale 8-bit color input to PWM range
  //int scaledColor = map(intensity,0,255,0,1024);
  // globally scale the value with the dimmer
  int bnessScaledColor = intensity * brightnessScaler/1024;
  return bnessScaledColor;
}

// set a single color
// types: 0-red, 1-green, 2-blue
// intensity from 0 to 255
void setColor(int type, int intensity){
  int cIntensity = scaleColor(intensity);
  analogWrite(PWM_Color[type],cIntensity);
}

// set all three colors at the same time
void setRGB(int r,int g, int b){
  setColor(0,r);
  setColor(1,g);
  setColor(2,b);
}