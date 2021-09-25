#include "OneButton.h"

// Setup a new OneButton on pin A1.  
OneButton button1(0, true);
// Setup a new OneButton on pin A2.  
//OneButton button2(A2, true);




void buttonRun(){
  button1.tick();
}
////////////////////////////////////////////////////////////////////////////////////////////

void click1() {
  Serial.println("Button 1 click.");
  SleepMode(0);
  i2cScan();
} 
void doubleclick1() {
  Serial.println("Button 1 doubleclick.");
    FILESYSTEM.format();
   //preferences.clear();
   delay(500);
   ESP.restart();
} 
void longPressStart1() {
  Serial.println("Button 1 longPress start");
} 
void longPress1() {
 Serial.println("Button 1 longPress...");
} 
void longPressStop1() {
  Serial.println("Button 1 longPress stop");
    deletpara();
     settingMode = true;
     SAVEconfig();
     ESP.restart();
} 
/////////////////////////////////////////////////////////////////////////////////////////
void setupButtons(){
   button1.attachClick(click1);
   button1.attachDoubleClick(doubleclick1);
//  button1.attachLongPressStart(longPressStart1);
   button1.attachLongPressStop(longPressStop1);
//  button1.attachDuringLongPress(longPress1);
}
