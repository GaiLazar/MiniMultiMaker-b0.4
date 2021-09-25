///////////////////////////////////////////////////////////////////i2c
 

void i2cScan(){
  i2cscan="";
  byte error, address;
  int nDevices=0;
 // Serial.println("Scanning...");
  nDevices = 0;
  for(address = 1; address < 127; address++ ) 
  {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    
    if (error == 0)
    {
      
      if(nDevices==1){
        //i2cscan+="\"device";
        }
        else{
          i2cscan+=",";
          }
      //i2cscan+=String(nDevices);
      i2cscan+=" \"0x";
      if (address<16) 
      delay(5);
      i2cscan+=String(address,HEX);
      i2cscan+="\""; 
      nDevices++;

    }
    else if (error==4) 
    {
      if (address<16) 
      delay(5);
      i2cscan+="0";
      i2cscan+=String(address,HEX);
    }    
  }
  if (nDevices == 0){
    i2cscan= ",\"i2cScan\":\"No I2C devices found\"";
   i2cscanResolt=0;
    }
  else{
    i2cscan+="]";
    i2cscan=",\"i2cScan\":[" + i2cscan + "]";
    i2cscanResolt=nDevices;
    }
     Serial.println(i2cscanResolt);
     Serial.println(i2cscan);
}
