
bool upfile=0;
void hexdump(const void *mem, uint32_t len, uint8_t cols = 16) {
  const uint8_t* src = (const uint8_t*) mem;
 Serial.printf("\n[HEXDUMP] Address: 0x%08X len: 0x%X (%d)", (ptrdiff_t)src, len, len);
  for(uint32_t i = 0; i < len; i++) {
    if(i % cols == 0) {
      Serial.printf("\n[0x%08X] 0x%08X: ", (ptrdiff_t)src, i);
    }
    Serial.printf("%02X ", *src);
    src++;
  }
  Serial.printf("\n");
}


String setjsonn;
String shortjsons(){

    String json = "all {";
    json += "\"heap\":" + String(ESP.getFreeHeap());
    json += ",\"RSSI\":" + String(WiFi.RSSI());    
    json += getAdc(); 
    json += shortjson();
    json += "}";
    setjsonn=json;
}





void senddata(uint8_t num, uint8_t * payload) {
   String xx=(char*)payload;
    Serial.println(xx);
    
    if(xx=="config"){ String json = configjson(); webSocket.sendTXT(num, json);}
   
   if(xx=="all"){shortjsons(); webSocket.sendTXT(num,setjsonn );  }
    
   if(xx=="button"){
    String json = "button {";
    json += "\"heap\":" + String(ESP.getFreeHeap());
    json += ",\"RSSI\":" + String(WiFi.RSSI());    
    json += shortjson();
    json += "}";
    webSocket.sendTXT(num, json);
   }
   
   if(xx=="adc"){
    String json = "adc {";
    json += "\"heap\":" + String(ESP.getFreeHeap());
    json += ",\"RSSI\":" + String(WiFi.RSSI());    
    json += getAdc(); 
    json += "}";
    webSocket.sendTXT(num, json);
   }
   
    if(xx=="i2c"){
     i2cScan();
        String json = "i2c {";
        json += "\"i2cscanResolt\":" + String(i2cscanResolt)+"\"";
        json += i2cscan;
        json += "}";
    webSocket.sendTXT(num, json);
   }
   
    if(xx=="hii"){
        String json = "hii {";
        json += "\"heap\":" + String(ESP.getFreeHeap());
        json += ",\"hallRead\":" + String(hallRead());
        if(!settingMode){
        json += ",\"RSSI\":" + String(WiFi.RSSI()); 
         if(mqttConnection==1){json += ",\"MQTTstate\":\"connected\"";}else{json += ",\"MQTTstate\":\"disconnected\"";}  
        }
        json += "}";
    webSocket.sendTXT(num, json);
   }
   
   if(xx=="--filelist--"){
    String json = FileList();
    Serial.println(json);
    webSocket.sendTXT(num, json);
   }
    
   if(xx.startsWith("fsread:")){
    String json;
    xx.replace("fsread:", "");
    Serial.println(xx);
    xx="/"+xx;
    File file = FILESYSTEM.open(xx);
    if (!file) {
      json="Failed to read file";
      Serial.println("Failed to read file");
      webSocket.sendTXT(num, json);
      return;
      }
       Serial.println("striming file");

    while (file.available()) {
      int x=0;  
      json="--**Sfile:";
      while(x!=200 && file.available()){
         x++;
         json+=(char)file.read();
         }
        webSocket.sendTXT(num, json);
      }
    Serial.println("fines striming file");
    json="--**Sfile**--";
    webSocket.sendTXT(num, json);
   }
///////////////////////////////////////////////////// uplode file
   if(xx.startsWith("--**upfile**--:--")){
    xx.replace("--**upfile**--:--", "");
    int oo=xx.indexOf("--");
    String namee=xx.substring(0, oo);
    xx.replace(namee + "--", "");
    if (!namee.startsWith("/")) {namee = "/" + namee;}
    if(!upfile){writeFile(SPIFFS, namee.c_str(), xx.c_str()); upfile=1;}
    else{appendFile(SPIFFS, namee.c_str() , xx.c_str());}
    }

    if(xx=="--**upfilend**--"){upfile=0;}

////////////////////////////////////////////////////////deletefile
if(xx.startsWith("--**deletefile**--:--")){
    xx.replace("--**deletefile**--:--", "");
    int oo=xx.indexOf("--");
    String namee=xx.substring(0, oo);
    xx.replace(namee + "--", "");
    if (!namee.startsWith("/")) {namee = "/" + namee;}
    deleteFile(SPIFFS, namee.c_str());
    }

////////////////////////////////////////////////////////
   
    if(xx=="serial"){outnum=num;seralOnSocket=1;}
    if(xx=="mqtt"){mqttOnSocket=1;}  
   if(xx=="ssid"){String json = "--*ssid*-- ";json += ssidList; webSocket.sendTXT(num, json);}  
   if(xx.startsWith("--*serial*--")){xx.replace("--*serial*--", "");Serial.println(xx);seralOnSocket=1;}    
   if(xx.startsWith("--*mqtt*--")){ xx.replace("--*mqtt*--", "");mqttPUB(xx); mqttOnSocket=1;}
   
////////////////////////////////////////////////////////output
   
   int XI;
   if(xx.startsWith("gpio-")){
   if(xx.startsWith("gpio-2-s=")){xx.replace("gpio-2-s=", ""); XI=xx.toInt(); chingIO(IO2 , XI); }
   if(xx.startsWith("gpio-4-s=")){xx.replace("gpio-4-s=", ""); XI=xx.toInt(); chingIO(IO4 , XI); }
   if(xx.startsWith("gpio-5-s=")){xx.replace("gpio-5-s=", ""); XI=xx.toInt(); chingIO(IO5 , XI); }
   if(xx.startsWith("gpio-16-s=")){xx.replace("gpio-16-s=", ""); XI=xx.toInt(); chingIO(IO16 , XI); }
   if(xx.startsWith("gpio-17-s=")){xx.replace("gpio-17-s=", ""); XI=xx.toInt(); chingIO(IO17 , XI); }
   if(xx.startsWith("gpio-25-s=")){xx.replace("gpio-25-s=", ""); XI=xx.toInt(); chingIO(IO25 , XI);}
   if(xx.startsWith("gpio-26-s=")){xx.replace("gpio-26-s=", ""); XI=xx.toInt(); chingIO(IO26 , XI); }
   if(xx.startsWith("gpio-27-s=")){xx.replace("gpio-27-s=", ""); XI=xx.toInt(); chingIO(IO27 , XI);}
   if(xx.startsWith("gpio-18-s=")){xx.replace("gpio-18-s=", ""); XI=xx.toInt(); chingIO(IO18 , XI); }
   if(xx.startsWith("gpio-19-s=")){xx.replace("gpio-19-s=", ""); XI=xx.toInt(); chingIO(IO19 , XI); }
   if(xx.startsWith("gpio-12-s=")){xx.replace("gpio-12-s=", ""); XI=xx.toInt(); chingIO(IO12 , XI); }
   if(xx.startsWith("gpio-13-s=")){xx.replace("gpio-13-s=", ""); XI=xx.toInt(); chingIO(IO13 , XI); }
   if(xx.startsWith("gpio-14-s=")){xx.replace("gpio-14-s=", ""); XI=xx.toInt(); chingIO(IO14 , XI);}
   if(xx.startsWith("gpio-15-s=")){xx.replace("gpio-15-s=", ""); XI=xx.toInt(); chingIO(IO15 , XI); }
   shortjsons();webSocket.sendTXT(num,setjsonn );
   }
///////////////////////////////////////////////////////////////////////////pwm  
   double XX;
   if(xx.startsWith("PwM-")){
   if(xx.startsWith("PwM-2=")){xx.replace("PwM-2=", ""); XX = xx.toDouble();chingpwm(IO2, XX);}
   if(xx.startsWith("PwM-4=")){xx.replace("PwM-4=", ""); XX = xx.toDouble();chingpwm(IO4, XX);}
   if(xx.startsWith("PwM-5=")){xx.replace("PwM-19=", ""); XX = xx.toDouble();chingpwm(IO5, XX);}
   if(xx.startsWith("PwM-16=")){xx.replace("PwM-16=", ""); XX = xx.toDouble();chingpwm(IO16, XX);}
   if(xx.startsWith("PwM-17=")){xx.replace("PwM-17=", ""); XX = xx.toDouble();chingpwm(IO17, XX);}
   if(xx.startsWith("PwM-25=")){xx.replace("PwM-25=", ""); XX = xx.toDouble();chingpwm(IO25, XX);}
   if(xx.startsWith("PwM-26=")){xx.replace("PwM-26=", ""); XX = xx.toDouble();chingpwm(IO26, XX);}
   if(xx.startsWith("PwM-27=")){xx.replace("PwM-27=", ""); XX = xx.toDouble();chingpwm(IO27, XX);}
   if(xx.startsWith("PwM-18=")){xx.replace("PwM-18=", ""); XX = xx.toDouble();chingpwm(IO18, XX);}
   if(xx.startsWith("PwM-19=")){xx.replace("PwM-19=", ""); XX = xx.toDouble();chingpwm(IO19, XX);}
   if(xx.startsWith("PwM-12=")){xx.replace("PwM-12=", ""); XX = xx.toDouble();chingpwm(IO12, XX);}
   if(xx.startsWith("PwM-13=")){xx.replace("PwM-13=", ""); XX = xx.toDouble();chingpwm(IO13, XX);}
   if(xx.startsWith("PwM-14=")){xx.replace("PwM-14=", ""); XX = xx.toDouble();chingpwm(IO14, XX);}
   if(xx.startsWith("PwM-15=")){xx.replace("PwM-15=", ""); XX = xx.toDouble();chingpwm(IO15, XX);}
   shortjsons();webSocket.sendTXT(num,setjsonn );
   }
}


