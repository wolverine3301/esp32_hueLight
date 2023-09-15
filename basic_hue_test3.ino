#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <LinkedList.h>
#include "LightGroup.h"
#include "ColorGamut.h"
#include "secret.h"

const char *GROUP_URL  = "http://" BRIDGE "/api/" API_USERNAME "/groups/" ROOM;
const char *ACTION_URL = "http://" BRIDGE "/api/" API_USERNAME "/groups/" ROOM "/action";
//const char *HUE_BRIDGE_URL = "http://" BRIDGE "/api/" API_USERNAME "/lights";
const char *HUE_BRIDGE_URL = "http://" BRIDGE "/api/" API_USERNAME;
const char *COLOR_URL  = "http://" BRIDGE "/api/" API_USERNAME "/groups/" ROOM;

const String SCENE_DATA = "{\"scene\": \"" SCENE "\"}";
const String OFF_DATA = "{\"on\": false}";

const int INPUT_PIN = 12;
const int LED_PIN = 22;

const unsigned int BOUNCE_DELAY_MS = 500; // ms

unsigned long lastInterrupt;  // last interrupt time
volatile int shouldTrigger = 0;

const unsigned int CONNECT_TIMEOUT_MS = 30000;  // WiFi connnection timeout (ms)

// connectToWiFi adapted from ESP32 example code. See, e.g.:
// https://github.com/espressif/arduino-esp32/blob/master/libraries/WiFi/examples/WiFiClient/WiFiClient.ino
void connectToWiFi() {
  unsigned long startTime = millis();
  Serial.println("Connecting to: " + String(SSID));

  WiFi.disconnect();
  WiFi.begin(SSID, PWD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");

    if (millis() - startTime > CONNECT_TIMEOUT_MS) {
      Serial.println();
      Serial.println("Failed to connect.");
      return;
    }
  }

  WiFi.setAutoReconnect(true);

  Serial.println();
  Serial.println("Connected.");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  digitalWrite(LED_PIN, LOW);
  delay(100);
  digitalWrite(LED_PIN, HIGH);
}

void putJson(const char *url, String content) {
  Serial.println("putJson");
  Serial.printf("PUT %s: %s\n", url, content.c_str());

  HTTPClient http;
  http.begin(url);
  int httpCode = http.PUT(content);
  if (httpCode > 0) {
    Serial.printf("Code: %d\n", httpCode);
  } else {
    Serial.printf("Error: %s\n", http.errorToString(httpCode).c_str());
  }
  Serial.println(http.getString());
  http.end();
}

String getUrl(const char *url) {
  //Serial.println("get");
  //Serial.printf("GET %s\n", url);

  HTTPClient http;
  http.begin(url);
  int httpCode = http.GET();
  if (httpCode > 0) {
    Serial.printf("Code: %d\n", httpCode);
  } else {
    Serial.printf("Error: %s\n", http.errorToString(httpCode).c_str());
  }

  return http.getString();
}

void turnLightsOn() {
  Serial.println("turnLightsOn");
  putJson(ACTION_URL, SCENE_DATA);
}

void turnLightsOff() {
  Serial.println("turnLightsOff");
  putJson(ACTION_URL, OFF_DATA);
}

bool lightsOn() {
  Serial.println("lightsOn");
  String jsonBody = getUrl(GROUP_URL);

  StaticJsonDocument<256> jsonDoc;
  deserializeJson(jsonDoc, jsonBody);
  bool isOn = jsonDoc["state"]["any_on"];
  Serial.printf("isOn: %d\n", isOn);
  return isOn;
}

void toggleLights() {
  if (lightsOn()) {
    turnLightsOff();
  } else {
    turnLightsOn();
  }
}

