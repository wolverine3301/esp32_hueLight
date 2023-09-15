#include "HueBridge.h"

HueBridge::HueBridge(){
  //this->roomMap = HashMap<char*,LightGroup*>( hashArray , hashsize );
  //init();
}

void HueBridge::init(){
  //this->hashArray = HashType<char*,LightGroup*>[hashSize]
  //this->roomMap = HashMap<char*,LightGroup*>( hashArray , hashsize );
}
void HueBridge::addRoom(LightGroup* newRoom){
  
}
Map HueBridge::getRooms(){
  return this->roomMap;
}
String HueBridge::getName(){
  return this->bridgeName;
}
LightGroup HueBridge::getRoom(String roomName){
  return this->roomMap.getValue(roomName);
}
void HueBridge::setName(String newName){
  this->bridgeName = newName;
}
