#pragma once

#include <Arduino.h>
#include <MFRC522Debug.h>
#include <MFRC522DriverI2C.h>
#include <MFRC522v2.h>
#include <Wire.h>

#include "Config.h"
#include "Event.h"
#include "GeneMachineTag.h"
#include "MuxController.h"

enum class TagState : uint8_t {
  Absent,    // no tag present, waiting for first detection
  Detecting, // first detection, now must pass debounce
  Confirmed, // debounce passed, reading data
  Departing  // stopped seeing tag, confirming removal w/ debounce
};

// Reader class owns channel switching on mux for now
struct MuxGuard {
  MuxGuard(uint8_t ch) { MuxController::selectChannel(ch); }
  ~MuxGuard() { MuxController::disableChannel(); }
};

class Reader {
public:
  Reader(const char *name, uint8_t channel)
      : name_(name), channel_(channel), driver_(config::WS1850S_I2C_ADDR, Wire),
        reader_(driver_) {};

  void init();
  void update();
  void printStatus() const;

  void setCallback(EventCallback cb) { callback_ = cb; }

  TagState getTagState() const { return tag_state; };
  uint8_t getChannel() const { return channel_; }
  bool getReaderStatus() const { return reader_ok; }
  gene_tag::NucleotidePair getPair() const { return tag_.pair; };

private:
  const char *name_;
  uint8_t channel_;
  MFRC522DriverI2C driver_;
  MFRC522 reader_;
  bool reader_ok = false;

  EventCallback callback_ = nullptr;

  gene_tag::TagData tag_;
  bool tag_identified_ = false;
  uint8_t read_attempts_ = 0;

  TagState tag_state = TagState::Absent;
  uint32_t last_seen_time = 0;
  uint32_t first_seen_time = 0;

  uint8_t consecutive_fails = 0;
  uint8_t last_UID[10]{};
  uint8_t last_UID_length = 0;

  void clearTagData();
  void readTagData();
  bool compareUID(uint8_t *uid1, uint8_t len1, uint8_t *uid2, uint8_t len2);
};
