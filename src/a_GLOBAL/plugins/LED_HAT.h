#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#include "FastLED.h"

#define LED_BRIGHTNESS     20    //VALUE FROM 0 TO 255
#define DATA_PIN    26
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#define NUM_LEDS    126
#define UPDATES_PER_SECOND 5
#define arr_len( x )  ( sizeof( x ) / sizeof( *x ) )
CRGB leds[NUM_LEDS];

// Matrix setup params
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(18, 7, DATA_PIN,
  NEO_MATRIX_TOP  + NEO_MATRIX_LEFT +
  NEO_MATRIX_ROWS + NEO_MATRIX_PROGRESSIVE,
  NEO_GRB         + NEO_KHZ800);

const uint16_t colors[] = {
  matrix.Color(255, 0, 255), matrix.Color(100, 255, 0), matrix.Color(255, 255, 0),matrix.Color(0, 0, 255), matrix.Color(255, 0, 255), matrix.Color(0, 255, 255), matrix.Color(255, 255, 255)};

//int y = matrix.height();
//int x = matrix.width();

class M5TallyLEDHat{

public:
	M5TallyLEDHat(){

		matrix.begin();
		matrix.setTextWrap(true);
		matrix.setBrightness(LED_BRIGHTNESS);
		matrix.setRotation(0);

//		FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
//		FastLED.setBrightness(LED_BRIGHTNESS);
	}

	void brightness(int x) {
		matrix.setBrightness(LED_BRIGHTNESS);
		matrix.show();
//		FastLED.setBrightness(x);
//		FastLED.show();
	}

	void onLive(int nr, int rotation) {
		matrixSetScreen(nr, rotation, CRGB::Red);
//		fill_solid( leds, NUM_LEDS, CRGB::Red);
//		FastLED.show();
	}

	void onPre(int nr, int rotation) {
		matrixSetScreen(nr, rotation, CRGB::Green);
//		fill_solid( leds, NUM_LEDS, CRGB::Green);
//		FastLED.show();
  }

  void onSafe(int nr, int rotation) {
		matrixSetScreen(nr, rotation, CRGB::Black);
//		FastLED.clear();
//		FastLED.show();
  }

  void onClear() {
		matrix.fill(CRGB::Black);
		matrix.clear();
		matrix.show();
//		FastLED.clear();
//		FastLED.show();
  }
  
  void matrixSetScreen(int nr, int r, int c) {
		int rotation = 0;
		// Remap rotation to match the LED Matrix
		switch (r) {
			case 0:
				rotation = 1;
				break;

			case 1:
				rotation = 0;
				break;

			case 2:
				rotation = 3;
				break;

			case 3:
				rotation = 2;
				break;

			default:
			  break;
		}

		matrix.fill(c);	
		matrix.setRotation(rotation);

		// Set correct pixel offset based on Rotation and number
		if(rotation == 1 || rotation == 3){ // Potrate
			if (nr <= 9) { 					// Set Caractor offset for inputs 1-9
				matrix.setCursor(1, 5);
				matrix.print(String(nr));
			} else {						// Set Caractor offset for inputs 10 and above
				matrix.setCursor(1, 1);
				matrix.print(String(nr).substring(0,1));
				matrix.setCursor(1, 9);
				matrix.print(String(nr).substring(1));
			}
		} else { 							// Landscape
			if (nr <= 9) { 					// Set Caractor offset for inputs 1-9
				matrix.setCursor(7, 0);
				matrix.print(String(nr));
			} else { 						// Set Caractor offset for inputs 10 and above
				matrix.setCursor(3, 0);
				matrix.print(String(nr));
			}
		}

		matrix.setTextColor(CRGB::White);	
		matrix.show();
  }

};