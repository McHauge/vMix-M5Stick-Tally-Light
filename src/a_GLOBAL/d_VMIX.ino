bool stm = 0;
bool rec = 0;

// Connect to vMix instance
boolean connectTovMix(bool recursive) {
  resetScreen();
  Serial.println("Connecting to vMix...");
  M5.Lcd.println("Connecting to vMix...");

  if (client.connect(&(VMIX_IP[0]), VMIX_PORT))
  {
    connectedTovMix = true;
    M5.Lcd.println("Connected to vMix!");

    // Subscribe to the tally events
    client.println("SUBSCRIBE TALLY");
    client.println("SUBSCRIBE ACTS");
    showTallyScreen();
    return true;
  }
  else
  {
    if (recursive) {
      return false;
    }
    char tryCount = 0;
    cls();
    M5.Lcd.println("Could not connect to vMix");
    M5.Lcd.println("Retrying: 0/3");
    boolean retry = false;
    for (uint8_t i = 0; i < 3; i++)
    {
      Serial.print(i);
      retry = retryConnectionvMix(i);
      if (!retry) {
        return true;
      }
    }
    cls();
    connectedTovMix = false;
    noConnectionTovMix();
    return false;
  }
}

void singleReconnect() {
  resetScreen();
  M5.Lcd.println("Connecting to vMix...");
  if (client.connect(&(VMIX_IP[0]), VMIX_PORT))
  {
    lastConnCheck = millis();
    connectedTovMix = true;
    M5.Lcd.println("Connected to vMix!");

    // Subscribe to the tally events
    client.println("SUBSCRIBE TALLY");
    showTallyScreen();
  } else {
    lastConnCheck = millis();
  }
}

boolean retryConnectionvMix(int tryCount) {
  cls();
  M5.Lcd.setTextSize(1);
  M5.Lcd.println("Couldn't connect to vMix");
  M5.Lcd.print("Retrying: ");
  M5.Lcd.print(tryCount);
  M5.Lcd.print("/3");
  delay(2000);
  boolean conn = connectTovMix(true);
  if (conn) {
    return false;
  }
  return true;
}

void posTallyNums() {
  int y = lcdCoordY(70);
  int x = lcdCoordX(30);
  if (screenRotation == 1 || screenRotation == 3) {
    x = lcdCoordX(70);
    y = lcdCoordY(23);
    if (tnlen == 2) {
      x = lcdCoordX(50);
    }
    M5.Lcd.setCursor(x, y);
  } else {
    if (tnlen == 2) {
      x = lcdCoordX(10);
    }
    M5.Lcd.setCursor(x, y);
  }
}

void setTallyProgram()
{
  //  digitalWrite(LED_BUILTIN, LOW);
  M5.Lcd.fillScreen(RED);
  M5.Lcd.setTextColor(WHITE, RED);
  if (screenRotation == 1 || screenRotation == 3) {
    M5.Lcd.setCursor(lcdCoordX(25), lcdCoordY(23));
    if (MODE == 0) {
      M5.Lcd.println("LIVE");
    }
  } else if (screenRotation == 0 || screenRotation == 2) {
    M5.Lcd.setCursor(lcdCoordX(30), lcdCoordY(70));
    if (MODE == 0) {
      M5.Lcd.println("L");
    }
  }
  if (MODE == 1) {
    posTallyNums();
    M5.Lcd.println(TALLY_NR);
  }
}

void setTallyPreview() {
  // digitalWrite(LED_BUILTIN, HIGH);
  M5.Lcd.fillScreen(GREEN);
  M5.Lcd.setTextColor(BLACK, GREEN);
  if (screenRotation == 1 || screenRotation == 3) {
    M5.Lcd.setCursor(lcdCoordX(40), lcdCoordY(23));
    if (!JUSTLIVE && MODE == 0) {
      M5.Lcd.println("PRE");
    }
  } else if (screenRotation == 0 || screenRotation == 2) {
    M5.Lcd.setCursor(lcdCoordX(30), lcdCoordY(70));
    if (!JUSTLIVE && MODE == 0) {
      M5.Lcd.println("P");
    }
  }
  if (MODE == 1) {
    posTallyNums();
    M5.Lcd.println(TALLY_NR);
  }
}

