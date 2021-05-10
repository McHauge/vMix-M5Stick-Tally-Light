#include "plugins/LED_HAT.h";

class PluginManager {
  public:
    PluginManager(){}

    M5TallyLEDHat ledHat;
    
    void setPmBrightness(int x) {
      ledHat.brightness(x);
    }

    void onLive(int nr, int nr_mode, int rotation){
//      Serial.print(nr_mode);
      ledHat.onLive(nr, nr_mode, rotation);
    }

    void onPre(int nr, int nr_mode, int rotation) {
//      Serial.print(nr_mode);
      ledHat.onPre(nr, nr_mode, rotation);
    }

    void onSafe(int nr, int nr_mode, int rotation) {
//      Serial.print(nr_mode);
      ledHat.onSafe(nr, nr_mode, rotation);
    }

    void onClear() {
      ledHat.onClear();      
    }

    void onUpdate(int nr, int nr_mode, int rotation) {
//      Serial.print(nr_mode);
//      ledHat.onUpdate(nr, nr_mode, rotation);      
    }
    
    void onLoop() {
    }
};
