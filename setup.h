///////////////////////////////////////////////////////////////////////// get values
struct gpio GetTouchVlue(gpio IO){
if(IO.type==2 && IO.Touch==1){
    if(IO.pin==2){IO.TouchVlue=touchRead(T2); }
    if(IO.pin==4){IO.TouchVlue=touchRead(T0); }
    if(IO.pin==27){IO.TouchVlue=touchRead(T7) ;}
    if(IO.pin==12){IO.TouchVlue=touchRead(T5); }
    if(IO.pin==13){IO.TouchVlue=touchRead(T4); }
    if(IO.pin==14){IO.TouchVlue=touchRead(T6) ;}
    if(IO.pin==15){IO.TouchVlue=touchRead(T3) ;}
    if(IO.pin==32){IO.TouchVlue=touchRead(T9) ;}
    if(IO.pin==33){IO.TouchVlue=touchRead(T8) ;}
    }
    return IO;
}

void setTouchVlue(){
IO2=GetTouchVlue(IO2);
IO4=GetTouchVlue(IO4);
IO27=GetTouchVlue(IO27);
IO12=GetTouchVlue(IO12);
IO13=GetTouchVlue(IO13);
IO14=GetTouchVlue(IO14);
IO15=GetTouchVlue(IO15);
IO32=GetTouchVlue(IO32);
IO33=GetTouchVlue(IO33);
}

struct gpio GetAdcVlue(gpio IO){
    if(IO.type==6 && IO.ADC==1){IO.AdcVal=analogRead(IO.pin);}
  return IO;
}

void setAdcVlue(){
IO32=GetAdcVlue(IO32);
IO33=GetAdcVlue(IO33);
IO34=GetAdcVlue(IO34);
IO35=GetAdcVlue(IO35);
IO36=GetAdcVlue(IO36);
IO39=GetAdcVlue(IO39);
}


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
////////////////////////////////////////////////////////////////////////////////////////////////mqtt messges
String valueToMqttMsg(gpio IO){
  String X;
  if(IO.type==0 && IO.IOset==0){X="Input:";X+=digitalRead(IO.pin);}
  if(IO.type==0 && IO.IOset==1){X="Output:";X+=digitalRead(IO.pin);}
  if(IO.type==0 && IO.IOset==0){X="InputPULLUP:";X+=digitalRead(IO.pin);}
  if(IO.type==1){X="PWM:";X+=IO.PwM;}
  if(IO.type==2){X="Touch:";X+=IO.TouchVlue;}
  if(IO.type==6){X="ADC:";X+=analogRead(IO.pin);}
  return X;
}

void MqttSendAll(){
  SmqttPUB(valueToMqttMsg(IO2),IO2.Uname);
  SmqttPUB(valueToMqttMsg(IO4),IO4.Uname);
  SmqttPUB(valueToMqttMsg(IO5),IO5.Uname);
  SmqttPUB(valueToMqttMsg(IO12),IO12.Uname);
  SmqttPUB(valueToMqttMsg(IO13),IO13.Uname);
  SmqttPUB(valueToMqttMsg(IO14),IO14.Uname);
  SmqttPUB(valueToMqttMsg(IO15),IO15.Uname);
  SmqttPUB(valueToMqttMsg(IO16),IO16.Uname);
  SmqttPUB(valueToMqttMsg(IO17),IO17.Uname);
  SmqttPUB(valueToMqttMsg(IO18),IO18.Uname);
  SmqttPUB(valueToMqttMsg(IO19),IO19.Uname);
  SmqttPUB(valueToMqttMsg(IO25),IO25.Uname);
  SmqttPUB(valueToMqttMsg(IO26),IO26.Uname);

  SmqttPUB(valueToMqttMsg(IO32),IO32.Uname);
  SmqttPUB(valueToMqttMsg(IO33),IO33.Uname);
  SmqttPUB(valueToMqttMsg(IO34),IO34.Uname);
  SmqttPUB(valueToMqttMsg(IO35),IO35.Uname);
  SmqttPUB(valueToMqttMsg(IO36),IO36.Uname);
  SmqttPUB(valueToMqttMsg(IO39),IO39.Uname);
  
}



String valueToSend(gpio IO){
  String X="IO";
  X+=IO.pin;
  X+="=";
  if(IO.RunInterup!=4){X+=digitalRead(IO.pin);}
  if(IO.RunInterup==4){X+=IO.TouchVlue;}
  return X;
}

