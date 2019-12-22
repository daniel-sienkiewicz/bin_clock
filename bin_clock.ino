/*
bin_clock.ino - Arduino project for Real-Time Clock

Version: 1.0.0
(c) 2019 Daaniel Sienkiewicz
www.sienkiewicz.ovh

This program is free software: you can redistribute it and/or modify
it under the terms of the version 3 GNU General Public License as
published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <Wire.h>
#include "DS1307.h"

DS1307 clock;
RTCDateTime dt;
int output[4][4];

void setup() {  
  Serial.begin(9600);

  // Initialize DS1307
  Serial.println("Initialize DS1307");;
  clock.begin();

  // If date not set
  if (!clock.isReady())
  {
    // Set sketch compiling time
    clock.setDateTime(__DATE__, __TIME__);
  }
}

void reset_output(){
  int i, j;

  for (i = 0; i < 4; i++)
    for (j = 0; j < 4; j++)
      output[i][j] = 0;
}

void print_output(){
  int i, j;

    for (i = 3; i >=0; i--){
      for (j = 0; j < 4; j++)
        Serial.print(output[i][j]);
      Serial.println();
    }
    Serial.println();
}

void write_to_led_min(int value){
  int dec, part;
  dec = value / 10;
  part = value % 10;

  if (dec == 1 || dec == 3 || dec == 5 || dec == 7|| dec == 9)
    output[0][2] = 1;

  if (dec == 2 || dec == 3 || dec == 6 || dec == 7)
    output[1][2] = 1;

  if (dec == 4 || dec == 5)
    output[2][2] = 1;

  if (part == 1 || part == 3 || part == 5 || part == 7|| part == 9)
    output[0][3] = 1;
 
  if (part == 2 || part == 3 || part == 6|| part == 7)
    output[1][3] = 1;

  if (part == 4  || part == 5|| part == 6|| part == 7)
    output[2][3] = 1;

  if (part == 8 || part == 9)
    output[3][3] = 1;
}

void write_to_led_h(int value){
  int dec, part;
  dec = value / 10;
  part = value % 10;

  if (dec == 1)
    output[0][0] = 1;
 
  if (dec == 2)
    output[1][0] = 1;

  if (part == 1 || part == 3 || part == 5 || part == 7|| part == 9)
    output[0][1] = 1;
 
  if (part == 2 || part == 3 || part == 6|| part == 7)
    output[1][1] = 1;

  if (part == 4  || part == 5|| part == 6|| part == 7)
    output[2][1] = 1;

  if (part == 8 || part == 9)
    output[3][1] = 1;
}

void print_time(){
  Serial.print("Raw data: ");
  Serial.print(dt.year);   Serial.print("-");
  Serial.print(dt.month);  Serial.print("-");
  Serial.print(dt.day);    Serial.print(" ");
  Serial.print(dt.hour);   Serial.print(":");
  Serial.print(dt.minute); Serial.print(":");
  Serial.print(dt.second); Serial.println("");
}

void loop() {
  int min, h, day, month;

  dt = clock.getDateTime();
  print_time();
  write_to_led_h(dt.hour);
  write_to_led_min(dt.minute);
  print_output();
  reset_output();
  delay(6000);
}
