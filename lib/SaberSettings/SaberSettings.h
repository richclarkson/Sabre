#ifndef SaberSettings_h
#define SaberSettings_h

class SaberSettingsClass {
    const int sensitivityAddress = 0;
    const int brightnessAddress = 1;
    const int channelsAddress = 2;

    public:
    void setSensitivity(char newVal);
    char getSensitivity();
    void setBrightness(char newVal);
    char getBrightness();
    void setChannels(char newVal);
    char getChannels();
    bool hasNoValues();
    void setDefaults();
};

static SaberSettingsClass SaberSettings;

#endif
