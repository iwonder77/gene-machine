#pragma once
/**
 * SequenceManager.h
 *
 * Central coordinator for executing critical exhibit logic (detecting
 * sequences, sending udp packets, letting LED controller know what to animate,
 * etc)
 */
#include <Arduino.h>

#include "Config.h"
#include "EthernetController.h"
#include "Event.h"
#include "GeneMachineTag.h"
#include "LEDController.h"

class SequenceManager {
public:
  SequenceManager(EthernetController &ethernet, LEDController &leds)
      : ethernet_(ethernet), leds_(leds) {}
  // void update();
  void handleEvent(const Event &event);
  void printSequence();
  void printEvent(const Event &event);

private:
  gene_tag::NucleotidePair slots_[config::NUM_READERS] = {};
  bool sequence_complete_ = false;

  EthernetController &ethernet_;
  LEDController &leds_;

  uint8_t buildSequenceIndex();
};