void handleButton() {
  unsigned long currentTime = millis();
  if ((currentTime - lastInterrupt) > BOUNCE_DELAY_MS) {
    Serial.println("Handling button event");
    lastInterrupt = currentTime;
    shouldTrigger = 1;
  }
}
void changeXY(){
  float newx = 0.1515;
  float newy = 0.185;
  for(int i = 0; i< 100;i++){
    if(newx > 0.89){
      newx = 0.1515;
    }
    if(newy < 0.01){
      newy = 0.85;
    }
    newx = newx + 0.05;
    newy = newy - 0.05;
  }
  
}
void merge(JsonVariant dst, JsonVariantConst src)
{
  if (src.is<JsonObjectConst>())
  {
    for (JsonPairConst kvp : src.as<JsonObjectConst>())
    {
      if (dst[kvp.key()]) 
        merge(dst[kvp.key()], kvp.value());
      else
        dst[kvp.key()] = kvp.value();
    }
  }
  else
  {
    dst.set(src);
  }
}
void changeLightsColor() {
  //String body = {"on":true, "sat":254, "bri":254,"hue":10000}
  //putJson(ACTION_URL, SCENE_DATA);
  
  String jsonBody = getUrl(HUE_BRIDGE_URL);
  StaticJsonDocument<4096> jsonDoc;
  deserializeJson(jsonDoc, jsonBody);

  LightGroup lightGroupOne = LightGroup();

  JsonObject root = jsonDoc.as<JsonObject>();
  JsonObject cha = jsonDoc.as<JsonObject>();
  
  JsonObject root2 = root["lights"];
  ColorGamut color;
  for (JsonPair kv : root2) {
    Light newLight = Light();
    Serial.print("LIGHT: ");
    Serial.println(kv.key().c_str());
    String gogo = String(HUE_BRIDGE_URL);
    gogo+="/lights/";
    gogo += kv.key().c_str();
    gogo += "/state";
    String gogo2 = "{\"on\":true,\"xy\":";
    //newLight.setBrightness
    //Serial.println(kv.value().as<const char*>());
    JsonObject root3 = root2[kv.key()];
    JsonObject STATE = root3["state"];
    
    
  float newx = 0.1515;
  float newy = 0.185;
  for(int i = 0; i< 100;i++){
    if(newx > 0.89){
      newx = 0.1515;
    }
    if(newy < 0.01){
      newy = 0.85;
    }
    newx = newx + 0.05;
    newy = newy - 0.05;
    String xy_str = "[";
    xy_str += newx;
    xy_str += ",";
    xy_str += newy;
    xy_str += "]";
    gogo2+=xy_str;
    gogo2+=",\"bri\":200";
    gogo2+="}";
    Serial.println("XY:");
    Serial.println(xy_str);
    cha["lights"][kv.key()]["state"]["xy"] = xy_str;
    //serializeJson(jsonDoc,cha);
    //const char* gogo3 = gogo2;
    putJson(gogo.c_str(), gogo2);
    //delay(500);
  }
  }


    
}
void changeLightsColor2() {
  //String body = {"on":true, "sat":254, "bri":254,"hue":10000}
  //putJson(ACTION_URL, SCENE_DATA);
  
  String jsonBody = getUrl(HUE_BRIDGE_URL);
  StaticJsonDocument<4096> jsonDoc;
  deserializeJson(jsonDoc, jsonBody);

  LightGroup lightGroupOne = LightGroup();

  JsonObject root = jsonDoc.as<JsonObject>();
  JsonObject cha = jsonDoc.as<JsonObject>();
  
  JsonObject root2 = root["lights"];
  ColorGamut color;
  for (JsonPair kv : root2) {
    Light newLight = Light();
    Serial.print("LIGHT: ");
    Serial.println(kv.key().c_str());
    String gogo = String(HUE_BRIDGE_URL);
    gogo+="/lights/";
    gogo += kv.key().c_str();
    gogo += "/state";
    String gogo2;
    JsonObject root3 = root2[kv.key()];
    JsonObject STATE = root3["state"];
    
    int j = 250;
    for(int i = 0; i < 250; i+=10){
      if( j < 1){
        j = 250;
      }
      color.rgb_to_xy(i, j, i);
      gogo2 = color.getAction();
      putJson(gogo.c_str(), gogo2);
      delay(100);
      j-=10;
    }
    //Serial.println("XY:");
    //Serial.println(xy_str);
    //cha["lights"][kv.key()]["state"]["xy"] = xy_str;
    //serializeJson(jsonDoc,cha);
    //const char* gogo3 = gogo2;
    
    //delay(500);
  }
}
void changeLightsColor3() {
  //String body = {"on":true, "sat":254, "bri":254,"hue":10000}
  //putJson(ACTION_URL, SCENE_DATA);
  
  String jsonBody = getUrl(HUE_BRIDGE_URL);
  StaticJsonDocument<4096> jsonDoc;
  deserializeJson(jsonDoc, jsonBody);

  LightGroup lightGroupOne = LightGroup();

  JsonObject root = jsonDoc.as<JsonObject>();
  JsonObject cha = jsonDoc.as<JsonObject>();
  
  JsonObject root2 = root["lights"];
  ColorGamut color;

      int j = 250;
    for(int i = 0; i < 250; i+=5){
      if( j < 1){
        j = 250;
      }
  for (JsonPair kv : root2) {
    Light newLight = Light();
    Serial.print("LIGHT: ");
    Serial.println(kv.key().c_str());
    String gogo = String(HUE_BRIDGE_URL);
    gogo+="/lights/";
    gogo += kv.key().c_str();
    gogo += "/state";
    String gogo2;
    JsonObject root3 = root2[kv.key()];
    JsonObject STATE = root3["state"];
    

      
      color.rgb_to_xy(i, j, i);
      gogo2 = color.getAction();
      putJson(gogo.c_str(), gogo2);

    }
          delay(500);
      j-=5;
    //Serial.println("XY:");
    //Serial.println(xy_str);
    //cha["lights"][kv.key()]["state"]["xy"] = xy_str;
    //serializeJson(jsonDoc,cha);
    //const char* gogo3 = gogo2;
    
    //delay(500);
  }
}


