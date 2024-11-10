#include <Arduino.h>

#include <M1820.h>
#include <espnow.h>
#include <OneWire.h>
#include <ESP8266WiFi.h>

#include "pinout.h"
#include "protocol.h"

#define BAUDRATE 74880

uint8_t BROADCAST_ADDRESS[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

bool received = false;
uint8_t mac[6];
ReportPack pack;

void onReceive(uint8_t *mac_addr, uint8_t *data, uint8_t len)
{
  if (len != sizeof(ReportPack))
    return; // 忽略长度不匹配的数据包
  pack = *((ReportPack *)data);
  memcpy(mac, mac_addr, 6);
  received = true;
}

void setup()
{
  Serial.begin(BAUDRATE);
  Serial.printf("\n");
  analogWriteFreq(1000);
  WiFi.mode(WIFI_STA);
  WiFi.begin();
  wifi_promiscuous_enable(1);
  wifi_set_channel(2);
  wifi_promiscuous_enable(0);
  WiFi.disconnect();
  esp_now_init();
  esp_now_register_recv_cb(onReceive);
  Serial.printf("EVT:SETUP;\n");
}

void loop()
{
  if (received)
  {
    received = false;
    analogWrite(LED_PIN, LOW);
    Serial.printf("EVT:BEGIN_REPORT;\n");
    Serial.printf("SRC:%02X%02X%02X%02X%02X%02X;\n", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
    Serial.printf("TMP:%.2f;\n", pack.Temperature);
    Serial.printf("BAT:%d;\n", pack.BatteryLevel);
    Serial.printf("CHG:%d;\n", pack.Charging);
    Serial.printf("EVT:END_REPORT;\n");
    digitalWrite(LED_PIN, HIGH);
  }
}
