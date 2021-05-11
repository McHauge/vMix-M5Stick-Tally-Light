void showTallyNum()
{
  Serial.println("Showing Tally Number screen");
  screen = 2;
  resetScreen();
  screenRotation = 3;
  M5.Lcd.setRotation(3);

  M5.Lcd.setTextSize(2);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextColor(WHITE, BLACK);
  M5.Lcd.setCursor(45, 5);
  M5.Lcd.println("ADJUST");
  M5.Lcd.setCursor(10, 30);
  M5.Lcd.println("TALLY");
  M5.Lcd.setCursor(10, 50);
  M5.Lcd.println("INPUT");
  M5.Lcd.setTextSize(4);
  if (TALLY_NR <=9) { // Center tally nr on the right side, depending on 1 or 2 digits
    M5.Lcd.setCursor(110, 32);    
  } else {
    M5.Lcd.setCursor(95, 32);        
  }
  M5.Lcd.println(TALLY_NR);
  M5.Lcd.drawLine(80, 51, 80, 70, WHITE);
  M5.Lcd.drawTriangle(80, 80, 70, 70, 90, 70, WHITE);
  M5.Lcd.fillTriangle(80, 80, 70, 70, 90, 70, WHITE);
}

/*
  screenRotation = 3;
  M5.Lcd.setRotation(3);
  String s = "";
  if(PM_MODE == 0){
    s = "User";
  } else if(PM_MODE == 1){
    s = "PGM";
  } else if(PM_MODE == 2){
    s = "PVW";
  } else if(PM_MODE == 3){
    s = "None";
  }
  resetScreen();
  M5.Lcd.setTextSize(2);
  digitalWrite(LED_BUILTIN, HIGH);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextColor(WHITE, BLACK);
  M5.Lcd.setCursor(45, 5);
  M5.Lcd.println("ADJUST");
  M5.Lcd.setCursor(10, 23);
  M5.Lcd.println("LED Numbers");
  M5.Lcd.drawLine(80, 51, 80, 70, WHITE);
  M5.Lcd.drawTriangle(80, 80, 70, 70, 90, 70, WHITE);
  M5.Lcd.fillTriangle(80, 80, 70, 70, 90, 70, WHITE);
  M5.Lcd.setCursor(10, 50);
  M5.Lcd.println(s);
*/
