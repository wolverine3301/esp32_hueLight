#include "map.h"

Map::Map(){
  init();
}
void Map::init(){
   this->keys = LinkedList<String>();
   this->values = LinkedList<LightGroup>();
}
LightGroup Map::getValue(String key){
  for(int i = 0; i < keys.size();i++){
    if (strcmp(keys.get(i).c_str(),key.c_str()) == 0){
      return values.get(i);
    }else{
      LightGroup nullGroup;
      return nullGroup;
    }
  }
}
void Map::addPair(String key, LightGroup value){
  this->keys.add(key);
  this->values.add(value);
  
}
void POP(){

}
