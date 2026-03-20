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

// ----- SEQUENCE LOOK UP TABLE -----
constexpr uint8_t NUM_SEQUENCES = 16; // 2^4

// index of array corresponds to bit-packed sequence
// leftmost slot (slot 0) represents LSB
// rightmost slot (slot 3) represents MSB
// AT = 0, CG = 1
// ex: Sequence AT-CG-AT-CG --> 0b1010 = index 10
const char *const VIDEO_COMMANDS[NUM_SEQUENCES] = {
    "amber_eyes",    // 0b0000 = 0  , AT-AT-AT-AT
    "black_hair",    // 0b0001 = 1  , CG-AT-AT-AT
    "blond_hair",    // 0b0010 = 2  , AT-CG-AT-AT
    "blue_eyes",     // 0b0011 = 3  , CG-CG-AT-AT
    "brown_eyes",    // 0b0100 = 4  , AT-AT-CG-AT
    "brown_hair",    // 0b0101 = 5  , CG-AT-CG-AT
    "coily_hair",    // 0b0110 = 6  , AT-CG-CG-AT
    "curly_hair",    // 0b0111 = 7  , CG-CG-CG-AT
    "freckles",      // 0b1000 = 8  , AT-AT-AT-CG
    "gray_eyes",     // 0b1001 = 9  , CG-AT-AT-CG
    "green_eyes",    // 0b1010 = 10 , AT-CG-AT-CG
    "hazel_eyes",    // 0b1011 = 11 , CG-CG-AT-CG
    "myopia",        // 0b1100 = 12 , AT-AT-CG-CG
    "red_hair",      // 0b1101 = 13 , CG-AT-CG-CG
    "straight_hair", // 0b1110 = 14 , AT-CG-CG-CG
    "wavy_hair",     // 0b1111 = 15 , CG-CG-CG-CG
};
} // namespace config
