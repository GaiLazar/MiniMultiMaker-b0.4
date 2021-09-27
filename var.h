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

struct gpio {
  int pin=0;
  String Uname="IO";
  bool Touch=0;
  bool spi=0;
  bool ADC=0;
  int  ClockNum;
  long interupNum=0;
  
  int interup=0; //waekup from sleep 0=OFF 1=IO 2=TOUCH
  int RunInterup=0;//0=OFF  1=CHANGE 2=RISING 3=FALLING 4=TOUCH 
  
  int type=0;//0=IO 1=PWM 2=Touch 3=spi 4=uarta 5=i2c 6=ADC
  
  int  IOset=0;//0=input 1=output 2=inputPULLUP 
  bool IOstaet=0;
  
  double PwM=0;
  double MaxDute = 8191;
  double Hz = 5000;
  int Bit= 13;
  
  int TouchTHRESHOLD=40;
  int TouchNum;
  double TouchVlue=0;
  
  long AdcVal=0;
  long AdcMax=0;
  long AdcMin=0;
   
};

struct gpio IO2,IO4,IO5,IO16,IO17,IO25,IO26,IO27,IO18,IO19,IO12,IO13,IO14,IO15,IO32,IO33,IO34,IO35,IO36,IO39;
