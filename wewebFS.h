String makePage(String title, String contents ,bool root=0) {
  String s = "<!DOCTYPE html><html><head>";
  s += "<meta name=\"viewport\" content=\"width=device-width,initial-scale=1\">";
  s += "<title>";
  s += title;
  s += "</title></head><body style=\"text-align: center;\">";
  s += contents;
  if(!root){s+= "<p><a href=\"/..\">BACK</a></p>";}
  s += "</body></html>";
  return s;
}

String urlDecode(String input) {
  String s = input;
  s.replace("%20", " ");
  s.replace("+", " ");
  s.replace("%21", "!");
  s.replace("%22", "\"");
  s.replace("%23", "#");
  s.replace("%24", "$");
  s.replace("%25", "%");
  s.replace("%26", "&");
  s.replace("%27", "\'");
  s.replace("%28", "(");
  s.replace("%29", ")");
  s.replace("%30", "*");
  s.replace("%31", "+");
  s.replace("%2C", ",");
  s.replace("%2E", ".");
  s.replace("%2F", "/");
  s.replace("%2C", ",");
  s.replace("%3A", ":");
  s.replace("%3A", ";");
  s.replace("%3C", "<");
  s.replace("%3D", "=");
  s.replace("%3E", ">");
  s.replace("%3F", "?");
  s.replace("%40", "@");
  s.replace("%5B", "[");
  s.replace("%5C", "\\");
  s.replace("%5D", "]");
  s.replace("%5E", "^");
  s.replace("%5F", "-");
  s.replace("%60", "`");
  return s;
}





