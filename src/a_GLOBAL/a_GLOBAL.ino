#define C_PLUS 0 //CHANGE TO 1 IF YOU USE THE M5STICK-C PLUS
// LCD has a resolution of: 80×160

#if C_PLUS == 1
#include <M5StickCPlus.h>
#else
#include <M5StickC.h>
#endif
#include <WiFi.h>
#include <PinButton.h>
#include <WebServer.h>
#include <Preferences.h>
#include "plugins/LED_HAT.h";
//#include "M_PLUGINMANAGER.h";

#define LED_BUILTIN 10

extern uint8_t QR_CODE[]; // Wifi QR Code
int tnlen = 1; //LET THIS BE

Preferences preferences;

// DON'T CHANGE THESE VARIABLES, YOU CAN CHANGE THEM IN THE WEB UI
String WIFI_SSID = "";
String WIFI_PASS = "";
String VMIX_IP = "";
String M_TALLY = "";  // Store Tally numbers when following more that one input
int VMIX_PORT = 8099; // USES THE TCP API PORT, THIS IS FIXED IN VMIX
int TALLY_NR = 1;     // Stores Selected Tally to Follow
int PGM_NR = 0;       // Global variable for storing what curently on PGM (Program)
int PVW_NR = 0;       // Global variable for storing what curently on PVW (Preview)
int BRIGHTNESS = 13;  // 100%
int CONN_INT = 0;     // Sets reconect intervals
int MODE = 0;         // 0 for words like SAFE, PRE and LIVE. 1 for numbers with changing background
int PM_MODE = 0;      // Sets the Plugin display mode, 0 = Selected Camera NR, 1 = Follow what's on PGM, 2 = Follow what's on PVW, 3 = No numbers (only bg color),
int PM_COLOR = 0;     // Sets the Plugin Colors ON or Off, mostly for text colors
int JUSTLIVE = 0;     // When 1, SAFE and PRE are not used. Just the LIVE screen

String semver = "2.4.1"; // Software Version Number