void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {

    switch(type) {
        case WStype_DISCONNECTED:
            Serial.printf("[%u] Disconnected!\n", num);
            if( seralOnSocket==1){ seralOnSocket=0;}
             if( mqttOnSocket==1){ mqttOnSocket=0;}
            break;
        case WStype_CONNECTED:
            {
                IPAddress ip = webSocket.remoteIP(num);
                Serial.printf("[%u] Connected from %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);

        // send message to client
        webSocket.sendTXT(num, "Connected");
            }
            break;
        case WStype_TEXT:
         //   Serial.printf("[%u] get Text: %s\n", num, payload);
             senddata(num,payload);
            // send message to client
             //webSocket.sendTXT(num, json);
            
            // send data to all connected clients
            // webSocket.broadcastTXT("message here");
            break;
        case WStype_BIN:
            Serial.printf("[%u] get binary length: %u\n", num, length);
            hexdump(payload, length);

            // send message to client
            // webSocket.sendBIN(num, payload, length);
            break;
    case WStype_ERROR:      
    case WStype_FRAGMENT_TEXT_START:
    case WStype_FRAGMENT_BIN_START:
    case WStype_FRAGMENT:
    case WStype_FRAGMENT_FIN:
      break;
    }

}


void websocetsetup() {
    webSocket.begin();
    webSocket.onEvent(webSocketEvent);
}

void webSocketloop() {
    webSocket.loop();
}
