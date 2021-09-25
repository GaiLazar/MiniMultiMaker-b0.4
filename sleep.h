/*
NOTE:
======
Only RTC IO can be used as a source for external wake
source. They are pins: 0,2,4,12-15,25-27,32-39.

Author:
Pranav Cherukupalli <cherukupallip@gmail.com>
*/

#define BUTTON_PIN_BITMASK 0x200000000 // 2^33 in hex
touch_pad_t touchPin;

#define uS_TO_S_FACTOR 1000000  /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP  5        /* Time ESP32 will go to sleep (in seconds) */


void print_wakeup_reason(){
  esp_sleep_wakeup_cause_t wakeup_reason;
  wakeup_reason = esp_sleep_get_wakeup_cause();
  switch(wakeup_reason)
  {
    case ESP_SLEEP_WAKEUP_EXT0 : WakeupIOres="Wakeup caused by external signal using RTC_IO"; break;
    case ESP_SLEEP_WAKEUP_EXT1 : WakeupIOres="Wakeup caused by external signal using RTC_CNTL"; break;
    case ESP_SLEEP_WAKEUP_TIMER : WakeupIOres="Wakeup caused by timer"; break;
    case ESP_SLEEP_WAKEUP_TOUCHPAD : WakeupIOres="Wakeup caused by touchpad"; break;
    case ESP_SLEEP_WAKEUP_ULP : WakeupIOres="Wakeup caused by ULP program"; break;
    default : WakeupIOres="Wakeup was not caused by deep sleep"; break;
    // default : WakeupIOres="Wakeup was not caused by deep sleep: %d\n",wakeup_reason; break;
  }
}

void print_wakeup_touchpad(){
  touch_pad_t pin;

  touchPin = esp_sleep_get_touchpad_wakeup_status();

  switch(touchPin)
  {
    case 0  : WakeupTouchPad="Touch detected on GPIO 4"; break;
    case 1  : WakeupTouchPad="Touch detected on GPIO 0"; break;
    case 2  : WakeupTouchPad="Touch detected on GPIO 2"; break;
    case 3  : WakeupTouchPad="Touch detected on GPIO 15"; break;
    case 4  : WakeupTouchPad="Touch detected on GPIO 13"; break;
    case 5  : WakeupTouchPad="Touch detected on GPIO 12"; break;
    case 6  : WakeupTouchPad="Touch detected on GPIO 14"; break;
    case 7  : WakeupTouchPad="Touch detected on GPIO 27"; break;
    case 8  : WakeupTouchPad="Touch detected on GPIO 33"; break;
    case 9  : WakeupTouchPad="Touch detected on GPIO 32"; break;
    default : WakeupTouchPad="Wakeup not by touchpad"; break;
  }
}

void callback(){
  //placeholder callback function
}


void SleepButtonSetup(){
  //esp_sleep_enable_ext0_wakeup(GPIO_NUM_33,1); //1 = High, 0 = Low
  //If you were to use ext1, you would use it like
  unsigned long xxx=0;
  bool ioWekUp=0;
  bool tuchWekUp=0;
  if(IO2.interup==1){xxx+=IO2.interupNum;ioWekUp=1;}
  if(IO4.interup==1){xxx+=IO4.interupNum;ioWekUp=1;}
  if(IO12.interup==1){xxx+=IO12.interupNum;ioWekUp=1;}
  if(IO13.interup==1){xxx+=IO13.interupNum;ioWekUp=1;}
  if(IO14.interup==1){xxx+=IO14.interupNum;ioWekUp=1;}
  if(IO15.interup==1){xxx+=IO15.interupNum;ioWekUp=1;}
  if(IO25.interup==1){xxx+=IO25.interupNum;ioWekUp=1;}
  if(IO26.interup==1){xxx+=IO26.interupNum;ioWekUp=1;}
  if(IO27.interup==1){xxx+=IO27.interupNum;ioWekUp=1;}
  
  if(IO2.interup==2){touchAttachInterrupt(T2, callback, 40);tuchWekUp=1;}
  if(IO4.interup==2){touchAttachInterrupt(T0, callback, 40);tuchWekUp=1;}
  if(IO12.interup==2){touchAttachInterrupt(T5, callback, 40);tuchWekUp=1;}
  if(IO13.interup==2){touchAttachInterrupt(T4, callback, 40);tuchWekUp=1;}
  if(IO14.interup==2){touchAttachInterrupt(T6, callback, 40);tuchWekUp=1;}
  if(IO15.interup==2){touchAttachInterrupt(T3, callback, 40);tuchWekUp=1;}
  if(IO27.interup==2){touchAttachInterrupt(T7, callback, 40);tuchWekUp=1;}

  if(ioWekUp==1){esp_sleep_enable_ext1_wakeup(xxx,ESP_EXT1_WAKEUP_ANY_HIGH);}
  
 if(tuchWekUp==1){esp_sleep_enable_touchpad_wakeup();} 
 
}

void SleepTimerSetup(){
  esp_sleep_enable_timer_wakeup(TimeOfSleep);
  Serial.println("Setup ESP32 to sleep for every " + String((TimeOfSleep/1000000)/60) +
  " M");
  //esp_deep_sleep_pd_config(ESP_PD_DOMAIN_RTC_PERIPH, ESP_PD_OPTION_OFF);
  //Serial.println("Configured all RTC Peripherals to be powered down in sleep");

}

void GotoSleep(){
   esp_deep_sleep_start();
}


void SleepMode(bool X){
  TimerInterup=X;
  TempoFlag=X;
 SAVEconfig();
}

void sleeper(){
  if(TimerInterup){
     Serial.print("enter sleep mode");
    if(ButtonInterup){SleepButtonSetup();}
     SleepTimerSetup();
     GotoSleep();
    }

}
