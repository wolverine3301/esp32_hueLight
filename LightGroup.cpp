#include "LightGroup.h"

LightGroup::LightGroup(){
  init();
}
void LightGroup::init(){
  this->lights = LinkedList<Light>();
}
void LightGroup::addLight(Light newLight){
  this->lights.add(newLight);
  this->numberOfLights++;
}
void LightGroup::printGroupInfo(){
  
}
/*
 * GETTERS
 */
int LightGroup::getNumberOfLights(){
  return this->numberOfLights;
}
String LightGroup::getGroupName(){
  return this->groupName;
}
LinkedList<Light> LightGroup::getLights(){
  return this->lights;
}
/*
 * SETTERS
 */
void LightGroup::setGroupName(String newName){
  this->groupName = newName;
}
