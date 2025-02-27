void startWiFi()
{
    Serial.println("STARTING WIFI");
    WiFi.mode(WIFI_STA);
    WiFi.begin(&(WIFI_SSID[0]), &(WIFI_PASS[0]));

    // We start by connecting to a WiFi network
/* REMOVE THIS LINE WHEN YOU NEED STATIC IP
    // Set your Static IP address
    IPAddress local_IP(192, 168, 178, 222);
    IPAddress gateway(192, 168, 178, 222);
    IPAddress subnet(255, 255, 255, 0);
    IPAddress primaryDNS(8, 8, 8, 8); // optional
    IPAddress secondaryDNS(8, 8, 4, 4); // optional
    
    // Configures static IP address
    if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
      Serial.println("STA Failed to configure");
    }
REMOVE THIS LINE WHEN YOU NEED STATIC IP */

    //WiFi.begin(&(WIFI_SSID[0]), &(WIFI_PASS[0]));
    //WiFi.softAP(ssid, password);

    M5.Lcd.println();
    M5.Lcd.setCursor(lcdCoordX(25), lcdCoordY(60));
    M5.Lcd.println("Waiting for WiFi...");
    M5.Lcd.setCursor(lcdCoordX(38), lcdCoordY(70));
    //while (WiFi.status() != WL_CONNECTED) {
    int tries = 0;
    boolean wifi_connected = true;

    while (WiFi.waitForConnectResult() != WL_CONNECTED)
    {
        M5.Lcd.print(".");
        delay(1000);
        tries++;
        if (tries > 5)
        {
            tries = 0;
            Serial.println("Wifi connection failed, start local wifi");
            wifi_connected = false;
            break;
        }
    }

    if (wifi_connected == false)
    {
        startLocalWiFi();
    }
    else
    {
        cls();
        M5.Lcd.println("WiFi connected");
        M5.Lcd.println("IP address: ");
        M5.Lcd.print(WiFi.localIP());
        startServer();
        connectTovMix(false);
    }
}

// This starts the M5Stack as a WiFi Access Point so you can configure it
void startLocalWiFi()
{
    char apSsid[32];
    sprintf(apSsid, "vMix-M5Stick-Tally %s", WiFi.macAddress().substring(9, WiFi.macAddress().length()));
    WiFi.mode(WIFI_AP);
    WiFi.softAP(apSsid, "12345678");
    apEnabled = true;
    showAPScreen();
    delay(100);
    startServer();
}