void interupSendMsg(){
  setTouchVlue();
  if(intruptMsgFlag==1 && intruptMsg<millis()){
    
         if(mqttConnection){
            if(IO2.RunInterup!=0){SmqttPUB(valueToMqttMsg(IO2),IO2.Uname);}
            if(IO4.RunInterup!=0){SmqttPUB(valueToMqttMsg(IO4),IO4.Uname);}
            if(IO5.RunInterup!=0){SmqttPUB(valueToMqttMsg(IO5),IO5.Uname);}
            if(IO12.RunInterup!=0){SmqttPUB(valueToMqttMsg(IO12),IO12.Uname);}
            if(IO13.RunInterup!=0){SmqttPUB(valueToMqttMsg(IO13),IO13.Uname);}
            if(IO14.RunInterup!=0){SmqttPUB(valueToMqttMsg(IO14),IO14.Uname);}
            if(IO15.RunInterup!=0){SmqttPUB(valueToMqttMsg(IO15),IO15.Uname);}
            if(IO16.RunInterup!=0){SmqttPUB(valueToMqttMsg(IO16),IO16.Uname);}
            if(IO17.RunInterup!=0){SmqttPUB(valueToMqttMsg(IO17),IO17.Uname);}
            if(IO18.RunInterup!=0){SmqttPUB(valueToMqttMsg(IO18),IO18.Uname);}
            if(IO19.RunInterup!=0){SmqttPUB(valueToMqttMsg(IO19),IO19.Uname);}
            
            if(IO25.RunInterup!=0){SmqttPUB(valueToMqttMsg(IO25),IO25.Uname);}
            if(IO26.RunInterup!=0){SmqttPUB(valueToMqttMsg(IO26),IO26.Uname);}
            if(IO27.RunInterup!=0){SmqttPUB(valueToMqttMsg(IO27),IO27.Uname);}
            if(IO32.RunInterup!=0){SmqttPUB(valueToMqttMsg(IO32),IO32.Uname);}
            if(IO33.RunInterup!=0){SmqttPUB(valueToMqttMsg(IO33),IO33.Uname);}
            if(IO34.RunInterup!=0){SmqttPUB(valueToMqttMsg(IO34),IO34.Uname);}
            if(IO35.RunInterup!=0){SmqttPUB(valueToMqttMsg(IO35),IO35.Uname);}
            if(IO36.RunInterup!=0){SmqttPUB(valueToMqttMsg(IO36),IO36.Uname);}
            if(IO39.RunInterup!=0){SmqttPUB(valueToMqttMsg(IO39),IO39.Uname);}
          
          }
    intruptMsgFlag=0;
    intruptMsg=millis()+1000;
  }
  
  if(intruptMsgFlag==1 && intruptMsg>millis()){intruptMsgFlag=0;}
  
}


 ///////////////////////////////////////////////////////////////////////////////////////////////////////////IO Setup
void IRAM_ATTR isr() {
   intruptMsgFlag=1;
  Serial.println("isrC");
  }


void ioSET(gpio IO){
  if(IO.IOset==0){pinMode(IO.pin, INPUT);}
  if(IO.IOset==1 && IO.ADC==0){pinMode(IO.pin, OUTPUT); digitalWrite(IO.pin, IO.IOstaet);}
  if(IO.IOset==2 && IO.ADC==0){pinMode(IO.pin, INPUT_PULLUP);}
}


struct gpio Setup4pin(gpio IO){
    ledcDetachPin(IO.pin);
   
    if(IO.RunInterup ==0){
      if(IO.type==0){ioSET(IO);}
      else if(IO.type==1 && IO.ADC==0){IO=pwmsetup(IO);}
      else if(IO.type==2 && IO.Touch==true){}
      else if(IO.type==6 && IO.ADC==true){pinMode(IO.pin, INPUT);}
    }

    if(IO.RunInterup !=0 && IO.type==1 && IO.RunInterup !=6){IO.type=0;}
    

    if(IO.RunInterup ==1){  
      if(IO.IOset==0){pinMode(IO.pin, INPUT);}
      if(IO.IOset==2){pinMode(IO.pin, INPUT_PULLUP);}
      if(IO.IOset==1){IO.IOset=0;pinMode(IO.pin, INPUT);}
      attachInterrupt(digitalPinToInterrupt(IO.pin), isr, CHANGE);
      }
  
    if(IO.RunInterup ==2){
      if(IO.IOset==0){pinMode(IO.pin, INPUT);}
      if(IO.IOset==2){pinMode(IO.pin, INPUT_PULLUP);}
      if(IO.IOset==1){IO.IOset=0;pinMode(IO.pin, INPUT);}
     // IO.IOset=0;pinMode(IO.pin, INPUT);
      attachInterrupt(digitalPinToInterrupt(IO.pin), isr, RISING);
      }
    if(IO.RunInterup ==3){
      IO.IOset=2;
      pinMode(IO.pin, INPUT_PULLUP);
      attachInterrupt(digitalPinToInterrupt(IO.pin), isr, FALLING);
      }
    if(IO.RunInterup ==4 && IO.Touch==true){
      IO.type=2;
      if(IO.pin==2){touchAttachInterrupt(T2, isr, IO.TouchTHRESHOLD);}
      if(IO.pin==4){touchAttachInterrupt(T0, isr, IO.TouchTHRESHOLD);}
      if(IO.pin==27){touchAttachInterrupt(T7, isr, IO.TouchTHRESHOLD);}
      if(IO.pin==12){touchAttachInterrupt(T5, isr, IO.TouchTHRESHOLD);}
      if(IO.pin==13){touchAttachInterrupt(T4, isr, IO.TouchTHRESHOLD);}
      if(IO.pin==14){touchAttachInterrupt(T6, isr, IO.TouchTHRESHOLD);}
      if(IO.pin==15){touchAttachInterrupt(T3, isr, IO.TouchTHRESHOLD);}
      if(IO.pin==32){touchAttachInterrupt(T9, isr, IO.TouchTHRESHOLD);}
      if(IO.pin==33){touchAttachInterrupt(T8, isr, IO.TouchTHRESHOLD);}
      }
    return IO;
  }




