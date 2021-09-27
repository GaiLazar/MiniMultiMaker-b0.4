///////////////////////////////////////////////////////////////////////// get values




String getAdc(){
  setAdcVlue();
  String json;
    if(IO32.type==6){json += ", \"io32\":{";json+= "\"AdcVal\":" + String(IO32.AdcVal);json+=+ "}";}
    if(IO33.type==6){json += ", \"io33\":{";json+= "\"AdcVal\":" + String(IO33.AdcVal);json+=+ "}";}
    if(IO34.type==6){json += ", \"io34\":{";json+= "\"AdcVal\":" + String(IO34.AdcVal);json+=+ "}";}
    if(IO35.type==6){json += ", \"io35\":{";json+= "\"AdcVal\":" + String(IO35.AdcVal);json+=+ "}";}
    if(IO36.type==6){json += ", \"io36\":{";json+= "\"AdcVal\":" + String(IO36.AdcVal);json+=+ "}";}
    if(IO39.type==6){json += ", \"io39\":{";json+= "\"AdcVal\":" + String(IO39.AdcVal);json+=+ "}";}
    
    return json;
    
}


 ///////////////////////////////////////////////////////////////////////////////////////////////JSON


  String Setjson(gpio IO){
  String json = ", \"io"+String(IO.pin)+"\":{";
  json+="\"type\":" + String(IO.type) ;
  json+= ",\"pin\":" + String(IO.pin);
  json+= ",\"Touch\":" + String(IO.Touch);
  json+= ",\"interup\":" + String(IO.interup);
  json+= ",\"spi\":" + String(IO.spi);
  json+= ",\"ADC\":" + String(IO.ADC);
  json+= ",\"RunInterup\":" + String(IO.RunInterup);
  json+= ",\"Uname\":\"" + IO.Uname +"\"";
  if(IO.Touch==1){
    json+= ",\"TouchTHRESHOLD\":" + String(IO.TouchTHRESHOLD);
    json+= ",\"TouchVlue\":" + String(IO.TouchVlue);
    }
  json+= ",\"IOstaet\":" + String(digitalRead(IO.pin));
  json+= ",\"IOset\":" + String(IO.IOset);
  if(IO.ADC==0){
    json+= ",\"PwM\":" + String(IO.PwM);
    json+= ",\"MaxDute\":" + String(IO.MaxDute);
    json+= ",\"Hz\":" + String(IO.Hz);
    json+= ",\"Bit\":" + String(IO.Bit);
  }
  if(IO.ADC==1){
     json+= ",\"AdcVal\":" + String(IO.AdcVal);
     json+= ",\"AdcMax\":" + String(IO.AdcMax);
     json+= ",\"AdcMin\":" + String(IO.AdcMin);
  }
  
  json+= "}";
    return json;
}


String SetShortJson(gpio IO){
    String json = ", \"io"+String(IO.pin)+"\":{";
    json+="\"IOstaet\":" + String(digitalRead(IO.pin));
    if(IO.ADC==0){json+= ",\"PwM\":" + String(IO.PwM);}
   if(IO.Touch==1){ json+= ",\"TouchVlue\":" + String(IO.TouchVlue);}
   if(IO.ADC==1){json+= ",\"AdcVal\":" + String(IO.AdcVal);}
    
    json+=+ "}";
    return json;
}


String shortjson(){
  setTouchVlue();
   setAdcVlue();
      String json;
              json = SetShortJson(IO2);
              json += SetShortJson(IO4);
              json += SetShortJson(IO5);
              json += SetShortJson(IO12);
              json += SetShortJson(IO13);
              json += SetShortJson(IO14);
              json += SetShortJson(IO15);
              json += SetShortJson(IO16);
              json += SetShortJson(IO17);
              json += SetShortJson(IO18);
              json += SetShortJson(IO19);
              
              json += SetShortJson(IO25);
              json += SetShortJson(IO26);
              json += SetShortJson(IO27);
              json += SetShortJson(IO32);
              json += SetShortJson(IO33);
              json += SetShortJson(IO34);
              json += SetShortJson(IO35);
              json += SetShortJson(IO36);
              json += SetShortJson(IO39);
              return json;
}
String iojson(){

      String json;
              json = Setjson(IO2);
              json += Setjson(IO4);
              json += Setjson(IO5);
              json += Setjson(IO12);
              json += Setjson(IO13);
              json += Setjson(IO14);
              json += Setjson(IO15);
              json += Setjson(IO16);
              json += Setjson(IO17);
              json += Setjson(IO18);
              json += Setjson(IO19);
             
              json += Setjson(IO25);
              json += Setjson(IO26);
              json += Setjson(IO27);
                      
              json += Setjson(IO32);
              json += Setjson(IO33);
              json += Setjson(IO34);
              json += Setjson(IO35);
              json += Setjson(IO36);
              json += Setjson(IO39);
              return json;
}



String configjson(){
   setTouchVlue();
   setAdcVlue();
      String json = "config {";
        json += "\"heap\":" + String(ESP.getFreeHeap());
        json += ",\"hallRead\":" + String(hallRead());
        if(!settingMode){
            json += ",\"IP\": \"" + WiFi.localIP().toString()+"\"";
            json += ",\"RSSI\":" + String(WiFi.RSSI());   
            if(NETstatus==1){json += ",\"NAT\":\"LOCAL\"";}else{json += ",\"NAT\":\"NET\"";} 
            if(mqttConnection==1){json += ",\"MQTTstate\":\"connected\"";}else{json += ",\"MQTTstate\":\"disconnected\"";}       
            json += ",\"SSID\":\"" + String(WiFi.SSID())+"\"";
            json += ",\"STAAP\":\"Station\"";
          }
          else{
            json += ",\"IP\": \"192.168.4.1\"";
            json += ",\"STAAP\":\"AP\"";
            json += ",\"MQTTstate\":\"disconnected\"";
            json += ",\"SSID\":\"" + String(apSSID) +"\"";
          }
        json += ",\"mqttOnOff\":\"" + String(mqttOnOff)+"\"";
        json += ",\"mqtt_server\":\"" + String(mqtt_server)+"\"";
        json += ",\"port\":\"" + String(port)+"\"";
        json += ",\"MqttrRipet\":\"" + String(MqttrRipet)+"\"";
        json += ",\"MQttRiperOnOff\":\"" + String(MQttRiperOnOff)+"\"";
        json += ",\"MqttMesgOnStart\":\"" + String(MqttMsgOnWekup)+"\"";
        json += ",\"clientId\":\"" + String(clientId)+"\"";
        json += ",\"outTopic\":\"" + String(outTopic)+"\"";
        json += ",\"inTopic\":\"" + String(inTopic)+"\"";
        json += ",\"MDNS\":\"" + String(host)+"\"";
        json += ",\"apSSID\":\"" + String(apSSID)+"\"";
        json += ",\"TimerInterup\":\"" + String(TimerInterup)+"\"";
        json += ",\"Serial\":\"" + String(buad)+"\"";
        json += ",\"ButtonInterup\":\"" + String(ButtonInterup)+"\"";
        json += ",\"TimeOfSleep\":\"" + String((TimeOfSleep/1000000)/60)+"\"";
        json += ",\"WakeupTouchPad\":\"" + String(WakeupTouchPad)+"\"";
        json += ",\"WakeupIOres\":\"" + String(WakeupIOres)+"\"";
        json += ",\"ntpclk\":\"" + String(ntpServer)+"\"";
        json += ",\"offsetclk\":\"" + String((gmtOffset_sec/60)/60)+"\"";
        json += iojson();
        json += "}";
              return json;
}
