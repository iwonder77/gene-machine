/**
 * Project: Gene Machine interactive
 * File: gene-machine.ino
 * Description: Scan tags with RFID modules on every MUX channel to poll for nucleotide 
 *              pieces, animate LED lights and send UDP packets according to 
 *              order/sequence of nucelotide pieces
 *
 * Author: Isai Sanchez
 * Date: 3-16-26
 * MCU Board: Waveshare ESP32-S3-ETH
 * Hardware:
 *  - RFID2 Module: M5Stack RFID2 (WS1850S, I2C @ 0x28)
 *  - I2C Multiplexer: TCA9548A
 * Libraries:
 *  - Wire.h
 *  - MFRC522v2.h (https://github.com/OSSLibraries/Arduino_MFRC522v2/tree/master)
 *  - MFRC522DriverI2C.h
 *  - MFRC522Debug.h
 * Notes:
 *  - ESP32-S3 GPIO matrix allows I2C on almost any pin via Wire.begin(SDA_PIN, SCL_PIN)
 *  - WS1850S version check bypassed — known quirk with this module vs pure MFRC522
 *
 * (c) Thanksgiving Point Exhibits Electronics Team — 2025
 */

#include <Wire.h>

#include "src/Config.h"
#include "src/Reader.h"
#include "src/SequenceManager.h"

Reader readers[] = { { "ch_0", 0 }, { "ch_1", 1 }, { "ch_2", 2 }, { "ch_3", 3 } };
SequenceManager sequencer;
uint32_t last_poll_time = 0;

void onEvent(const Event& event) {
  sequencer.handleEvent(event);
}

void setup() {
  Serial.begin(115200);
  while (!Serial) { delay(10); }  // wait for USB CDC Serial on ESP32-S3

  Wire.begin(config::I2C_SDA, config::I2C_SCL);
  Wire.setClock(400000);  // RFID2 supports 400 kHz fast mode; reduces read latency
  delay(100);

  for (int i = 0; i < config::NUM_READERS; i++) {
    readers[i].init();
    readers[i].setCallback(onEvent);
  }

  Serial.println("=== RFID Scanner Ready ===");
  Serial.print("I2C SDA: GPIO");
  Serial.println(config::I2C_SDA);
  Serial.print("I2C SCL: GPIO");
  Serial.println(config::I2C_SCL);
}

void loop() {
  uint32_t now = millis();
  if (now - last_poll_time >= config::POLL_INTERVAL_MS) {
    for (int i = 0; i < config::NUM_READERS; i++) {
      readers[i].update();
    }
    last_poll_time = now;
  }
}
