#ifndef IFTTTMaker_h
#define IFTTTMaker_h

#include <Arduino.h>
#include <Client.h>
#include <ArduinoJson.h>

#define HOST "maker.ifttt.com"
#define SSL_PORT 443


class IFTTTMaker
{
  public:
    IFTTTMaker (String key, Client &client);
    String sendTriggerEvent(String eventName);
    String sendTriggerEventWithData(String eventName, JsonObject& payload);
    bool triggerEvent(String eventName, String value1 = "", String value2 = "", String value3 = "");

  private:
    String _key;
    Client *client;
    const int maxMessageLength = 1000;
    bool checkForSucessResponse(String response);
};

#endif
