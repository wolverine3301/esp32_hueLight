#include "ColorGamut.h"

ColorGamut::ColorGamut() {

}
/*
   UTIL
*/
void ColorGamut::xy_to_rgb(float newx, float newy) {

}
void ColorGamut::rgb_to_xy(int red, int green, int blue) {

  // convert values from range 0-255 to new range of 0-1
  float r = red * 0.00392157;
  float g = green * 0.00392157;
  float b = blue * 0.00392157;

  if (r > 0.04045) {
    r = pow(((r + 0.055) / 1.055), 2.4);
  } else {
    r = r / 12.92;
  }
  if (g > 0.04045) {
    g = pow(((g + 0.055) / 1.055), 2.4);
  } else {
    g = g / 12.92;
  }
  if (b > 0.04045) {
    b = pow(((b + 0.055) / 1.055), 2.4);
  } else {
    b = b / 12.92;
  }
  float X = r * 0.4124 + g * 0.3576 + b * 0.1805;
  float Y = r * 0.2126 + g * 0.7152 + b * 0.0722;
  float Z = r * 0.0193 + g * 0.1192 + b * 0.9505;

  this->x = X / (X + Y + Z);
  this->y = Y / (X + Y + Z);
  //this->brightness = int(Y * 254);
  this->brightness = 250;
}

/*
   GETTERS
*/
String ColorGamut::getAction() {
  //String state_str = "/state{\"on\":true,\"xy\":";
  String state_str = "{\"on\":true,\"xy\":";
  String xy_str = "[";
  xy_str += this->x;
  xy_str += ",";
  xy_str += this->y;
  xy_str += "]";
  state_str += xy_str;
  state_str += ",\"bri\":";
  state_str += this->brightness;
  state_str += "}";
  return state_str;
}
float ColorGamut::getX() {
  return this->x;
}
float ColorGamut::getY() {
  return this->y;
}
int ColorGamut::getBright() {
  return this->brightness;
}
int ColorGamut::getRed() {
  return this->red;
}
int ColorGamut::getBlue() {
  return this->blue;
}
int ColorGamut::getGreen() {
  return this->green;
}

/*
   SETTERS
*/
void ColorGamut::setX(float newX) {
  this->x = newX;
}
void ColorGamut::setY(float newY) {
  this->y = newY;
}
void ColorGamut::setBright(int newBri) {
  this->brightness = newBri;
}
void ColorGamut::setRed(int newRed) {
  this->red = newRed;
}
void ColorGamut::setBlue(int newBlue) {
  this->blue = newBlue;
}
void ColorGamut::setGreen(int newGreen) {
  this->green = newGreen;
}
