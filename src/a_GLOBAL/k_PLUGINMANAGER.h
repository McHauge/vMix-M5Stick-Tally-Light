#include "plugins/LED_HAT.h";

class PluginManager {
  public:
    PluginManager(){}

    M5TallyLEDHat ledHat;
    void setBrightness(int x) {
      ledHat.brightness(x);
    }

    void onLive(int nr, int rotation){
      ledHat.onLive(nr, rotation);
    }

    void onPre(int nr, int rotation) {
      ledHat.onPre(nr, rotation);
    }

    void onSafe(int nr, int rotation) {
      ledHat.onSafe(nr, rotation);
    }

    void onClear() {
      ledHat.onClear();      
    }
    
    void onLoop() {
//      ledHat.onLoop();
    }
};
