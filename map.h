//#include <LinkedList.h>
#include <Arduino.h>
#include "LightGroup.h"

/**
 * MAP
 * This is a very simple object of 2 linked list to map string names of rooms
 * to lightgroups (Rooms). Simply iterates through the list of names,
 * once a match is found, returns the light group at that index.
 * 
 */
class Map{
  private:
    /* list of key names */
    LinkedList<String> keys;
    /* list of values */
    LinkedList<LightGroup> values;
    void init();
    
  public:
    Map();
    LightGroup getValue(String key);
    void addPair(String key, LightGroup value);
    void POP();
    
    
};
