#pragma once

#include <Arduino.h>

namespace config {
// ----- PIN DEFINITIONS -----
constexpr uint8_t I2C_SDA = 16;
constexpr uint8_t I2C_SCL = 17;

// ----- CONSTANTS -----
constexpr uint8_t CHANNEL_SWITCH_SETTLE_MS = 1;

// ----- RFID2 READER -----
constexpr uint16_t POLL_INTERVAL_MS =
    50; // how often to poll all readers for tags (ms)
constexpr uint32_t TAG_DEBOUNCE_TIME = 150; // debounce time for tag detection
constexpr uint32_t TAG_ABSENCE_TIMEOUT =
    450; // time before considering tag removed
constexpr uint8_t TAG_PRESENCE_THRESHOLD = 3; // num fails before marking absent
constexpr uint8_t TAG_START_PAGE = 4; // page # to read data from in tag memory
constexpr uint8_t MAX_READ_ATTEMPTS = 5;
constexpr uint8_t NUM_READERS = 4;

// ----- I2C ADDRESSES -----
constexpr uint8_t MUX_ADDR = 0x70;
constexpr uint8_t WS1850S_I2C_ADDR = 0x28;

// ----- W5500 ETHERNET MODULE PINS -----
// ESP32-S3-ETH onboard W5500 SPI mapping
// (ref: https://www.waveshare.com/wiki/ESP32-S3-ETH)
constexpr uint8_t W5500_CS = 14;
constexpr uint8_t W5500_RST = 9;
constexpr uint8_t W5500_INT = 10; // optional interrupt line, not polled
constexpr uint8_t W5500_MISO = 12;
constexpr uint8_t W5500_MOSI = 11;
constexpr uint8_t W5500_SCK = 13;

// ----- NETWORK CONFIG -----
static const uint8_t MAC_ADDR[6] = {0xDE, 0xAD, 0xBE, 0xEF, 0x00, 0x01};
static const uint8_t LOCAL_IP[4] = {192, 168, 50, 2};   // ESP32 static IP
static const uint8_t TARGET_IP[4] = {192, 168, 50, 10}; // BrightSign target IP
constexpr uint16_t UDP_PORT = 5000;
constexpr uint32_t LINK_TIMEOUT_MS =
    10000; // how long to wait for link on boot (ms)
} // namespace config
