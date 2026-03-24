#pragma once

#include "Config.h"
#include <Arduino.h>
#include <FastLED.h>

enum class AnimationType : uint8_t {
  Idle,       // lavender breathing
  TrailGreen, // AT piece — green running trail
  TrailBlue   // CG piece — blue running trail
};

struct StripState {
  AnimationType animation = AnimationType::Idle;
  uint32_t start_time = 0; // when this animation began
};

class LEDController {
public:
  void init();
  void update();
  void setAnimation(uint8_t strip, AnimationType type);

private:
  StripState strips_state_[config::NUM_STRIPS] = {};
  CRGB leds_[config::NUM_STRIPS][config::LEDS_PER_STRIP];

  void renderIdle(uint8_t strip, uint32_t now);
  void renderTrail(uint8_t strip, uint32_t now, CRGB color);
};
