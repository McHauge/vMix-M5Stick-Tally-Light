extern uint8_t QR_CODE[];

void showAPScreen()
{
  resetScreen();
  Serial.println("Showing Access Point Screen");
  screen = 10;

//  int x = random(M5.Lcd.width()  - wifiCodeWidth);
//  int y = random(M5.Lcd.height() - wifiCodeHeight);
//  int x = 20;
//  int y = 20;


//  M5.Lcd.fillScreen(WHITE);
//  M5.Lcd.drawXBitmap(x, y, wifiCode, wifiCodeWidth, wifiCodeHeight, TFT_BLACK);

  renderBatteryLevel();
  M5.Lcd.println();
  M5.Lcd.println("Unable to connect to WiFi");
  M5.Lcd.println("Please connect to:");
  M5.Lcd.println();
  M5.Lcd.println("SSID: vMix-M5Stick-Tally");
  M5.Lcd.println("Pwd: 12345678");
  M5.Lcd.println();
  M5.Lcd.println("To configure the settings");
  M5.Lcd.println("Open http://192.168.4.1");
}
