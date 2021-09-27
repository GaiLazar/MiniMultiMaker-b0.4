/*
  access the sample web page at http://esp32fs.local
  edit the page by going to http://esp32fs.local/edit
*/
#include <Wire.h>
#include <ESP.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>

#include <Arduino.h>
#include <WiFiClientSecure.h>
#include <WebSocketsServer.h>
#include <ArduinoJson.h>


//#include <Preferences.h>
//Preferences preferences;
//#define FILESYSTEM SPIFFS
//#define FORMAT_FILESYSTEM true


#define FILESYSTEM SPIFFS
// You only need to format the filesystem once
#define FORMAT_FILESYSTEM true
//#define DBG_OUTPUT_PORT Serial

#if FILESYSTEM == FFat
#include <FFat.h>
#endif
#if FILESYSTEM == SPIFFS
#include <SPIFFS.h>
#endif

WebServer server(80);
//holds the current upload
File fsUploadFile;

#include "var.h"
#include "FSys.h"
#include "gpio.h"
#include "config.h"
#include "WifiSet.h"

WebSocketsServer webSocket = WebSocketsServer(81);

#include "i2cS.h"
#include "clock.h"
#include "mqtt.h"
#include "json.h"
#include "websocet.h"
#include "serial.h"

#include "wewebFS.h"
#include "sleep.h"
#include "buttons.h"


long stopaleep;
int count=0;

TaskHandle_t Task1;
TaskHandle_t Task2;

void setup(void) {
FILESYSTEM.begin();
Wire.begin(22,21);//22=SDA,21=SCL


 AllPinSetup();

 restoreConfig();
 setSerial(); 
 setFILESYSTEM();
 setupButtons();
  
 print_wakeup_touchpad();
 print_wakeup_reason();
          
         if (settingMode == false) {setupSTAmode(); }
         else{TimerInterup=0;setupAPmode();}
            
  
  serverINIT();

 if (settingMode == false) { getNTPtime(); printLocalTime();}

  //TFTsetup();
  
   //here the list of headers to be recorded
  const char * headerkeys[] = {"User-Agent", "Cookie"} ;
  size_t headerkeyssize = sizeof(headerkeys) / sizeof(char*);
  //ask server to track these headers
  server.collectHeaders(headerkeys, headerkeyssize);
  server.begin();
  Serial.println("HTTP server started");

if(mqttOnOff==1 && NETstatus!=0 && settingMode == false){MqttSetup();}

  stopaleep=5000+millis();
 
//dubgIO(IO12);
websocetsetup();

// readFile("/config.txt");
// readFile("/2GPIO.txt");

 // MqttTimer=millis()+5000;
  
Serial.println(xPortGetCoreID());
 
  //create a task that will be executed in the Task1code() function, with priority 1 and executed on core 0
  xTaskCreatePinnedToCore(
                    Task1code,   /* Task function. */
                    "Task1",     /* name of task. */
                    10000,       /* Stack size of task */
                    NULL,        /* parameter of the task */
                    1,           /* priority of the task */
                    &Task1,      /* Task handle to keep track of created task */
                    0);          /* pin task to core 0 */                  
  delay(500); 

  //create a task that will be executed in the Task2code() function, with priority 1 and executed on core 1
  xTaskCreatePinnedToCore(
                    Task2code,   /* Task function. */
                    "Task2",     /* name of task. */
                    10000,       /* Stack size of task */
                    NULL,        /* parameter of the task */
                    2,           /* priority of the task */
                    &Task2,      /* Task handle to keep track of created task */
                    1);          /* pin task to core 1 */
    delay(500); 
}




void Task1code( void * pvParameters ){
  Serial.print("Task1 running on core ");
  Serial.println(xPortGetCoreID());
  // FILESYSTEM.format();
  //MqttRipetM=millis()  + (MqttrRipet*60)*1000;
  for (;;) // A Task shall never return or exit.
  {
    
    delay(10); 
    buttonRun(); 
    
    if( settingMode == false && WiFi.status() != WL_CONNECTED){ setupSTAmode();}
    // else{TimerInterup=0;setupAPmode();} 
   
    if(mqttOnOff==1 && NETstatus!=0 && settingMode == false && MqttTimer<millis()){
          if (!client.connected() && MqttTimerCountrer < 3) {reconnect();MqttTimer=millis()+5000;}
          else{ MqttTimerCountrer = 0;client.loop();}
       }

    if( mqttConnection==1 && MQttRiperOnOff==1 && MqttRipetM < millis()){
      MqttRipetM = millis()  + (MqttrRipet*60)*1000;
      MqttSendAll();
      }
       if( mqttConnection==1 && mqttferstmsg==0 && MqttMsgOnWekup==1 ){
      MqttSendAll();
      mqttferstmsg=1;
      }
      
   
    
    server.handleClient();
   
   
 }
}



void Task2code( void * pvParameters ){
  Serial.print("Task2 running on core ");
  Serial.println(xPortGetCoreID());

  for (;;)
  {
  delay(10); 
     interupSendMsg();
       if(buad>=0 && buad<=12 ){serialEvent();}
     webSocketloop();
      if(stopaleep<millis()){sleeper();}


        
  }
}


void loop(void) {   }
