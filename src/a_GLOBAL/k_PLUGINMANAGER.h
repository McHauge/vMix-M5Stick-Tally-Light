#include "plugins/LED_HAT.h";

class PluginManager {
  public:
    PluginManager(){}

    M5TallyLEDHat ledHat;
    void setBrightness(int x) {
      ledHat.brightness(x);
    }

    void onLive(int nr, int nr_mode, int rotation){
      ledHat.onLive(nr, rotation);
    }

    void onPre(int nr, int nr_mode, int rotation) {
      ledHat.onPre(nr, rotation);
    }

    void onSafe(int nr, int nr_mode, int rotation) {
      ledHat.onSafe(nr, rotation);
    }

    void onClear() {
      ledHat.onClear();      
    }

    void onUpdate(int nr, int nr_mode, int rotation) {
      ledHat.onUpdate(nr, nr_mode, rotation);      
    }
    
    void onLoop() {
    }
};