void AllPinSetup(){
  
 IO2.pin=2;   IO2.interupNum=4;  IO2.Touch=true; IO2.ClockNum=1; IO2.TouchNum=2; IO2=GetIoMemory(IO2);
  IO4.pin=4;   IO4.interupNum=16; IO4.Touch=true; IO4.ClockNum=9; IO4.TouchNum=0;IO4=GetIoMemory(IO4);
  IO5.pin=5;   IO5.interupNum=32;IO5.ClockNum=10;IO5=GetIoMemory(IO5);
  //  //////////////////////////////////////////////////////////////////////////SPI
  IO12.pin=12; IO12.interupNum=4096;  IO12.Touch=true; IO12.spi=true; IO12.ClockNum=12; IO12.TouchNum=5;IO12=GetIoMemory(IO12);
  IO13.pin=13; IO13.interupNum=8192;  IO13.Touch=true; IO13.spi=true; IO13.ClockNum=13; IO13.TouchNum=4;IO13=GetIoMemory(IO13);
  IO14.pin=14; IO14.interupNum=16384; IO14.Touch=true; IO14.spi=true; IO14.ClockNum=14; IO14.TouchNum=6;IO14=GetIoMemory(IO14);
  IO15.pin=15; IO15.interupNum=32768; IO15.Touch=true; IO15.spi=true; IO15.ClockNum=15; IO15.TouchNum=3;IO15=GetIoMemory(IO15);
  IO16.pin=16; IO16.interupNum=65536; IO16.ClockNum=3;IO16=GetIoMemory(IO16);
  IO17.pin=17; IO17.interupNum=131072; IO17.ClockNum=4;IO17=GetIoMemory(IO17);
  IO18.pin=18; IO18.interupNum=262144; IO18.ClockNum=0; IO18=GetIoMemory(IO18);
  IO19.pin=19; IO19.interupNum=524288; IO19.ClockNum=11; IO19=GetIoMemory(IO19);
  IO25.pin=25; IO25.interupNum=33554432; IO25.ClockNum=5;IO25=GetIoMemory(IO25);
  IO26.pin=26; IO26.interupNum=67108864; IO26.ClockNum=6;IO26=GetIoMemory(IO26);
  IO27.pin=27; IO27.interupNum=134217728; IO27.Touch=true; IO27.ClockNum=7; IO27.TouchNum=7;IO27=GetIoMemory(IO27);
 //  //////////////////////////////////////////////////////////////////////////ADC
  IO32.pin=32; IO32.ADC=true; IO32.interupNum=32768; IO32.Touch=true;  IO32.TouchNum=9;IO32=GetIoMemory(IO32);
  IO33.pin=33; IO33.ADC=true; IO33.interupNum=32768; IO33.Touch=true;  IO33.TouchNum=8;IO33=GetIoMemory(IO33);
  IO34.pin=34; IO34.ADC=true; IO34.interupNum=32768; IO34=GetIoMemory(IO34);
  IO35.pin=35; IO35.ADC=true; IO35.interupNum=32768; IO35=GetIoMemory(IO35);
  IO36.pin=36; IO36.ADC=true; IO36.interupNum=32768; IO36=GetIoMemory(IO36);
  IO39.pin=39; IO39.ADC=true; IO39.interupNum=32768; IO39=GetIoMemory(IO39);

 //dubgIO(IO18);

IO2=Setup4pin(IO2);
IO4=Setup4pin(IO4);
IO5=Setup4pin(IO5);
IO16=Setup4pin(IO16);
IO17=Setup4pin(IO17);
IO25=Setup4pin(IO25);
IO26=Setup4pin(IO26);
IO27=Setup4pin(IO27);
IO19=Setup4pin(IO19);
IO18=Setup4pin(IO18);

IO12=Setup4pin(IO12);
IO13=Setup4pin(IO13);
IO14=Setup4pin(IO14);
IO15=Setup4pin(IO15);
IO32=Setup4pin(IO32);
IO33=Setup4pin(IO33);
IO34=Setup4pin(IO34);
IO35=Setup4pin(IO35);
IO36=Setup4pin(IO36);
IO39=Setup4pin(IO39);
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
