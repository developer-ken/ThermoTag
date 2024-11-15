#include <Arduino.h>

#include <M1820.h>
#include <OneWire.h>
#include <ESPNowW.h>
#include <ESP8266WiFi.h>

#include "pinout.h"
#include "protocol.h"

#define SAMPLE_INTERVAL 2000 // 采样间隔，毫秒
#define BRIGHTNESS 1         // LED指示灯亮度，0-255

#define BAUDRATE 74880

uint8_t LISTENER_ADDRESS[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
//uint8_t LISTENER_ADDRESS[] = {0xd4, 0x8a, 0xFc, 0x29, 0x95, 0x2f};
uint8_t fw = 51;
bool direction = true;
OneWire oneWire(SDA_PIN);
M1820 sensor(&oneWire);

void setup()
{
  // Serial.begin(BAUDRATE);
  // Serial.printf("\n");
  pinMode(LED_PIN, OUTPUT);
  analogWriteFreq(1000);
  analogWrite(LED_PIN, 255 - BRIGHTNESS);
  {
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    ESPNow.init();
    ESPNow.add_peer(LISTENER_ADDRESS);
  }
  M1820::SampleNow();
  float temperature = M1820::receiveTemperatureSkipRom();
  ReportPack pack;
  pack.Temperature = temperature;
  pack.Charging = digitalRead(CHARGE_DETECT_PIN);
  pack.BatteryLevel = analogRead(0) * 55.45454 / 1024;
  // Serial.printf("T=%.2f\n", pack.Temperature);
  // Serial.printf("V=%d\n", pack.BatteryLevel);
  // Serial.printf("C=%d\n", pack.Charging);
  ESPNow.send_message(LISTENER_ADDRESS, (uint8_t *)&pack, sizeof(ReportPack));
  //  if (temperature < -100)
  //  {
  //    Serial.begin(115200);
  //    Serial.println("ERROR: Sensor communication error.");
  //    delay(100);
  //    digitalWrite(LED_PIN, HIGH);
  //    ESP.reset();
  //    return;
  //  }
  //  digitalWrite(LED_PIN, HIGH);
  ESP.deepSleep(SAMPLE_INTERVAL * 1000 - millis());
}

void loop()
{
  digitalWrite(LED_PIN, LOW);
}