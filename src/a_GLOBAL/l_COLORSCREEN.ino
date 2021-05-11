void showPmColorScreen(){
  Serial.println("Showing Matrix Color Screen");
  screen = 5;
  screenRotation = 3;
  M5.Lcd.setRotation(3);
  String s = "";
  if(PM_COLOR == 0) {
    s = "OFF";
  } else if(PM_COLOR == 1) {
    s = "ON";
  }
  resetScreen();
  M5.Lcd.setTextSize(2);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextColor(WHITE, BLACK);
  M5.Lcd.setCursor(45, 5);
  M5.Lcd.println("ADJUST");
  M5.Lcd.setCursor(20, 30);
  M5.Lcd.println("LED COLORS");
  M5.Lcd.setCursor(20, 50);
  M5.Lcd.println("SET:");
  M5.Lcd.drawLine(80, 51, 80, 70, WHITE);
  M5.Lcd.drawTriangle(80, 80, 70, 70, 90, 70, WHITE);
  M5.Lcd.fillTriangle(80, 80, 70, 70, 90, 70, WHITE);
  M5.Lcd.setCursor(100, 50);
  M5.Lcd.println(s);
}

void updatePmColorVar(){
  if(PM_COLOR == 0){
    PM_COLOR = 1;
  } else if(PM_COLOR == 1){
    PM_COLOR = 0;
  } else {
    //If for some reason the value is different, default back to PM_MODE = 0
    PM_COLOR = 0;
  }
  updatePmColor();
  showPmColorScreen();
}

void updatePmColor(){
  renderCurentMatrix();
  savePmColor();
}
