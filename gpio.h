/////////////////////////////////////////////////////////////////////////////////////////////
struct gpio GetIoMemory(gpio IO){
  String phte="/";
  phte+=String(IO.pin);
  phte+="GPIO.txt";
  File file = FILESYSTEM.open(phte);
  StaticJsonDocument<700> doc;
  DeserializationError error = deserializeJson(doc, file);
  if (error){Serial.println(error.c_str());}
 
  String XX="IO"+String(IO.pin);
  
  IO.Uname=doc["pinNum"] | XX;
  IO.IOset=doc["IOset"] | 0;
  IO.type=doc["type"] | 0;
  IO.interup=doc["interup"] | 0;
  IO.RunInterup=doc["RunInterup"] | 0;
 
 if(IO.ADC==0){ 
  IO.IOstaet=doc["IOstaet"] | false;
  IO.PwM=doc["PwM"] | 0;
  IO.MaxDute=doc["IO.MaxDute"] | 8191;
  IO.Hz=doc["Hz"] | 5000;
  IO.Bit=doc["Bit"] | 13;
 }
 
  if(IO.Touch==1){
  IO.TouchTHRESHOLD=doc["TouchTHRESHOLD"] | 40;
  }
  if(IO.ADC==1){
  IO.AdcMax=doc["AdcMax"] | 0;
  IO.AdcMin=doc["AdcMin"] | 0;
  }
  file.close();
   return IO;
  }

bool SetIoMemory(gpio IO){
     String phte="/";
  phte+=String(IO.pin);
  phte+="GPIO.txt";
  FILESYSTEM.remove(phte);
  File file = FILESYSTEM.open(phte, FILE_WRITE);
  if (!file) {Serial.println(F("Failed to create file")); return 0; }
  StaticJsonDocument<700> doc;
  
  doc["pinNum"]=IO.Uname;
  doc["IOset"]=IO.IOset;
  doc["type"]= IO.type ;
  doc["interup"]= IO.interup ;
  doc["RunInterup"]=IO.RunInterup ;
  
 if(IO.ADC==0){ 
  doc["IOstaet"]=IO.IOstaet;
  doc["PwM"]=IO.PwM ;
  doc["IO.MaxDute"]=IO.MaxDute;
  doc["Hz"]= IO.Hz;
  doc["Bit"]= IO.Bit;
  }
 if(IO.Touch==1){
  doc["TouchTHRESHOLD"]=IO.TouchTHRESHOLD;
    }
 if(IO.ADC==1){
  doc["AdcMax"]=IO.AdcMax;
  doc["AdcMin"]=IO.AdcMin;
    }
  if (serializeJson(doc, file) == 0) {
    Serial.println(F("Failed to write to file"));
  }

  file.close();
  return 1;
  }


///////////////////////////////////////////////////////////////////////////////
void chingIO(gpio IO , int XI){
  if(IO.IOset == 1 && IO.type == 0){
   if(XI==1 || XI==0){
     digitalWrite(IO.pin, XI);
     if(XI==1){IO.IOstaet=1;}else{IO.IOstaet=0;}
     SetIoMemory(IO);
    } 
   }
 }
////////////////////////////////////////////////////////////////////////////////////
struct gpio GetAdcVlue(gpio IO){
    if(IO.type==6 && IO.ADC==1){IO.AdcVal=analogRead(IO.pin);}
  return IO;
}
////////////////////////////////////////////////////////////////////////////////
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

///////////////////////////////////////////////////////////////////////////////
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


void setAdcVlue(){
IO32=GetAdcVlue(IO32);
IO33=GetAdcVlue(IO33);
IO34=GetAdcVlue(IO34);
IO35=GetAdcVlue(IO35);
IO36=GetAdcVlue(IO36);
IO39=GetAdcVlue(IO39);
}
/////////////////////////////////////////////////////////////////////////////
void chingpwm(gpio IO, double XX){
  if(IO.type == 1){
     if(XX>=0 && XX<IO.MaxDute){IO.PwM=XX;} 
     else{IO.PwM=IO.MaxDute;}
     ledcWrite(IO.ClockNum,IO.PwM);
     SetIoMemory(IO);
  }
}
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
