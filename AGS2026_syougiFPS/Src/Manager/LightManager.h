#ifndef LIGHT_MANAGER_H
#define LIGHT_MANAGER_H
#include "../Common/Vector3.h"

class LightManager {
private:
    float brightness;
    float ambientIntensity;
    float diffuseIntensity;
    Vector3 direction;

    int fillLightHandle;

public:
    LightManager();
    ~LightManager();
    void setBrightness(float b);
    void setAmbient(float a);
    void setDirection(float x, float y, float z);
    void applyLighting(); // ƒ‰ƒCƒuƒ‰ƒŠ‚Ìİ’è‚ÉŠÖ”‚ğŒÄ‚Ño‚·
};

#endif