// This example is based on this tutorial
// https://www.instructables.com/id/Converting-Images-to-Flash-Memory-Iconsimages-for-/
// https://github.com/STEMpedia/eviveProjects/blob/master/imageToFlashMemoryIconsForTFT/

//Don't forget to change User_Setup.h inside TFT_eSPI library !

#include <TFT_eSPI.h>
#include <feelsgood.h>
#include <ESP8266WiFi.h>
#include <FS.h>
#include <LittleFS.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>

const int ledPin=13;
String ledState;

#define ssid "memeLCD" // Replace with your network name
#define password "123456789" // Replace with your network password
AsyncWebServer server(80);

TFT_eSPI tft = TFT_eSPI();   // Invoke library

void setup(void) {
  Serial.begin(9600);

  WiFi.softAP(ssid,password);

  // Initialize LittleFS
  if(!LittleFS.begin()){
    Serial.println("An Error has occurred while mounting LittleFS");
    return;
  }
  pinMode(ledPin, OUTPUT);
//website ---------------

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(LittleFS, "/index.html", String(), false);
  });
  
  // Route to load style.css file
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(LittleFS, "/style.css", "text/css");
  });

  // Start server
  server.begin();

//------------------




  tft.begin();     
  tft.setSwapBytes(true); // Swap the byte order for pushImage() - corrects endianness
  tft.fillScreen(TFT_WHITE);
  
}

void loop() {
  
  for(int i=0; i < frames; i++){
      tft.pushImage(0,0,animation_width,animation_height,animation[i]);
      delay(100);
      };
   for(int y=frames; y>0; y--){
       tft.pushImage(0,0,animation_width,animation_height,animation[y-1]);
       delay(100);
       };
}