
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
