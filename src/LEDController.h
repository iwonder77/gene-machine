#pragma once

#include <Arduino.h>
#include <FastLED.h>

static constexpr uint8_t NUM_STRIPS = 4;
static constexpr uint8_t LEDS_PER_STRIP = 9;
static constexpr uint8_t DATA_PINS[NUM_STRIPS] = {1, 2, 3, 15};

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
  StripState strips_state_[NUM_STRIPS] = {};
  CRGB leds_[NUM_STRIPS][LEDS_PER_STRIP];

  void renderIdle(uint8_t strip, uint32_t now);
  void renderTrail(uint8_t strip, uint32_t now, CRGB color);
};
