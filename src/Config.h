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

// ----- I2C ADDRESSES -----
constexpr uint8_t MUX_ADDR = 0x70;
constexpr uint8_t WS1850S_I2C_ADDR = 0x28;
} // namespace config
