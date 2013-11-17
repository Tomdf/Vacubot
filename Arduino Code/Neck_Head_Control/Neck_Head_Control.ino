/* SparkFun WS2812 Breakout Board Example
 SparkFun Electronics
 date: July 25, 2013
 license: GNU GENERAL PUBLIC LICENSE
 
 Requires the Adafruit NeoPixel library. It's awesome, go get it.
 https://github.com/adafruit/Adafruit_NeoPixel
 
 This simple example code runs three sets of animations on a group of WS2812
 breakout boards. The more boards you link up, the better these animations
 will look. 
 
 For help linking WS2812 breakouts, checkout our hookup guide:
 https://learn.sparkfun.com/tutorials/ws2812-breakout-hookup-guide
 
 Before uploading the code, make sure you adjust the two defines at the
 top of this sketch: PIN and LED_COUNT. Pin should be the Arduino pin
 you've got connected to the first pixel's DIN pin. By default it's
 set to Arduino pin 4. LED_COUNT should be the number of breakout boards
 you have linked up.
 */
#include <Adafruit_NeoPixel.h>
#include "WS2812_Definitions.h"

#define PIN 10
#define LED_COUNT 1

// Create an instance of the Adafruit_NeoPixel class called "leds".
// That'll be what we refer to from here on...
Adafruit_NeoPixel leds = Adafruit_NeoPixel(LED_COUNT, PIN, NEO_GRB + NEO_KHZ800);

#include <Servo.h> 

Servo myservo;  // create servo object to control a servo 
// a maximum of eight servo objects can be created 

int pos = 0;    // variable to store the servo position 
int color;
int testColor = 0; // testing numbers fer fun and knowledge

void setup()
{
  Serial.begin(9600);
  leds.begin();  // Call this to start up the LED strip.
  clearLEDs();   // This function, defined below, turns all LEDs off...
  color = 0;
  setColor(color,1);
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
}

void loop()
{
  testColor += 1;
  Serial.println(testColor,BIN);
  for(pos = 50; pos < 140; pos += 1)  // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15); 
    color += 1;
    setColor(color,1);    // waits 15ms for the servo to reach the position 
    
  } 
  for(pos = 140; pos>=50; pos-=1)     // goes from 180 degrees to 0 degrees 
  {                                
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
    if (color > 0){
      color -= 1;
    }
    setColor(color,1);    // waits 15ms for the servo to reach the position 
    ;
  }
}

void setColor(unsigned long color, byte brightness)
{
  byte red = (color & 0xFF0000) >> 16;
  byte green = (color & 0x00FF00) >> 8;
  byte blue = (color & 0x0000FF);

  for (int i=0; i<=LED_COUNT-1; i++)
  {
    leds.setPixelColor(i, red/brightness, green/brightness, blue/brightness);
  }
  leds.show();  // Turn the LEDs on
}

// Sets all LEDs to off, but DOES NOT update the display;
// call leds.show() to actually turn them off after this.
void clearLEDs()
{
  for (int i=0; i<LED_COUNT; i++)
  {
    leds.setPixelColor(i, 0);
  }
}




