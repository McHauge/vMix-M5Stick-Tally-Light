void loadSettings()
{
  preferences.begin("vMixTally", false);
  
  if (preferences.getString("wifi_ssid").length() > 0)
  {
    Serial.println("LOADING FROM PREFERENCES, OVERRIDING HARDCODED VARIABLES");
    WIFI_SSID = preferences.getString("wifi_ssid");
    WIFI_PASS = preferences.getString("wifi_pass");
  }
  else
  {
      Serial.println("Use hardcoded settings here");
      saveWiFiPreferences(&(WIFI_SSID[0]), &(WIFI_PASS[0]));
  }
  
  if(preferences.getString("vmix_ip").length() > 0){
    TALLY_NR = preferences.getUInt("tally");
    VMIX_IP = preferences.getString("vmix_ip");
    if(TALLY_NR > 9){
      tnlen = 2;
    }
  }

  CONN_INT = preferences.getUInt("connint", CONN_INT) ;
  MODE = preferences.getUInt("mode") || MODE;
  PM_MODE = preferences.getUInt("pmmode", PM_MODE);
  PM_COLOR = preferences.getUInt("pmcolor", PM_COLOR);
  JUSTLIVE = preferences.getUInt("justLive") || JUSTLIVE;
  VMIX_CUSTOM_ENABLE = preferences.getUInt("customenable") || VMIX_CUSTOM_ENABLE;
  VMIX_CUSTOM_PORT = preferences.getUInt("vmixcustomport", VMIX_CUSTOM_PORT);
  Serial.print("PUT CONN INT: ");
  Serial.println(CONN_INT);


  if(preferences.getString("m_tally").length() > 0){
    M_TALLY = preferences.getString("m_tally");
  }

  Serial.println(preferences.getUInt("bright"));

  if(preferences.getUInt("bright")){
    BRIGHTNESS = preferences.getUInt("bright");
    M5.Axp.ScreenBreath(BRIGHTNESS);
    setPluginBrightness();
  }
  preferences.end();
}

void saveWiFiPreferences(String wifi_ssid, String wifi_pass)
{
    preferences.begin("vMixTally", false);
    if (wifi_ssid != "")
    {
        preferences.putString("wifi_ssid", wifi_ssid);
        preferences.putString("wifi_pass", wifi_pass);
    }
    preferences.end();
    WIFI_SSID = wifi_ssid;
    WIFI_PASS = wifi_pass;
}

void resetSettings(){
  preferences.begin("vMixTally", false);
  
  preferences.putString("wifi_ssid", "");
  preferences.putString("wifi_pass", "");
  preferences.putString("vmix_ip", "");
  preferences.putUInt("tally", 1);
  preferences.putUInt("bright", 13);
  preferences.putString("m_tally", "");
  preferences.putUInt("customenable", 0);
  preferences.putUInt("vmixcustomport", 8099);
  preferences.putUInt("pmmode", 0);
  preferences.putUInt("pmcolor", 0);
  
  preferences.end();

  Serial.println("Settings are reset");
  resetScreen();
  M5.Lcd.println("Settings are reset");
  M5.Lcd.println();
  M5.Lcd.println("Please reboot device");
}

void increaseTally(){
  TALLY_NR++;
  preferences.begin("vMixTally", false);
  preferences.putUInt("tally", TALLY_NR);
  preferences.end();
}
void resetTally(){
  TALLY_NR = 1;
  preferences.begin("vMixTally", false);
  preferences.putUInt("tally", TALLY_NR);
  preferences.end();
}

void saveBrightness(){
  preferences.begin("vMixTally", false);
  preferences.putUInt("bright", BRIGHTNESS);
  preferences.end();
}

void savePmMode(){
  preferences.begin("vMixTally", false);
  preferences.putUInt("pmmode", PM_MODE);
  preferences.end();
}

void savePmColor(){
  preferences.begin("vMixTally", false);
  preferences.putUInt("pmcolor", PM_COLOR);
  preferences.end();
}

void saveVmixCustomEnable(){
  preferences.begin("vMixTally", false);
  preferences.putUInt("customenable", VMIX_CUSTOM_ENABLE);
  preferences.end();
}

void saveVmixCustomPort(){
  preferences.begin("vMixTally", false);
  preferences.putUInt("vmixcustomport", VMIX_CUSTOM_PORT);
  preferences.end();
}

// Print settings
void printSettings()
{
  Serial.println();
  Serial.print("SSID: ");
  Serial.println(&(WIFI_SSID[0]));
  Serial.print("SSID Password: ");
  Serial.println(&(WIFI_PASS[0]));
  Serial.print("vMix hostname: ");
  Serial.println(VMIX_IP);
  Serial.print("Tally number: ");
  Serial.println(TALLY_NR);
}