void setTallyOff() {
  // digitalWrite(LED_BUILTIN, HIGH);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextColor(WHITE, BLACK);
  if (screenRotation == 1 || screenRotation == 3) {
    M5.Lcd.setCursor(lcdCoordX(23), lcdCoordY(23));
    if (!JUSTLIVE && MODE == 0) {
      M5.Lcd.println("SAFE");
    }
  } else if (screenRotation == 0 || screenRotation == 2) {
    M5.Lcd.setCursor(lcdCoordX(30), lcdCoordY(70));
    if (!JUSTLIVE && MODE == 0) {
      M5.Lcd.println("S");
    }
  }
  if (MODE == 1) {
    posTallyNums();
    M5.Lcd.println(TALLY_NR);
  }
}

// Handle incoming data
void handleData(String data) {
  bool changed = false;
  bool tallyChange = false;
  // Check if server data is tally data
  if (data.indexOf("TALLY") == 0)
  {
    char newState = data.charAt(TALLY_NR + 8);

    // Parse so we only have the tally digits and store then to a char array
    String a_data = data.substring(9);
    int b_char_len = a_data.length() + 1;
    char b_char[b_char_len];
    a_data.toCharArray(b_char, b_char_len);

    // Check each input for what input is curently on PGM and PVW and store it
    for (int i = 0; i < b_char_len; i++) {
      if (b_char[i] == '1') {
        PGM_NR = i + 1;  // check what input is on program
      }
      else if (b_char[i] == '2') {
        PVW_NR = i + 1;  // check what input is on preview
      }
    }
    tallyChange = true;
    
    // Check if tally state has changed
    if (currentState != newState || screen == 1)
    {
      currentState = newState;
      if (M_TALLY == "") {
        showTallyScreen();
        renderCurentMatrix();
        tallyChange = false;
      }
    }
    if (M_TALLY != "") {
      if (currentState != '1' && M_TALLY != "") {
        int str_len = M_TALLY.length() + 1;

        // Prepare the character array (the buffer)
        char str[str_len];

        // Copy it over
        M_TALLY.toCharArray(str, str_len);

        char * pch;
        pch = strtok(str, ",");
        while (pch != NULL)
        {
          String c(pch);
          char newMState = data.charAt(c.toInt() + 8);
          if ((currentState == '0' && (newMState == '1' || newMState == '2')) || (currentState == '2' && (newMState == '1'))) {
            currentState = newMState;
            changed = true;
          }
          pch = strtok(NULL, ",");
        }
      }
      if (changed == true) {
        showTallyScreen();
        renderCurentMatrix();
        tallyChange = false;
      }
    }
    if (tallyChange == true) {
      renderCurentMatrix();
    }
  }
  else
  {
    if (data.indexOf("ACTS OK Recording 1") == 0) {
      rec = 1;
    } else if (data.indexOf("ACTS OK Recording 0") == 0) {
      rec = 0;
    } else if (data.indexOf("ACTS OK Streaming 1") == 0) {
      stm = 1;
    } else if (data.indexOf("ACTS OK Streaming 0") == 0) {
      stm = 0;
    } else {
      Serial.print("Response from vMix: ");
      Serial.println(data);

      // Print out what's curently on PGM and PVW
      Serial.println("PGM: " + String(PGM_NR) + " PVW: " + String(PVW_NR));
    }
    showStatus();
  }
}

void showTallyScreen() {
  cls();              // Clear Screen
//  ledHat.clearDisp(); // Clear LED Matrix
  screen = 0;
  if (C_PLUS) {
    M5.Lcd.setTextSize(8);
  } else {
    M5.Lcd.setTextSize(5);
  }

  if (!JUSTLIVE) {
    switch (currentState) {
      case '0': setTallyOff();     break;
      case '1': setTallyProgram(); break;
      case '2': setTallyPreview(); break;
      default: setTallyOff();
    }
  } else {
    switch (currentState){
      case '1': setTallyProgram(); break;
      default: setTallyOff();
    }
  }

//  ledHat.showDisp();  // Show the LED Matrix Display
  renderBatteryLevel();
  showStatus();
}