void get_json_size(JsonObject obj) {
  Serial.println("SIZE:");
  Serial.println(measureJson(obj));
}
void initializeLights() {
  String jsonBody = getUrl(HUE_BRIDGE_URL);
  StaticJsonDocument<4096> jsonDoc;
  deserializeJson(jsonDoc, jsonBody);

  LightGroup lightGroupOne = LightGroup();

  JsonObject root = jsonDoc.as<JsonObject>();
  JsonObject root2 = root["lights"];
  for (JsonPair kv : root2) {
    Light newLight = Light();
    Serial.print("LIGHT: ");
    Serial.println(kv.key().c_str());

    //newLight.setBrightness
    //Serial.println(kv.value().as<const char*>());
    JsonObject root3 = root2[kv.key()];
    JsonObject STATE = root3["state"];
    
    String lightname = root3["name"];
    newLight.setName(lightname);
    newLight.setRoom("ROOM 1");
    String bri = STATE["bri"];
    newLight.setBrightness(bri.toInt());
    String hue = STATE["hue"];
    newLight.setHue(hue.toInt());
    String sat = STATE["sat"];
    newLight.setSat(sat.toInt());
    String onOff = STATE["on"];
    newLight.setON(onOff.toInt());
    //XY PARSE
    String xySTR = STATE["xy"];
    newLight.parseXY(xySTR);
    
    /*
    int str_len = xySTR.length() + 1; 
    char char_array[str_len];
    String x_str = "";
    String y_str = "";
    bool commaSWITCH = false;
    // Copy it over 
    
    xySTR.toCharArray(char_array, str_len);
    Serial.println("CHAAAAAAAAAAAR");
    for(int kk=0;kk<str_len;kk++){
      if (xySTR[kk] != '[' && xySTR[kk] != ']'){
        if (xySTR[kk] == ','){
          commaSWITCH = true;
        }
        if(!commaSWITCH && xySTR[kk] != ','){
          x_str = x_str + (String)xySTR[kk];
        }else if (commaSWITCH && xySTR[kk] != ','){
          y_str = y_str + (String)xySTR[kk];
        }
      }
    }
    xySTR.toCharArray(char_array, str_len);

    int x_str_len = x_str.length() + 1; 
    char x_char_array[x_str_len];
    int y_str_len = y_str.length() + 1; 
    char y_char_array[y_str_len];
    
    y_str.toCharArray(y_char_array, y_str_len);
    Serial.println(y_str);
    Serial.println(atof(y_char_array),4);
    */


    newLight.printLightInfo();
    //for (JsonPair kv2 : STATE) {
//Serial.println(kv2.key().c_str());
      //Serial.println(kv.value().as<const char*>());
    //}
  }
}


JsonArray get_hue_bridge() {
  String jsonBody = getUrl(HUE_BRIDGE_URL);

  StaticJsonDocument<2048> jsonDoc;
  deserializeJson(jsonDoc, jsonBody);
  //bool isOn = jsonDoc["state"]["any_on"];
  //Serial.printf("isOn: %d\n", isOn);
  return jsonDoc.as<JsonArray>();
}
void get_hue_lights() {
  JsonArray json = get_hue_bridge();
  for (JsonObject elem : json) {
    const char* name = elem["1"]["swupdate"];
    Serial.println(elem);
  }

  delay(1000);

}
void setup() {
  Serial.begin(115200);
  for (int i = 0; i < 5; i++) {
    Serial.println("Starting");
    delay(100);
  }


  pinMode(LED_PIN, OUTPUT);
  pinMode(INPUT_PIN, INPUT_PULLUP);

  connectToWiFi();
  //toggleLights();
  //  /resource/room/{id}
  initializeLights();
  delay(500);
  //toggleLights();
  //attachInterrupt(digitalPinToInterrupt(INPUT_PIN), handleButton, FALLING);
  //Serial.println("Button interrupt enabled");
}
const char *myurl = "http://" BRIDGE "/api/" API_USERNAME "/lights";




void loop() {
  /**
      String jsonBody = getUrl(HUE_BRIDGE_URL);

    StaticJsonDocument<2048> jsonDoc;
    deserializeJson(jsonDoc, jsonBody);
    String lights = jsonDoc["lights"];

    Serial.println(lights);
    **/
  /*
    //if (shouldTrigger) {
    char *newurl  = "http://" BRIDGE "/api/" API_USERNAME "/lights";

    //toggleLights();
    //shouldTrigger = 0;
      HTTPClient http;
    http.begin(newurl);
    int httpCode = http.GET();
    if (httpCode > 0) {
    Serial.printf("Code: %d\n", httpCode);
    } else {
    Serial.printf("Error: %s\n", http.errorToString(httpCode).c_str());
    }
    Serial.println(http.getString());
  */
  //get_hue_lights();
  //iter();
  changeLightsColor3();
  //}
}
