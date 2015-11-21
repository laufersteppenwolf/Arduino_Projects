
/*
 * Copyright (c) 2015 laufersteppenwolf@xda <laufersteppenwolf@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA  02110-1301, USA.
 */

const int red = 9;
const int green = 6;
const int blue = 5;
const int switchRed = 2;
const int switchGreen = 3;
const int switchBlue = 4;

boolean switchRedActive;
boolean switchGreenActive;
boolean switchBlueActive;

boolean redOn;
boolean greenOn;
boolean blueOn;

void setup()  {
  Serial.begin(9600); 
  pinMode(switchRed, INPUT_PULLUP);
  pinMode(switchGreen, INPUT_PULLUP);
  pinMode(switchBlue, INPUT_PULLUP);

  fadeOn(red);
} 

void loop()  { 
  switchRedActive = digitalRead(switchRed);
  switchGreenActive = digitalRead(switchGreen);
  switchBlueActive = digitalRead(switchBlue);
  
  Serial.print("Switch Red: ");
  Serial.println(switchRedActive);
  Serial.print("Switch Green: ");
  Serial.println(switchGreenActive);
  Serial.print("Switch Blue: ");
  Serial.println(switchBlueActive);
  
  // If no color is requested cycle them through
  if (!switchRedActive &&
      !switchGreenActive &&
      !switchBlueActive) {
        autoFadeRGB();
  } else {
  
    if (switchRedActive && !redOn) {
      fadeOn(red);
      redOn = true;
    } else if (!switchRedActive && redOn){
      fadeOff(red);
      redOn = false;
    }
  
    if (switchGreenActive && !greenOn) {
      fadeOn(green);
      greenOn = true;
    } else if (!switchGreenActive && greenOn) {
      fadeOff(green);
      greenOn = false;
    }
  
    if (switchBlueActive && !blueOn) {
      fadeOn(blue);
      blueOn = true;
    } else if (!switchBlueActive && blueOn) {
      fadeOff(blue);
      blueOn = false;
    }
  }

}

void autoFadeRGB() {
  fadeOnOff(green, red);
  fadeOnOff(blue, green);
  fadeOnOff(red, blue);
  delay(60);
}

void fadeOn(int pin) {
  for(int fadeValue = 255 ; fadeValue >= 0; fadeValue -=5) { 
    analogWrite(pin, fadeValue);         
    delay(30);                            
  }
  
  if (pin == red)
    redOn = true;
  if (pin == green)
    greenOn = true;
  if (pin == blue)
    blueOn = true;
}

void fadeOff(int pin) {
  for(int fadeValue = 0 ; fadeValue <= 255; fadeValue +=5) { 
    analogWrite(pin, fadeValue);         
    delay(30);                            
  }
  
  if (pin == red)
    redOn = false;
  if (pin == green)
    greenOn = false;
  if (pin == blue)
    blueOn = false;
}

void fadeOnOff(int on, int off) {
    for(int fadeValue = 255 ; fadeValue >= 0; fadeValue -=5) { 
    if (on == red && fadeValue >= 5) {
      analogWrite(on, fadeValue - 5);
    } else {
      analogWrite(on, fadeValue);
    }
    
    if (off == red && fadeValue == 250) {
      analogWrite(off, 250 - fadeValue);
    } else {
      analogWrite(off, 255 - fadeValue);
    }
    delay(30);                            
  }
  
  if (on == red)
    redOn = true;
  if (on == green)
    greenOn = true;
  if (on == blue)
    blueOn = true;
    
  if (off == red)
    redOn = false;
  if (off == green)
    greenOn = false;
  if (off == blue)
    blueOn = false;
}
