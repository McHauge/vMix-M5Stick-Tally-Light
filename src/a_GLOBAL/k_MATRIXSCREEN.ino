void showPmModeScreen(){
  screen = 4;
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
}

void updatePmModeVar(){
  if(PM_MODE == 0){
    PM_MODE = 1;
  } else if(PM_MODE == 1){
    PM_MODE = 2;
  } else if(PM_MODE == 2){
    PM_MODE = 3;
  } else if(PM_MODE == 3){
    PM_MODE = 0;
  } else {
    //If for some reason the value is different, default back to PM_MODE = 0
    PM_MODE = 0;
  }
  updatePmMode();
  showPmModeScreen();
}

void updatePmMode(){
  renderCurentMatrix();
  savePmMode();
}