void renderCurentMatrix() {
    ledHat.clearDisp();
    
    if (!JUSTLIVE) {
    switch (currentState) {
      case '0': ledHat.setSafe(); break;
      case '1': ledHat.setLive(); break;
      case '2': ledHat.setPreview(); break;
      default:  ledHat.setSafe();
    }
  } else {
    switch (currentState){
      case '1': ledHat.setLive(); break;
      default:  ledHat.setSafe();
    }
  }

  // Set LED Matrix Text Color
  if (PM_COLOR == 0) { // If text colors are disabled just use white
    ledHat.textColor(255, 255, 255);    
  } else if ( M_TALLY != "" && (currentState == '1' || currentState == '2') ) {
    ledHat.textColor(255, 255, 255);
  } else if (PGM_NR == TALLY_NR || PVW_NR == TALLY_NR) {
    ledHat.textColor(255, 255, 255);
  } else {
    switch (PM_MODE){
      case 0:  ledHat.textColor(255, 255, 255); break;
      case 1:  ledHat.textColor(255, 0, 0);     break;
      case 2:  ledHat.textColor(0, 255, 0);     break;
      default: ledHat.textColor(255, 255, 255); break;
    }    
  }

  // Set LED Matrix Text
  switch (PM_MODE){
    case 0:  // If we have multi inputs selected, show what input is on program (of the selected otherwise just the main input)
      if ( M_TALLY != "" && currentState == '1' ) { // Check If any on Progam
        ledHat.showNumber(PGM_NR, screenRotation); 
      } else if ( M_TALLY != "" && currentState == '2' ) { // Check if any on Preview
        ledHat.showNumber(PVW_NR, screenRotation); 
      } else {
        ledHat.showNumber(TALLY_NR, screenRotation);         
      }
      break;
    case 1:  ledHat.showNumber(PGM_NR, screenRotation);   break;
    case 2:  ledHat.showNumber(PVW_NR, screenRotation);   break;
    default: ledHat.showNumber(0, screenRotation);        break;
  }
  ledHat.showDisp();  // Show the LED Matrix Display
}

void showStatus() {
  if (C_PLUS) {
    M5.Lcd.setTextSize(2);
  } else {
    M5.Lcd.setTextSize(1);
  }

  if (screenRotation == 1 || screenRotation == 3) {
    if (C_PLUS) {
      M5.Lcd.setCursor(200, 0);
    } else {
      M5.Lcd.setCursor(140, 0);
    }
  } else {
    if (C_PLUS) {
      M5.Lcd.setCursor(95, 220);
    } else {
      M5.Lcd.setCursor(60, 150);
    }
  }
  if (rec) {
    M5.Lcd.print("REC");
  } else {
    M5.Lcd.print("   ");
  }

  if (screenRotation == 1 || screenRotation == 3) {
    if (C_PLUS) {
      M5.Lcd.setCursor(150, 0);
    } else {
      M5.Lcd.setCursor(110, 0);
    }
  } else {
    if (C_PLUS) {
      M5.Lcd.setCursor(10, 220);
    } else {
      M5.Lcd.setCursor(0, 150);
    }
  }
  if (stm) {
    M5.Lcd.print("STM");
  } else {
    M5.Lcd.print("   ");
  }
}

void noConnectionTovMix() {
  resetScreen();
  M5.Lcd.println("Couldn't connect to vMix");
  M5.Lcd.println();
  M5.Lcd.println("vMix is closed");
  M5.Lcd.println("or check settings");
  M5.Lcd.println();
  M5.Lcd.print("http://");
  M5.Lcd.println(WiFi.localIP());
  M5.Lcd.println();
  M5.Lcd.println("Press BTN39 to reconnect");
}
