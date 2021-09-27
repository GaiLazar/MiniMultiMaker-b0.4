
boolean restoreConfig() {
  File file = FILESYSTEM.open("/config.txt");
  StaticJsonDocument<1500> doc;
  DeserializationError error = deserializeJson(doc, file);
  if (error){Serial.println(error.c_str());}

  TimerInterup = doc["sleepOnOff"] | false ;
  ButtonInterup=doc["ButtonInterup"] | false ;
  TimeOfSleep=doc["TimeOfSleep"] | 2000000;
    
  gmtOffset_sec=doc["gmtOffset_sec"] | 7200;
  ntpServer=doc["ntpServer"] | "pool.ntp.org" ;

  buad=doc["buad"]| 10;
  settingMode=doc["settingMode"] | true ;
  
  wifi_ssid=doc["wifi_ssid"]|"" ;
  wifi_password=doc["wifi_password"]|"" ;
  apSSID=doc["apSSID"]|"ESP32_SETUP" ;
  ApPasword=doc["ApPasword"]|"password" ;
  host=doc["host"]| "esp32fs" ;
  HostUserName=doc["HostUserName"]| "User" ;
  HostPasword=doc["HostPasword"]| "password" ;

  mqtt_server=doc["MQTT_SERVER"] | "example.com"; 
  port= doc["MQTT_PORT"] | 1889;
  username= doc["USER_NAME"] | "";
  userpass= doc["MQTT_PASSWD"] | ""; 
  inTopic= doc["IN_TOPIC"] | "inTopic";
  outTopic= doc["OUT_TOPIC"] | "outTopic";
  clientId= doc["clientId"] | "clientId"; 
  MqttMsgOnWekup =doc["MqttMsgOnWekup"] | false;  
  MQttRiperOnOff =doc["MQttRiperOnOff"] | false; 
  mqttOnOff= doc["MQTTOnOff"] | false;
  MqttrRipet = doc["MqttrRipet"] | 2; 
   
  file.close();
  
  if(wifi_ssid.length() > 0) {return true;}
  else {return false;}
   
}



void SAVEconfig(){
FILESYSTEM.remove("/config.txt");
  File file = FILESYSTEM.open("/config.txt", FILE_WRITE);
  if (!file) {Serial.println(F("Failed to create file")); return; }
  StaticJsonDocument<1500> doc;
 doc["sleepOnOff"] = TempoFlag  ;
 doc["ButtonInterup"] = ButtonInterup  ;
 doc["TimeOfSleep"] = TimeOfSleep;
   
 doc["gmtOffset_sec"] = gmtOffset_sec;
 doc["ntpServer"] = ntpServer  ;
  
 doc["buad"] = buad;
 doc["settingMode"] = settingMode;
 
 doc["wifi_ssid"] = wifi_ssid ;
 doc["wifi_password"] = wifi_password;
 doc["apSSID"]= apSSID;
 doc["ApPasword"]= ApPasword;
 doc["host"] = host ;
 doc["HostUserName"] = HostUserName ;
 doc["HostPasword"] = HostPasword ;

 
 doc["MQTT_SERVER"] = mqtt_server;
 doc["MQTT_PORT"] =port;
 doc["USER_NAME"] =username;
 doc["MQTT_PASSWD"]=userpass;
 doc["IN_TOPIC"] =inTopic;
 doc["OUT_TOPIC"] =outTopic;
 doc["clientId"] =clientId;
 doc["MQTTOnOff"] = mqttOnOff ;
 doc["MqttMsgOnWekup"] = MqttMsgOnWekup;
 doc["MQttRiperOnOff"]= MQttRiperOnOff;
 doc["MqttrRipet"] = MqttrRipet;
 
 if (serializeJson(doc, file) == 0) {Serial.println(F("Failed to write to file"));}
 file.close();  
}
