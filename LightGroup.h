#include "Light.h"
#include <LinkedList.h>

/**
 * LIGHTGROUP
 * 
 * Resembles a room or light that are to be controlled together
 * This is done with a linked list of light objects
 * 
 * 
 */
class LightGroup{
  
  private:
    /* the total number of lights in the room / group */
    int numberOfLights; 
    /* the name of the room / group */
    String groupName; 
    /* the lights */
    LinkedList<Light> lights; 
    void init();
  
  public:
    LightGroup();
    /* GETTERS */
    int getNumberOfLights();
    String getGroupName();
    LinkedList<Light> getLights();

    /* SETTERS */
    void setGroupName(String Name);
    void addLight(Light newLight);

    /* UTIL */
    void printGroupInfo();
  
};