////////////////////////////////////
struct gpio SetGet2Memore(gpio IO){
    double XD;
    long XL;
       int XI;
       String XS;
      String namee;
       namee="io";namee+=String(IO.pin);
       if(urlDecode(server.arg(namee))!= ""){XI = urlDecode(server.arg(namee)).toInt();if(XI>=0 && XI<=2){IO.IOset=XI;}}
       namee="MaxDute";namee+=String(IO.pin);
       if(urlDecode(server.arg(namee))!= ""){XD = urlDecode(server.arg(namee)).toDouble();IO.MaxDute=XD;}
       namee="Hz";namee+=String(IO.pin);
       if(urlDecode(server.arg(namee))!= ""){XD = urlDecode(server.arg(namee)).toDouble();IO.Hz=XD;}
       namee="Bit";namee+=String(IO.pin);
       if(urlDecode(server.arg(namee))!= ""){XI = urlDecode(server.arg(namee)).toInt();IO.Bit=XI;} 
       namee="type";namee+=String(IO.pin);
       if(urlDecode(server.arg(namee))!= ""){XI = urlDecode(server.arg(namee)).toInt();if(XI>=0 && XI<=7){IO.type=XI;}}
       namee="RunInterup";namee+=String(IO.pin);
       if(urlDecode(server.arg(namee))!= ""){XI = urlDecode(server.arg(namee)).toInt();IO.RunInterup=XI;}
       namee="Uname";namee+=String(IO.pin);
       if(urlDecode(server.arg(namee))!= ""){XS = urlDecode(server.arg(namee));IO.Uname=XS;}
       namee="THRESHOLD";namee+=String(IO.pin);
       if(urlDecode(server.arg(namee))!= ""){XI = urlDecode(server.arg(namee)).toInt();IO.TouchTHRESHOLD=XI;}
       namee="AdcMax";namee+=String(IO.pin);
       if(urlDecode(server.arg(namee))!= ""){XL = urlDecode(server.arg(namee)).toDouble();IO.AdcMax=XL;}
       namee="AdcMin";namee+=String(IO.pin);
       if(urlDecode(server.arg(namee))!= ""){XL = urlDecode(server.arg(namee)).toDouble();IO.AdcMin=XL;}
       return IO;
  }

  struct gpio SetGetStaet2Memore(gpio IO){
    double XX;
       int XI;
       bool XB;
       String nameee;
       nameee="io";
       nameee+=String(IO.pin);
       nameee+="s";;
       if(urlDecode(server.arg(nameee))!= ""){
          XI = urlDecode(server.arg(nameee)).toInt();
          if(XI==1 || XI==0){
            if(IO.IOset==1){ digitalWrite(IO.pin, XI);}
            if(XI==1){IO.IOstaet=1;}else{IO.IOstaet=0;}
            SetIoMemory(IO);
          }
       }
      nameee="PwM";
      nameee+=String(IO.pin);
       if(urlDecode(server.arg(nameee))!= "" ){
           XX = urlDecode(server.arg(nameee)).toDouble();
           if(XX>=0 && XX<IO.MaxDute){IO.PwM=XX;}
           else{IO.PwM=IO.MaxDute;}
           ledcWrite(IO.ClockNum,IO.PwM);
           SetIoMemory(IO);
        }
       return IO;
       
  }

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void serverINIT(){

//SERVER INIT
 server.on("/login", handleLogin);
  //list directory
  server.on("/list", HTTP_GET, handleFileList);
  //load editor
  server.on("/edit", HTTP_GET, []() {
    if (!handleFileRead("/edit.htm")) {
      server.send(404, "text/plain", "FileNotFound");
    }
  });
  //create file
 // server.on("/edit", HTTP_PUT, handleFileCreate);
  //delete file
 // server.on("/edit", HTTP_DELETE, handleFileDelete);
  //first callback is called after the request has ended with all parsed arguments
  //second callback handles file uploads at that location
  //server.on("/edit", HTTP_POST, []() {
  //  server.send(200, "text/plain", "");}, handleFileUpload);

  //called when the url is not defined here
  //use it to load content from FILESYSTEM
  server.onNotFound([]() {
    if (!handleFileRead(server.uri())) {
       Serial.println("not found" + server.uri());
      server.send(404, "text/plain", "FileNotFound");
    }
  });
////////////////////////////////////////////////////////////////////////////////////////////
  //get heap status, analog input value and all GPIO statuses in one json call
  server.on("/all", HTTP_GET, []() {
    
    String json = "{";
    json += "\"heap\":" + String(ESP.getFreeHeap());
    json += ",\"RSSI\":" + String(WiFi.RSSI());    
    json += getAdc();
    json += shortjson();
    json += "}";
    
    server.send(200, "text/json", json);
    json = String();
  });
/////////////////////////////////////////////////////////////////////////////////////////////////

  //get heap status, analog input value and all GPIO statuses in one json call
  server.on("/config", HTTP_GET, []() {
    String json = configjson();
    server.send(200, "text/json", json);
    json = String();
  });

///////////////////////////////////////////////////////////////////////////////////////////////////
 server.on("/setupwifi", HTTP_POST, []() {
       String XX;
       
       if(urlDecode(server.arg("ssid"))!= ""){wifi_ssid = urlDecode(server.arg("ssid"));}
       if(urlDecode(server.arg("pass"))!= ""){wifi_password = urlDecode(server.arg("pass"));}
       if(urlDecode(server.arg("mdns"))!= ""){host = urlDecode(server.arg("mdns"));}
       if(urlDecode(server.arg("apssid"))!= ""){apSSID = urlDecode(server.arg("apssid"));}
        if(urlDecode(server.arg("apPassword"))!= ""){ApPasword = urlDecode(server.arg("apPassword"));}
       if(urlDecode(server.arg("webusername"))!= ""){HostUserName = urlDecode(server.arg("webusername"));}
       if(urlDecode(server.arg("webUserPassword"))!= ""){HostPasword = urlDecode(server.arg("webUserPassword"));}
       
       
      String s = "<h1>Setup complete.</h1><p>device will be connected to \"";
      s += wifi_ssid;
      s += "\" after the restart.";
      server.send(200, "text/html", makePage("SAVE WiFi Settings", s));
      settingMode = false;
      SAVEconfig();
      delay(2000);
      ESP.restart();
    });

    /////////////////////////////////////////////////////////////////////////////////////////////////////////
     server.on("/setupmqtt",HTTP_GET, []() {
       String XX;
       int XI;
       if(urlDecode(server.arg("mqttonoff")) != ""){
           XX = urlDecode(server.arg("mqttonoff"));
           if(XX == "moff"){mqttOnOff=0;}
           if(XX== "mon"){mqttOnOff=1;}
       }
       if(urlDecode(server.arg("pow")) != ""){
           XX = urlDecode(server.arg("pow"));
           if(XX == "off"){MqttMsgOnWekup=0;}
           if(XX== "on"){MqttMsgOnWekup=1;}
       }
       if(urlDecode(server.arg("MQttROnOff")) != ""){
           XX = urlDecode(server.arg("MQttROnOff"));
           if(XX == "off"){MQttRiperOnOff=0;}
           if(XX== "on"){MQttRiperOnOff=1;}
       }
       if(urlDecode(server.arg("MqttrRipet")) != ""){
            XI=urlDecode(server.arg("MqttrRipet")).toInt();
           MqttrRipet=XI;
       }
       if(urlDecode(server.arg("mserver"))!=""){mqtt_server = urlDecode(server.arg("mserver"));}
       if(urlDecode(server.arg("mport"))!=""){port=urlDecode(server.arg("mport")).toInt();}
       if(urlDecode(server.arg("muser"))!=""){username = urlDecode(server.arg("muser"));}
       if(urlDecode(server.arg("mpass"))!=""){userpass = urlDecode(server.arg("mpass"));}
       if(urlDecode(server.arg("mintopic"))!=""){inTopic = urlDecode(server.arg("mintopic"));}
       if(urlDecode(server.arg("mouttopic"))!=""){outTopic = urlDecode(server.arg("mouttopic"));}
       if(urlDecode(server.arg("clientId"))!=""){clientId = urlDecode(server.arg("clientId"));}
       
       
       SAVEconfig();
       
   
      handleFileRead("/progreesbar.html");
      //server.send(200, "text/html", makePage("SAVE WiFi Settings", s));
      delay(2000);
      ESP.restart();
    });
    /////////////////////////////////////////////////////////////////////////////////////////////////////////
     server.on("/setupclock",HTTP_GET, []() {
       String XX;
      int XI;
      if(urlDecode(server.arg("pool")) != ""){
        XX = urlDecode(server.arg("pool"));
        ntpServer=XX.c_str();
        }
      if(urlDecode(server.arg("offset"))!= ""){
        XI=urlDecode(server.arg("offset")).toInt();
        if(XI >= -12 || XI <= 12 ){gmtOffset_sec = (XI * 60)*60;}
        }
       SAVEconfig();
     handleFileRead("/progreesbar.html");
      delay(2000);
      ESP.restart();
    });

     /////////////////////////////////////////////////////////////////////////////////////////////////////////
     server.on("/serialmsseg",HTTP_GET, []() {
       String XX,sendM,getM;
      int XI;
      bool reset =0;
      
      if(urlDecode(server.arg("msgS")) != "" ){Serial.println(String(urlDecode(server.arg("msgS"))));}
      if(urlDecode(server.arg("baud")) != "" ){
        XI=(urlDecode(server.arg("baud"))).toInt();
        if(XI>=0 && XI<=12){
         buad=XI;
         SAVEconfig();
         reset=1;
        }
      }
      
      sendM=SerialRX;
      SerialRX="";
      sendM.replace("\r\n", "<br>");
      sendM.replace("\n", "<br>");
      sendM.replace("\r", "<br>");

      String json = "{";
                json += "\"heap\":" + String(ESP.getFreeHeap());
                if(!settingMode){ json += ",\"RSSI\":" + String(WiFi.RSSI());}   
                 json += ",\"SerialMsg\":\"" + String(sendM) + "\"";
      
      json += "}";
     
      
     if(reset){handleFileRead("/progreesbar.html");delay(2000);ESP.restart();}
     else{server.send(200, "text/json", json);}
     
    });
    /////////////////////////////////////////////////////////////////////////////////////////////////////////
     server.on("/mqttmsseg",HTTP_GET, []() {
       String XX,sendM,getM;
      int XI;
      
      if(urlDecode(server.arg("msgS")) != "" ){
        mqttPUB(String(urlDecode(server.arg("msgS"))));
        }
      
      sendM=MqttMssege;
      MqttMssege="";
      sendM.replace("\r\n", "<br>");
      
      server.send(200, "text/plain", sendM );
     
    });
/////////////////////////////////////////////////////////////////////////////////////////////////////////
     server.on("/I2C",HTTP_GET, []() {
       String XX,sendM,getM;
      int XI;
  
     i2cScan();
        String json = "{";
        json += "\"i2cscanResolt\":\"" + String(i2cscanResolt)+"\"";
        json += i2cscan;
        json += "}";
     
      server.send(200, "text/json", json );
    });
      /////////////////////////////////////////////////////////////////////////////////////////////////////////
     server.on("/setinterup",HTTP_GET, []() {
       int XX;
       int XI;
       bool XB;
       int timeToM;
        
       if(urlDecode(server.arg("sleep"))!= ""){XI = urlDecode(server.arg("sleep")).toInt();if(XI==1 || XI==0){TempoFlag=XI;}}
       if(urlDecode(server.arg("iointerup")) !=""){XI = urlDecode(server.arg("iointerup")).toInt();if(XI==1 || XI==0){ButtonInterup=XI;}}
       if(urlDecode(server.arg("timer")) !=""){timeToM = urlDecode(server.arg("timer")).toInt();TimeOfSleep = (timeToM * 60) * 1000000;} ////======(M*S)*uS

       if(urlDecode(server.arg("IO2")) !=""){XX = urlDecode(server.arg("IO2")).toInt();if(XX == 1 || XX == 0 || XX == 2){IO2.interup=XX;}}
       if(urlDecode(server.arg("IO4")) !=""){XX = urlDecode(server.arg("IO4")).toInt();if(XX == 1 || XX == 0 || XX == 2){IO4.interup=XX;}}
       if(urlDecode(server.arg("IO12")) !=""){XX = urlDecode(server.arg("IO12")).toInt();if(XX == 1 || XX == 0 || XX == 2){IO12.interup=XX;}}
       if(urlDecode(server.arg("IO13")) !=""){XX = urlDecode(server.arg("IO13")).toInt();if(XX == 1 || XX == 0 || XX == 2){IO13.interup=XX;}} 
       if(urlDecode(server.arg("IO14")) !=""){XX = urlDecode(server.arg("IO14")).toInt();if(XX == 1 || XX == 0 || XX == 2){IO14.interup=XX;}}
       if(urlDecode(server.arg("IO15")) !=""){XX = urlDecode(server.arg("IO15")).toInt();if(XX == 1 || XX == 0 || XX == 2){IO15.interup=XX;}}
       if(urlDecode(server.arg("IO25")) !=""){XX = urlDecode(server.arg("IO25")).toInt();if(XX == 1 || XX == 0){IO25.interup=XX;}}
       if(urlDecode(server.arg("IO26")) !=""){XX = urlDecode(server.arg("IO26")).toInt();if(XX == 1 || XX == 0){IO26.interup=XX;}}
       if(urlDecode(server.arg("IO27")) !=""){XX = urlDecode(server.arg("IO27")).toInt();if(XX == 2 || XX == 1|| XX == 0){IO27.interup=XX;}}

       SetIoMemory(IO2);
       SetIoMemory(IO4);
       SetIoMemory(IO12);
       SetIoMemory(IO13);
       SetIoMemory(IO14);
       SetIoMemory(IO15);
       SetIoMemory(IO25);
       SetIoMemory(IO26);
       SetIoMemory(IO27);
       
      handleFileRead("/progreesbar.html");
      SAVEconfig();
      
     delay(3000);
     ESP.restart();
    });

    /////////////////////////////////////////////////////////////////////////////////////////////////////////
     server.on("/gpio",HTTP_GET, []() {
       int XX;
       
       IO2=SetGetStaet2Memore(IO2);
       IO4=SetGetStaet2Memore(IO4);
       IO5=SetGetStaet2Memore(IO5);
       IO16=SetGetStaet2Memore(IO16);
       IO17=SetGetStaet2Memore(IO17);
       IO25=SetGetStaet2Memore(IO25);
       IO26=SetGetStaet2Memore(IO26);
       IO27=SetGetStaet2Memore(IO27);
       IO19=SetGetStaet2Memore(IO19);
       IO18=SetGetStaet2Memore(IO18);
       IO12=SetGetStaet2Memore(IO12);
       IO13=SetGetStaet2Memore(IO13);
       IO14=SetGetStaet2Memore(IO14);
       IO15=SetGetStaet2Memore(IO15);
       IO32=SetGetStaet2Memore(IO32);
       IO33=SetGetStaet2Memore(IO33);
       IO34=SetGetStaet2Memore(IO34);
       IO35=SetGetStaet2Memore(IO35);
       IO36=SetGetStaet2Memore(IO36);
       IO39=SetGetStaet2Memore(IO39);
    
       
       String json = "{";
       json += "\"heap\":" + String(ESP.getFreeHeap());
              json += shortjson();
              json += "}";

    server.send(200, "text/json", json);
    });
  
///////////////////////////////////////////////////////////////////////////////////////////////////

server.on("/GPIOSET",HTTP_POST, []() {

   
   IO2=SetGet2Memore(IO2);
   IO4=SetGet2Memore(IO4);
   IO5=SetGet2Memore(IO5);
   
   IO16=SetGet2Memore(IO16);
   IO17=SetGet2Memore(IO17);
   IO25=SetGet2Memore(IO25);
   IO26=SetGet2Memore(IO26);
   IO27=SetGet2Memore(IO27);
   IO19=SetGet2Memore(IO19);
   IO18=SetGet2Memore(IO18);
   
   IO12=SetGet2Memore(IO12);
   IO13=SetGet2Memore(IO13);
   IO14=SetGet2Memore(IO14);
   IO15=SetGet2Memore(IO15);
   
   IO32=SetGet2Memore(IO32);
   IO33=SetGet2Memore(IO33);
   IO34=SetGet2Memore(IO34);
   IO35=SetGet2Memore(IO35);
   IO36=SetGet2Memore(IO36);
   IO39=SetGet2Memore(IO39);

      
       SetIoMemory(IO2);
       SetIoMemory(IO4);
       SetIoMemory(IO5);
       SetIoMemory(IO16);
       SetIoMemory(IO17);
       SetIoMemory(IO25);
       SetIoMemory(IO26);
       SetIoMemory(IO27);
       SetIoMemory(IO19);
       SetIoMemory(IO18);
      
       SetIoMemory(IO12);
       SetIoMemory(IO13);
       SetIoMemory(IO14);
       SetIoMemory(IO15);
       SetIoMemory(IO32);
       SetIoMemory(IO33);
       SetIoMemory(IO34);
       SetIoMemory(IO35);
       SetIoMemory(IO36);
       SetIoMemory(IO39);

        String json = "{";
       json += "\"heap\":" + String(ESP.getFreeHeap());
              json += shortjson();
              json += "}";

     handleFileRead("/progreesbar.html");
    //server.send(200, "text/json", json);
      delay(3000);
      ESP.restart();
    });
///////////////////////////////////////////////////////////////////////////////////////////////////

    server.on("/ssidList", HTTP_GET, []() {server.send(200, "text/plain", ssidList);});
///////////////////////////////////////////////////////////////////////////////////////////////////
}
