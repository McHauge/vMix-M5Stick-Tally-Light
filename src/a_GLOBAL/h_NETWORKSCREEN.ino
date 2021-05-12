void showNetworkScreen() {
  Serial.println("Showing Network screen");
  resetScreen();
  screen = 1;
  if(screenRotation == 0 || screenRotation == 2){
    screenRotation = 3;
    M5.Lcd.setRotation(3); 
  }
  if(C_PLUS){
    M5.Lcd.setTextSize(2);
  }
  M5.Lcd.println("SSID:");
  M5.Lcd.println(WIFI_SSID);
  M5.Lcd.println();
  M5.Lcd.println("IP Address:");
  M5.Lcd.println(WiFi.localIP());
  M5.Lcd.println();
  M5.Lcd.println("Wifi Strength:");
  M5.Lcd.print(rssi);
  M5.Lcd.print(" dBm (");
  M5.Lcd.print(rssiLabel);
  M5.Lcd.println(")");
  M5.Lcd.println();
  M5.Lcd.println("v"+semver);
}
