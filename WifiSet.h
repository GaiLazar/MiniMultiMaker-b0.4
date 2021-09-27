
void getssidlist() {
  //WiFi.mode(WIFI_MODE_STA);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  int n = WiFi.scanNetworks();
  Serial.println("");
  
  for (int i = 0; i < n; ++i) {
    ssidList += "<option value=\"";
    ssidList += WiFi.SSID(i);
    ssidList += "\">";
    ssidList += WiFi.SSID(i);
    ssidList += "</option>";
  }
   //Serial.println(ssidList);
  // setupSTAmode();
 
}


   void setupAPmode() {
  getssidlist();
  delay(100);
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP(apSSID.c_str(),ApPasword.c_str());
  
   //WiFi.mode(WIFI_MODE_AP);
  // WiFi.softAPConfig(IPAddress local_ip, IPAddress gateway, IPAddress subnet);
  // WiFi.softAP(const char* ssid, const char* passphrase = NULL, int channel = 1, int ssid_hidden = 0);
//   dnsServer.start(53, "*", apIP);
  Serial.print("Starting Access Point at \"");
  Serial.print(apSSID);
  Serial.println("\"");
  Serial.print("IP = ");
  Serial.println(apIP);

 if (!MDNS.begin(host.c_str())){Serial.println("Error setting up MDNS responder!");}
   MDNS.addService("http", "tcp", 80);
  Serial.print("Open http://");
  Serial.print(host);
  Serial.println(".local/edit to see the file browser");
}



void setupSTAmode(){
    getssidlist();
    Serial.print("Connecting to ");
    Serial.println(wifi_ssid);
    WiFi.begin(wifi_ssid.c_str(),wifi_password.c_str());
   
   int count=0;
   while (WiFi.status() != WL_CONNECTED && count!=20) {
    delay(500);
    Serial.print(".");
    count++;
   }
  
  if(WiFi.status() != WL_CONNECTED){
    settingMode = true;
    SAVEconfig();
    NETstatus=0;
    setupAPmode();
    }
    else{
      settingMode = false;
     // SAVEconfig();
      NETstatus=1;
     
  Serial.println("");
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());

  if (!MDNS.begin(host.c_str())){Serial.println("Error setting up MDNS responder!");}
   MDNS.addService("http", "tcp", 80);
  Serial.print("Open http://");
  Serial.print(host);
  Serial.println(".local/");
 }
 
}
