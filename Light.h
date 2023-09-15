#include <Arduino.h>

class Light {
  
  private:
    bool isON;
    int brightness;
    String lightName;
    String room_name;
    float x;
    float y;
    int hue;
    int sat;
    void init();
  public:
    Light();
    
    bool getON();
    int getBrightness();
    String getName();
    String getRoom();
    float getX();
    float getY();
    int getHue();
    int getSat();
    
    void setON(bool onOff); // onOff -> true = on
    void setBrightness(int bright); // bright -> int between 0-255 ,255=brightest
    void setName(String newName);
    void setRoom(String newRoom);
    void setXY(float newX, float newY);
    void setHue(int newHue);
    void setSat(int newSat);
    void printLightInfo();
    void parseXY(String newXY);
};
