void showBrightnessScreen(){
  Serial.println("Showing Brightness screen");
  screen = 3;
  screenRotation = 3;
  M5.Lcd.setRotation(3);
  int percentage = 100;
  if(BRIGHTNESS == 7){
    percentage = 0;
  } else if(BRIGHTNESS == 8){
    percentage = 10;
  } else if(BRIGHTNESS == 9){
    percentage = 20;
  } else if(BRIGHTNESS == 10){
    percentage = 40;
  } else if(BRIGHTNESS == 11){
    percentage = 60;
  } else if(BRIGHTNESS == 12){
    percentage = 80;
  }
  resetScreen();
  M5.Lcd.setTextSize(2);
  digitalWrite(LED_BUILTIN, HIGH);
  M5.Lcd.fillScreen(WHITE);
  M5.Lcd.setTextColor(BLACK, WHITE);
  M5.Lcd.setCursor(45, 5);
  M5.Lcd.println("ADJUST");
  M5.Lcd.setCursor(23, 23);
  M5.Lcd.println("BRIGHTNESS");
  M5.Lcd.drawLine(80, 51, 80, 70, BLACK);
  M5.Lcd.drawTriangle(80, 80, 70, 70, 90, 70, BLACK);
  M5.Lcd.fillTriangle(80, 80, 70, 70, 90, 70, BLACK);
  M5.Lcd.setCursor(10, 50);
  M5.Lcd.print(percentage);
  M5.Lcd.println("%");
}

void updateBrightnessVar(){
  if(BRIGHTNESS == 13){
    BRIGHTNESS = 7;
  } else if(BRIGHTNESS == 7){
    BRIGHTNESS = 8;
  } else if(BRIGHTNESS == 8){
    BRIGHTNESS = 9;
  } else if(BRIGHTNESS == 9){
    BRIGHTNESS = 10;
  } else if(BRIGHTNESS == 10){
    BRIGHTNESS = 11;
  } else if(BRIGHTNESS == 11){
    BRIGHTNESS = 12;
  } else if(BRIGHTNESS == 12){
    BRIGHTNESS = 13;
  } else {
    //If for some reason the value is different, default back to 100% brightness (12)
    BRIGHTNESS = 13;
  }
  updateBrightness();
  showBrightnessScreen();
}

void setPluginBrightness() {
  int pluginBrightness = 100;
  if(BRIGHTNESS == 7){
    pluginBrightness = 0;
  } else if(BRIGHTNESS == 8){
    pluginBrightness = 10;
  } else if(BRIGHTNESS == 9){
    pluginBrightness = 20;
  } else if(BRIGHTNESS == 10){
    pluginBrightness = 40;
  } else if(BRIGHTNESS == 11){
    pluginBrightness = 60;
  } else if(BRIGHTNESS == 12){
    pluginBrightness = 80;
  }
  ledHat.brightness(pluginBrightness);
}

void updateBrightness(){
  M5.Axp.ScreenBreath(BRIGHTNESS);
  setPluginBrightness();
  saveBrightness();
}
