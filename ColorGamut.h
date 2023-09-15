#include <math.h>
#include <Arduino.h>
class ColorGamut{
  private:
    float x;
    float y;
    int brightness;
    
    int red;
    int blue;
    int green;
  public:
    ColorGamut();
    void xy_to_rgb(float newx, float newy);
    void rgb_to_xy(int r, int g, int b);
    
    String getAction();
    float getX();
    float getY();
    int getBright();
    
    int getRed();
    int getBlue();
    int getGreen();
    
    void setX(float newX);
    void setY(float newY);
    void setBright(int newBri);
    void setRed(int newRed);
    void setBlue(int newBlue);
    void setGreen(int newGreen);
    
};
