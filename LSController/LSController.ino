/*
 * LED strip controller
 * 19 Sep 2018
 * Author: Egor Tamarin
 */

// pin definitions
int dimmer = A0;
int PWM_Color[3] = {1,2,3};
int colorValues[3] = {0,0,0};
int brightnessScaler = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  // pot value determines brightness
  brightnessScaler = getDimmerValue();
}

// get the value from the potentiometer
int getDimmerValue(){
  int dimmerVal = analogRead(dimmer);
  Serial.println(dimmerVal);
  return dimmerVal;
}

// adjust the color input to match PWM range
// and global brightness setting
int scaleColor(int intensity){
  // scale 8-bit color input to PWM range
  int scaledColor = map(intensity,0,255,0,1024);
  // globally scale the value with the dimmer
  int bnessScaledColor = scaledColor * brightnessScaler/1024;
  return bnessScaledColor;
}

// set a single color
// types: 1-red, 2-green, 3-blue
// intensity from 0 to 255
void setColor(int type, int intensity){
  int cIntensity = scaleColor(intensity);
  analogWrite(type,cIntensity);
}

// set all three colors at the same time
void setRGB(int r,int g, int b){
  setColor(1,r);
  setColor(2,g);
  setColor(3,b);
}
