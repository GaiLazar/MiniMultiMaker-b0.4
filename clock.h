#include "time.h"

const int   daylightOffset_sec = 3600;
String Rtime;
String Rdate;
String Rday;
struct tm timeinfo;

void printLocalTime()
{
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
  Rdate=timeinfo.tm_mday;
  Rdate+="/";
  Rdate+=timeinfo.tm_mon+1;
//  Rdate+="/";
//  Rdate+=timeinfo.tm_year-100;

  Rtime=timeinfo.tm_hour;
  Rtime+=":";
  if(timeinfo.tm_min<10){  Rtime+="0";}
  Rtime+=timeinfo.tm_min;
//  Rtime+=":";
//  Rtime+=timeinfo.tm_sec;  
  
  switch (timeinfo.tm_wday) {
  case 0:
    Rday="SUN";
    break;
  case 1:
    Rday="MON";
    break;
    case 2:
    Rday="TUE";
    break;
    case 3:
    Rday="WED";
    break;
    case 4:
    Rday="THU";
    break;
    case 5:
    Rday="FRI";
    break;
    case 6:
    Rday="SAT";
    break;
  default:
    Rday="";
    break;
}
  
NETstatus=2;
   
//   
//   timeinfo.tm_mday
//   timeinfo.tm_mon
//   timeinfo.tm_year
//   
//   timeinfo.tm_wday
//   timeinfo.tm_yday
//   timeinfo.tm_isdst
}

void getNTPtime(){
 configTime(gmtOffset_sec, daylightOffset_sec, ntpServer.c_str());
 printLocalTime();
}
