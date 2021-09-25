void setSerial(){
  if(buad!=0){serial=true;}else{serial=false;}
  if(buad==1){Serial.begin(300);}
  if(buad==2){Serial.begin(1200);}
  if(buad==3){Serial.begin(2400);}
  if(buad==4){Serial.begin(4800);}
  if(buad==5){Serial.begin(9600);}
  if(buad==6){Serial.begin(19200);}
  if(buad==7){Serial.begin(38400);}
  if(buad==8){Serial.begin(57600);}
  if(buad==9){Serial.begin(74880);}
  if(buad==10){Serial.begin(115200);}
  if(buad==11){Serial.begin(230400);}
  if(buad==12){Serial.begin(250000);}
}

void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    SerialRX += inChar;
  }
  
  if(seralOnSocket==1 && SerialRX!="" ){
    SerialRX="--*serial*-- "+SerialRX;
    webSocket.sendTXT(outnum, SerialRX);
    SerialRX="";
    }
  
}
