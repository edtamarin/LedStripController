# LED strip controller

from machine import Pin, PWM, ADC, I2C
from time import sleep
import ssd1306

# RGB driver pins
pwmR = PWM(Pin(2))
pwmG = PWM(Pin(0))
pwmB = PWM(Pin(4))
# ADC setup, 0.0-3.6V range, 9 bit data
adc = ADC(Pin(32))
adc.atten(ADC.ATTN_11DB)
adc.width(ADC.WIDTH_10BIT)
# display
i2c = I2C(-1,Pin(22),Pin(21))
display = ssd1306.SSD1306_I2C(128, 32, i2c)
display.text("LED strip status:",0,0,1)
display.show()

print("LED controller online")
print(pwmR.freq())

mqttIntensity = 1023;

# set intensity received as MQTT command
def setMqttIntensity(newIntensity):
    mqttIntensity = newIntensity;
    return

def getPotIntensity():
    return int(adc.read())

def computeIntensity():
    pot = getPotIntensity()
    print("brightness: "+ str(int(pot*(mqttIntensity/1023))))
    return int(pot*(mqttIntensity/1023))
  
# set intensity of the red component
def setR(newR, newI):
    pwmR.duty(1023-int(newR*(newI/1023)))
    return
  
# set intensity of the red component
def setG(newG, newI):
    pwmG.duty(1023-int(newG*(newI/1023)))
    return

# set intensity of the red component
def setB(newB, newI):
    pwmB.duty(1023-int(newB*(newI/1023)))
    return

# update the display with the strip status
def updateDisplay(r,g,b,i):
    display.fill_rect(0, 8, 128, 32, 0)
    display.text("R: " + str(int(100*r/1023)) + "%",0,8,1)
    display.text("G: " + str(int(100*g/1023)) + "%",0,16,1)
    display.text("B: " + str(int(100*b/1023)) + "%",0,24,1)
    display.text("I: " + str(int(100*i/1023)) + "%",64,8,1)
    display.text("v 1.0",64,24,1)
    display.show()
    print("R:{0} G:{1} B:{2} I:{3}".format(r,g,b,i))
    return

# set RGB intensity overall
def setRGB(r,g,b,i):
    setR(r,i)
    setG(g,i)
    setB(b,i)
    updateDisplay(r,g,b,i)
    return

while True:
    stripIntensity = computeIntensity()
    setRGB(1023,0,0,stripIntensity)
    sleep(0.5)
    setRGB(0,1023,0,stripIntensity)
    sleep(0.5)
    setRGB(0,0,1023,stripIntensity)
    sleep(0.5)

    
