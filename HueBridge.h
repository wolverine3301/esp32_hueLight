//#include <Arduino.h>
//#include "LightGroup.h"
#include "map.h"

//template< unsigned SIZE >
class HueBridge {
  
  private:
    //static const byte hashSize = 16;
    //HashType<char*, LightGroup*> hashArray[hashSize];
    Map roomMap;
    String bridgeName;

    void init();

  public:

    HueBridge();

    void addRoom(LightGroup* newRoom);

    String getName();
    LightGroup getRoom(String roomName);
    Map getRooms();
    void setName(String newName);

};
