#include <ESP8266WiFi.h>
#include <Wire.h>
#include <PubSubClient.h>
#include "Pushover.h"
#include "IFTTTMaker.h"

#include "defines.hpp"

class IOT {

  private:
    const char * m_wifi_ssid;
    const char * m_wifi_pwd;
    const char * m_mqtt_server;
    const char * m_mqtt_topic;
    const char * m_mqtt_user;
    const char * m_mqtt_password;
    String m_ifttt_key;
    String m_ifttt_event;

    const char * m_toSEND;

    uint8_t m_led_state;


    WiFiClient m_espClient;
    WiFiClientSecure m_espClientSec;
    PubSubClient *m_clientMqtt = NULL;
    Pushover *m_pushnotif = NULL;
    IFTTTMaker *m_ifttt = NULL;

  public:
    IOT();
    void go(void);

    void setWIFI(const char * _wifi_ssid = WIFI_SSID,
                 const char * _wifi_pwd = WIFI_PASSWORD);

    void setMQTT(const char * _mqtt_server = MQTT_SERVER,
                 const char * _mqtt_topic = MQTT_TOPIC,
                 const char * _mqtt_user = MQTT_USER,
                 const char * _mqtt_password = MQTT_PASSWORD);

    void setPUSHOVER(String _token = PUSHOVER_TOKEN, String _user = PUSHOVER_USER);

    void setIFTTT(String _ifttt_key = IFTTT_KEY, String _ifttt_event_name = IFTTT_EVENT_NAME);

    void setMessage(const char * _toSEND = "");

    void setLED(uint8_t _led_state = LED_STATE);

    void useSerial(const long _speed = SERIAL_SPEED);

    void startWifi(void);
    void reconnect(void);

};
