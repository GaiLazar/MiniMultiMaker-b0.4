
#include <PubSubClient.h>
WiFiClient espClient;
PubSubClient client(espClient);

long lastMsg = 0;
char msg[100];
char ttopic[100];
int value = 0;



void callback(char* topic, byte* payload, unsigned int length) {
  //Serial.print("Message arrived [");
 // Serial.print(topic);
 // Serial.print("] ");
  MqttMssege+=String(topic);
  MqttMssege+=" : ";
  for (int i = 0; i < length; i++) {
    //Serial.print((char)payload[i]);
    MqttMssege+=(char)payload[i];
  }
  MqttMssege+="\r\n";
  Serial.println();
  Serial.println(MqttMssege);

if(mqttOnSocket==1 && MqttMssege!="" ){
    MqttMssege="--*mqtt*-- "+MqttMssege;
    webSocket.sendTXT(outnum, MqttMssege);
    MqttMssege="";
    }

}

bool reconnect() {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect(clientId.c_str(), username.c_str(), userpass.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish(outTopic.c_str(), msg);
      // ... and resubscribe
      client.subscribe(inTopic.c_str());
      MqttTimerCountrer=0;
      mqttConnection=1;
      return 1;
    } else {
      MqttTimerCountrer++;
      Serial.println(" MQTT faild to connect...");
      if(MqttTimerCountrer >= 3){mqttOnOff=0;}
      mqttConnection=0;
      return 0;
    }
}


bool SmqttPUB(String messg,String names){
    String topic=outTopic;
    topic+="/";
    topic+=names;
    messg.toCharArray(msg, 100);
    topic.toCharArray(ttopic, 100);
  
  if (!client.connected()) {reconnect();}
  else{
     client.publish(ttopic, msg);
     return 1;
    }
}

bool XmqttPUB(String messg,String names){
    String topic=outTopic;
    messg=names+"="+messg;
    messg.toCharArray(msg, 100);
    topic.toCharArray(ttopic, 100);
  
  if (!client.connected()) {reconnect();}
  else{
     client.publish(ttopic, msg);
     return 1;
    }
}
//
// struct gpio MqttSETmsg(gpio IO){
//  if(IO.type==0){IO.IOstaet=digitalRead(IO.pin);SmqttPUB(String(IO.IOstaet),IO.Uname);}
//  if(IO.type==1){SmqttPUB(String(IO.PwM),IO.Uname);}
//  if(IO.type==2){setTouchVlue();SmqttPUB(String(IO.TouchVlue),IO.Uname);}
//  if(IO.type==6){GetAdcVlue(IO);SmqttPUB(String(IO.AdcVal),IO.Uname);}
//  return IO;
//}
//
//void MqttSendAll(){
//  IO2=MqttSETmsg(IO2);
//  IO2=MqttSETmsg(IO4);
//  IO2=MqttSETmsg(IO5);
//  IO2=MqttSETmsg(IO12);
//  IO2=MqttSETmsg(IO13);
//  IO2=MqttSETmsg(IO14);
//  IO2=MqttSETmsg(IO15);
//  IO2=MqttSETmsg(IO16);
//  IO2=MqttSETmsg(IO17);
//  IO2=MqttSETmsg(IO18);
//  IO2=MqttSETmsg(IO19);
//  IO2=MqttSETmsg(IO21);
//  IO2=MqttSETmsg(IO25);
//  IO2=MqttSETmsg(IO26);
//  IO2=MqttSETmsg(IO27);
//  
//}
//


bool mqttPUB(String messg){
    // topic=outTopic+"/"+topic;
   // messg.toCharArray(msg, 100);
   // outTopic.toCharArray(ttopic, 100);
  
  if (!client.connected()) {reconnect(); return 1;}
  else{

     Serial.print("Publish topic: ");
    Serial.println(ttopic);
    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish(outTopic.c_str(), messg.c_str());
     return 1;
  client.loop();
 
  }
}

void MqttSetup(){
  client.setServer(mqtt_server.c_str(), port);
  client.setCallback(callback);
 // reconnect();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
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
