//////////////////////////////////////////global
const IPAddress apIP(192, 168, 4, 1);
boolean settingMode;
int NETstatus=0;
String ssidList;
long mmm;
///////////////////////////////////////wifi config
String wifi_ssid;
String wifi_password;
String apSSID = "ESP32_SETUP";
String ApPasword="password";
String host = "esp32fs";
String HostUserName="user";
String HostPasword="password";
////////////////////////////////////////////////mqtt config
bool mqttOnOff=0;
bool MQttRiperOnOff=0;
int MqttrRipet=10;
long MqttRipetM=0;
bool MqttMsgOnWekup=0;
String mqtt_server = "broker.mqtt-dashboard.com";
long port=1883;
String username="";
String userpass="";
String clientId = "ESP32Client";
String inTopic="inTopic";
String outTopic="outTopic";

//String time_of_sleep_m="0"; ///mqttRepetTimer
bool mqttConnection=0;
String MqttMssege;
bool mqttOnSocket=0;
long MqttTimer=0;
int MqttTimerCountrer=0;

bool intruptMsgFlag=0;
long intruptMsg=0; ///time bitwin messeges
bool mqttferstmsg=0;
////////////////////////////////////////////////////serial
bool serial;
int buad=10;
String SerialRX;
bool seralOnSocket=0;
uint8_t outnum;
////////////////////////////////////////////////////I2C
int i2cscanResolt=0;
String i2cscan;
String I2Cmsg;
////////////////////////////////////////////////////sleep config
bool TimerInterup=0;
bool TempoFlag=0;
bool ButtonInterup=0;
long TimeOfSleep=0;///// deepsleep
String WakeupTouchPad;
String WakeupIOres;
//////////////////////////////////////////////////// config
bool uarta=1;
bool i2c=1;
bool spi=0;
/////////////////////////////////////////////////////ntp clock
String ntpServer = "pool.ntp.org";
 long  gmtOffset_sec = 7200;  //3600=60min
////////////////////////////////////////////////////////////////////////////////////////////////////////

//Check if header is present and correct
bool is_authentified() {
  //Serial.println("Enter is_authentified");
  if (server.hasHeader("Cookie")) {
  //  Serial.print("Found cookie: ");
    String cookie = server.header("Cookie");
  //  Serial.println(cookie);
    if (cookie.indexOf("ESPSESSIONID=1") != -1) {
  //    Serial.println("Authentification Successful");
      return true;
    }
  }
 // Serial.println("Authentification Failed");
  return false;
}

//login page, also called for disconnect
void handleLogin() {
  String msg;
  if (server.hasHeader("Cookie")) {
    //Serial.print("Found cookie: ");
    String cookie = server.header("Cookie");
  //  Serial.println(cookie);
  }
  if (server.hasArg("DISCONNECT")) {
    //Serial.println("Disconnection");
    server.sendHeader("Location", "/login");
    server.sendHeader("Cache-Control", "no-cache");
    server.sendHeader("Set-Cookie", "ESPSESSIONID=0");
    server.send(301);
    return;
  }
  if (server.hasArg("USERNAME") && server.hasArg("PASSWORD")) {
    if (server.arg("USERNAME") == HostUserName &&  server.arg("PASSWORD") == HostPasword) {
      server.sendHeader("Location", "/");
      server.sendHeader("Cache-Control", "no-cache");
      server.sendHeader("Set-Cookie", "ESPSESSIONID=1");
      server.send(301);
    //  Serial.println("Log in Successful");
      return;
    }
    msg = "Wrong username/password! try again.";
   // Serial.println("Log in Failed");
  }

 String content ="<html><title>Multi Mini Maker</title>";
content +="<meta name=\"viewport\" content=\"width=device-width,initial-scale=1\">";
content +="<style>html,body,h1,h2,h3,h4,h5 {font-family: \"Raleway\", sans-serif}</style>";
content +="<body style=\"text-align: center; background-color: #f1f1f1;\">";
content +="<h1 style=\"background-color:black; color:white; padding: 8px;\"><b>Mini Multi Maker</b></h1>";
content +="<br><div style=\"text-align: center; width: 350px; margin: auto;\" >To log in, please use : User/password<br><br>";
content +="<form action='/login' method='POST'><table style=\"margin: auto;\" ><tr><th>User:</th>";
content +="<td><input type='text' name='USERNAME' placeholder='user name'></td></tr><tr>";
content +="<th>Password:</th><td><input type='password' name='PASSWORD' placeholder='password'></td>";
content +="</tr></table><br><input type='submit' name='SUBMIT' value='Submit'></form><br>";
content += msg ;
content +="</div></body></html>";

  server.send(200, "text/html", content);
}
