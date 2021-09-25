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

////////////////////////////////////////PWM
//In such a case you can calculate duty resolution as: integer (log 2 (LEDC_APB_CLK / frequency)).
//For example, for 20kHz PWM frequency:
//* 80 MHz / 20 kHz = 4000
//* log 2 (4000) = 11.965...
//* integer(11.96) = 11 bits
//If you like to get 12 bits, then slightly lower PWM frequency from 20 kHz to 80 MHz / 2^12 = 19.531 kHz
//16=65535/15=32767/14=16383/13=8191/12=4095/11=2047/10=1023/9=511/8=255/7=127/6=63/5=31/4=15/3=7/2=3/1=1

int HzToBit(double HZ){
  int BIT=(log(80000000 / HZ)/log(2));
  if(BIT>16){BIT=16;}
  if(BIT<2){BIT=2;}
  return BIT;
}

double setmaxPWM(int X){
  double pwmax;
  if(X==16){pwmax=65535;}
  if(X==15){pwmax=32767;}
  if(X==14){pwmax=16383;}
  if(X==13){pwmax=8191;}
  if(X==12){pwmax=4095;}
  if(X==11){pwmax=2047;}
  if(X==10){pwmax=1023;}
  if(X==9){pwmax=511;}
  if(X==8){pwmax=255;}
  if(X==7){pwmax=127;}
  if(X==6){pwmax=63;}
  if(X==5){pwmax=31;}
  if(X==4){pwmax=15;}
  if(X==3){pwmax=7;}
  if(X==2){pwmax=3;}
  return pwmax;
}

struct gpio pwmsetup(gpio IO){
  if(IO.Hz>20000000){IO.Hz=20000000;}
   int X=HzToBit(IO.Hz);
   if(IO.Bit>X){IO.Bit=X;}
  IO.MaxDute=setmaxPWM(X);
  ledcSetup(IO.ClockNum, IO.Hz, IO.Bit);
    ledcAttachPin(IO.pin,IO.ClockNum);
  ledcWrite(IO.ClockNum, IO.PwM);
  return IO;
}

void dubgIO(gpio IO){
  Serial.print("IO2.pin=");Serial.println(IO.pin);
  Serial.print("IO2.RunInterup=");Serial.println(IO.RunInterup);
  Serial.print("IO2.function=");Serial.println(String(IO.Touch)+String(IO.spi));
  Serial.print("IO2.ClockNum=");Serial.println(IO.ClockNum);
  Serial.print("IO2.type=");Serial.println(IO.type);
  Serial.print("IO2.IOset=");Serial.println(IO.IOset);
  Serial.print("IO2.IOstaet=");Serial.println(IO.IOstaet);
  Serial.print("IO2.PwM=");Serial.println(IO.PwM);
  Serial.print("IO2.MaxDute=");Serial.println(IO.MaxDute);
  Serial.print("IO2.Hz=");Serial.println(IO.Hz);
 
}

////////////////////////////////////////////////////////////////////////////////////////////
