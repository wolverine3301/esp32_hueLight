#include "Light.h"

Light::Light(){

}
void Light::init(){
  //float initXY[2] ={0.0,0.0};
  //this->xy = initXY;
}
void Light::printLightInfo(){
  Serial.print("LIGHT NAME: ");
  Serial.println(this->lightName);
  Serial.print("ROOM: ");
  Serial.println(this->room_name);
  Serial.print("ON/OFF: ");
  Serial.println(this->isON);
  Serial.print("Brightness: ");
  Serial.println(this->brightness);
  Serial.print("X: ");
  Serial.println(this->x);
  Serial.print("Y: ");
  Serial.println(this->y);
  /*
  Serial.print();
  Serial.println();
  Serial.print();
  Serial.println();
  Serial.print();
  Serial.println();
  */
}
/*
 * GETTERS
 */
//true/false is light on
bool Light::getON(){
  return this->isON;
}
int Light::getBrightness(){
  return this->brightness;
}
String Light::getName(){
  return this->lightName;
}
String Light::getRoom(){
  return this->room_name;
}
float Light::getX(){
  return this->x;
}
float Light::getY(){
  return this->y;
}
int Light::getHue(){
  return this->hue;
}
int Light::getSat(){
  return this->sat;
}
/*
 * SETTERS
 */
void Light::setON(bool toggleON){
  this->isON = toggleON;
}
void Light::setBrightness(int newBrightness){
  this->brightness = newBrightness;
}
void Light::setName(String newName){
  this->lightName = newName;
}
void Light::setRoom(String newRoom){
  this->room_name = newRoom;
}
void Light::setXY(float newX, float newY){
  this->x = newX;
  this->y = newY;
}
void Light::setHue(int newHue){
  this->hue = newHue;
}
void Light::setSat(int newSat){
  this->sat = newSat;
}
/*
 * UTIL
 */
void Light::parseXY(String newXY){
  int str_len = newXY.length() + 1; 
    char char_array[str_len];
    String x_str = "";
    String y_str = "";
    bool commaSWITCH = false;
    // Copy it over 
    newXY.toCharArray(char_array, str_len);
    for(int kk=0;kk<str_len;kk++){
      if (newXY[kk] != '[' && newXY[kk] != ']'){
        if (newXY[kk] == ','){
          commaSWITCH = true;
        }
        if(!commaSWITCH && newXY[kk] != ','){
          x_str = x_str + (String)newXY[kk];
        }else if (commaSWITCH && newXY[kk] != ','){
          y_str = y_str + (String)newXY[kk];
        }
      }
    }
    newXY.toCharArray(char_array, str_len);

    int x_str_len = x_str.length() + 1; 
    char x_char_array[x_str_len];
    int y_str_len = y_str.length() + 1; 
    char y_char_array[y_str_len];

    y_str.toCharArray(y_char_array, y_str_len);
    x_str.toCharArray(x_char_array, x_str_len);

    this->y = atof(y_char_array);
    this->x = atof(x_char_array);

 }
