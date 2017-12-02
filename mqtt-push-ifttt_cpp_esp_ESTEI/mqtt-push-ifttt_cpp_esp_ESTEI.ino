// Author : Nazim SAIBI
// Date : 22/10/2017
// MQTT tested with Docker
// MQTT Broker : the open source Mosquitto
// The device is a MQTT publisher
// Pushover
// IFTTT
// You have to choose between MQTT+Pushover and IFTTT,
// because MQTT needs a WIFIClient to work in this project
// whereas IFTTT needs WIFIClientSecure


#include "IOT.h"

#define PUSH_MQTT


void setup() {
  IOT node;
  node.useSerial(115200);
  node.setWIFI("ssid", "password");

#ifdef PUSH_MQTT
  node.setMQTT("192.168.1.21", "topic", "user", "password");
  node.setPUSHOVER("API Token/Key", "User Key");
#else
  node.setIFTTT("Webhooks_api_key", "Webhooks_event");
#endif

  node.setLED(16);  //valid for nodemcu
  node.setMessage("test mqtt : ESTEI");
  node.go();
}


void loop() {

}
