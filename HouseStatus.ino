
/*
  LiquidCrystal Library -  House Status

  Uses the LCD with 5 buttons to toggle a list of tentants at a uni house so
  others can see if they are in. Using buttons are toggles

  The circuit:
 * LCD RS pin to digital pin 7
 * LCD Enable pin to digital pin 8
 * LCD D4 pin to digital pin 9
 * LCD D5 pin to digital pin 10
 * LCD D6 pin to digital pin 11
 * LCD D7 pin to digital pin 12
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * 5 buttons
 * Button1 pin to digital 6
 * Button2 pin to digital 5
 * Button3 pin to digital 4
 * Button4 pin to digital 3
 * Button5 pin to digital 2
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
 
 OliverDevsCode
 */

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
int buttonApin = 6;
int buttonBpin = 5;
int buttonCpin = 4;
int buttonDpin = 3;
int buttonEpin = 2;

String tenants[5]= {"OliverDevsCode","Person 2","Person 3","Person 4","Person 5"};
bool tenantStatus[5] = {false,false,false,false,false};
String displayText = String("");
String bufferText = String("");

//button variables
unsigned long timeNow = 0;
unsigned long timePrev = 0;
unsigned int timeWait = 500;

//display variables
namespace display {
  unsigned long timeNow = 0;
  unsigned long timePrev = 0;
  unsigned int timeWait = 50;
  int start = 0;
  int end = 15;
}

String tenantString(){
  String output = String("");
  for(int i = 0; i < 5; i ++){
    String name = tenants[i];
    bool present = tenantStatus[i];
    output += "  " + name + " is ";
    if(present){
      output += " home |";
    }else{
      output += " out |";
    }
  }
  output += "     ";
  return output;
};

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  pinMode(buttonApin, INPUT_PULLUP);  
  pinMode(buttonBpin, INPUT_PULLUP);  
  pinMode(buttonCpin, INPUT_PULLUP);  
  pinMode(buttonDpin, INPUT_PULLUP);  
  pinMode(buttonEpin, INPUT_PULLUP);  
  displayText = tenantString();
  bufferText = displayText.substring(display::start,display::end);
}

void loop() {
  // set the cursor to column 0, line 1
  lcd.setCursor(0, 0);
  
  //tickertape style
  display::timeNow = millis();
  if(display::timeNow % display::timeWait == 0){
    bufferText = displayText.substring(display::start,display::end);
    display::start ++;
    if(display::start >= displayText.length()){
      display::start = 0;
      display::end = 15;
    }
    display::end ++;
    if(display::end >= displayText.length()){
      display::end = displayText.length()-1;
    }
  }

  lcd.print(bufferText);

  if (digitalRead(buttonApin) == LOW)
  {
    timeNow = millis();
    if (timeNow-timePrev >= timeWait )    
    {   
      timePrev = timeNow;   
      tenantStatus[0] = !tenantStatus[0];
      displayText = tenantString();
    }
  }
  else if (digitalRead(buttonBpin) == LOW)
  {
    timeNow = millis();
    if (timeNow-timePrev >= timeWait )    
    {   
      timePrev = timeNow;   
      tenantStatus[1] = !tenantStatus[1];
      displayText = tenantString();
    }
  }
  else if (digitalRead(buttonCpin) == LOW)
  {
    timeNow = millis();
    if (timeNow-timePrev >= timeWait )    
    {   
      timePrev = timeNow;   
      tenantStatus[2] = !tenantStatus[2];
      displayText = tenantString();
    }
  }
  else if (digitalRead(buttonDpin) == LOW)
  {
    timeNow = millis();
    if (timeNow-timePrev >= timeWait )    
    {   
      timePrev = timeNow;   
      tenantStatus[3] = !tenantStatus[3];
      displayText = tenantString();
    }
  }
  else if (digitalRead(buttonEpin) == LOW)
  {
    timeNow = millis();
    if (timeNow-timePrev >= timeWait )    
    {   
      timePrev = timeNow;   
      tenantStatus[4] = !tenantStatus[4];
      displayText = tenantString();
    }
  }
  
}

