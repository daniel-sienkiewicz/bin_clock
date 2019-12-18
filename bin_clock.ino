#include <TimeLib.h>
#include <Wire.h>
#include <DS1307RTC.h>

int output[4][2];

void setup() {  
  Serial.begin(9600);
  setSyncProvider(RTC.get);   // the function to get the time from the RTC
  if(timeStatus()!= timeSet) 
     Serial.println("Unable to sync with the RTC");
  else
     Serial.println("RTC has set the system time");
}

void reset_output(){
  int i, j;

  for (i = 0; i < 4; i++)
    for (j = 0; j < 2; j++)
      output[i][j] = 0;
}

void print_output(){
  int i;

    for (i = 3; i >=0; i--){
      Serial.print(output[i][0]);
      Serial.println(output[i][1]);
    }
    Serial.println();
}

void get_time(int *month, int *day, int *h, int *min) {
  *month = 5;
  *day = 10;
  *h = 35;
  *min = 4;
}

void write_to_led(int value){
  int dec, part;
  dec = value / 10;
  part = value % 10;

  if (dec == 1 || dec == 3)
    output[0][0] = 1;
 
  if (dec == 2 || dec == 3)
    output[1][0] = 1;

  if (part == 1 || part == 3 || part == 5 || part == 7|| part == 9)
    output[0][1] = 1;
 
  if (part == 2 || part == 3|| part == 6|| part == 7)
    output[1][1] = 1;

  if (part == 4  || part == 5|| part == 6|| part == 7)
    output[2][1] = 1;

  if (part == 8 || part == 9)
    output[3][1] = 1;
 
}

void loop() {
  int min, h, day, month;
  get_time(&month, &day, &h, &min);

  write_to_led(h);
  Serial.println("Hours");
  print_output();

  reset_output();
  
  write_to_led(min);
  Serial.println("Min");
  print_output();
  
  if (timeStatus() == timeSet) {
    Serial.print(hour());
  } else {
    Serial.println("The time has not been set.");
  }
  delay(6000000);
}
