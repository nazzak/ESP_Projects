#include "IOT.h"
#include "Pushover.h"


IOT::IOT()
{

}

void IOT::setWIFI(const char * _wifi_ssid,
                  const char * _wifi_pwd)
{
  m_wifi_ssid = _wifi_ssid;
  m_wifi_pwd = _wifi_pwd;
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
}

void IOT::setMQTT(const char * _mqtt_server,
                  const char * _mqtt_topic,
                  const char * _mqtt_user,
                  const char * _mqtt_password)
{
  m_mqtt_server = _mqtt_server;
  m_mqtt_topic = _mqtt_topic;
  m_mqtt_user = _mqtt_user;
  m_mqtt_password = _mqtt_password;
  m_clientMqtt = new PubSubClient(m_espClient);
}

void IOT::setPUSHOVER(String _token, String _user)
{
  m_pushnotif = new Pushover(_token, _user);
}

void IOT::setIFTTT(String _ifttt_key, String _ifttt_event_name)
{
  m_ifttt_key = _ifttt_key;
  m_ifttt_event = _ifttt_event_name;
  m_ifttt = new IFTTTMaker(_ifttt_key, m_espClientSec);
}

void IOT::setMessage(const char * _toSEND)
{
  m_toSEND = _toSEND;
}

void IOT::setLED(const uint8_t _led_state)
{
  m_led_state = _led_state;
  pinMode(m_led_state, OUTPUT);
  digitalWrite(m_led_state, HIGH);
}

void IOT::go()
{
  startWifi();
  if (m_clientMqtt != NULL)
  m_clientMqtt->setServer(m_mqtt_server, 1883);

  do
  {
    if (m_clientMqtt != NULL)
    {
      if (!m_clientMqtt->connected())
        reconnect();

      m_clientMqtt->loop();
    }
    delay(5000);
    
    digitalWrite(m_led_state, LOW);
    delay(50);
    digitalWrite(m_led_state, HIGH);
    
    if (m_clientMqtt != NULL)
      m_clientMqtt->publish(m_mqtt_topic, m_toSEND, true);
    else
      Serial.println("Mqtt not used");

    if (m_pushnotif != NULL)
    {
      m_pushnotif->setMessage(m_toSEND);
      m_pushnotif->send();
    }
    else
      Serial.println("Pushover not used");

    if (m_ifttt != NULL)
    {
      m_ifttt->triggerEvent(m_ifttt_event, "test1", "test2");
    }
    else
      Serial.println("IFTTT not used");

  } while (1);
}

void IOT::useSerial(const long _speed)
{
  Serial.begin(_speed);
}

void IOT::startWifi()
{
  delay(10);

  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(m_wifi_ssid);

  WiFi.begin(m_wifi_ssid, m_wifi_pwd);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    digitalWrite(m_led_state, LOW);
    delay(50);
    digitalWrite(m_led_state, HIGH);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("MAC address: ");
  Serial.println(WiFi.macAddress());
}

void IOT::reconnect()
{

  while (!m_clientMqtt->connected())
  {
    Serial.print("Attempting MQTT connection...");
    if (m_clientMqtt->connect("ESP8266Client", m_mqtt_user, m_mqtt_password)) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(m_clientMqtt->state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(10000);
    }
  }
}

