#include <FastLED.h>
#include <cmath>

#include "LEDController.h"

void LEDController::init() {
  FastLED.addLeds<WS2815, DATA_PINS[0], GRB>(leds_[0], LEDS_PER_STRIP);
  FastLED.addLeds<WS2815, DATA_PINS[1], GRB>(leds_[1], LEDS_PER_STRIP);
  FastLED.addLeds<WS2815, DATA_PINS[2], GRB>(leds_[2], LEDS_PER_STRIP);
  FastLED.addLeds<WS2815, DATA_PINS[3], GRB>(leds_[3], LEDS_PER_STRIP);
  FastLED.setBrightness(125); // max global, we control per-LED

  // brief startup sequence
  // startup: flash all strips to confirm wiring
  CRGB testColors[] = {CRGB::Red, CRGB::Green, CRGB::Blue, CRGB::White,
                       CRGB::Black};
  for (auto color : testColors) {
    for (uint8_t i = 0; i < NUM_STRIPS; i++) {
      fill_solid(leds_[i], LEDS_PER_STRIP, color);
    }
    FastLED.show();
    delay(200);
  }
}

void LEDController::update() {
  uint32_t now = millis();

  for (uint8_t i = 0; i < NUM_STRIPS; i++) {
    switch (strips_state_[i].animation) {
    case AnimationType::Idle:
      renderIdle(i, now);
      break;
    case AnimationType::TrailGreen:
      renderTrail(i, now, CRGB(0, 255, 0));
      break;
    case AnimationType::TrailBlue:
      renderTrail(i, now, CRGB(0, 0, 255));
      break;
    }
  }

  FastLED.show(); // one call pushes all strips
}

void LEDController::setAnimation(uint8_t strip, AnimationType type) {
  if (strip >= NUM_STRIPS)
    return;
  strips_state_[strip].animation = type;
  strips_state_[strip].start_time = millis();
}

void LEDController::renderIdle(uint8_t strip, uint32_t now) {
  const CRGB baseColor = CRGB(180, 130, 255); // lavender
  const uint8_t minBright = 40;
  const uint8_t maxBright = 200;
  const uint16_t period = 3000; // 3 second full breath cycle

  uint32_t elapsed = (now - strips_state_[strip].start_time) % period;
  float angle = (2.0f * PI * elapsed) / period;
  float wave = (sin(angle) + 1.0f) / 2.0f;
  uint8_t brightness = minBright + wave * (maxBright - minBright);

  // scale color by brightness rather than using global setBrightness
  CRGB color = baseColor;
  color.nscale8(brightness);

  fill_solid(leds_[strip], LEDS_PER_STRIP, color);
}

void LEDController::renderTrail(uint8_t strip, uint32_t now, CRGB color) {
  const float trailLength = 5.0f;
  const float speedMsPerLed = 100.0f;
  uint32_t elapsed = now - strips_state_[strip].start_time;

  float position = fmod(elapsed / speedMsPerLed, (float)LEDS_PER_STRIP);

  for (uint8_t i = 0; i < LEDS_PER_STRIP; i++) {
    // how far behind the head is this LED (wrapping around)?
    float distance =
        fmod((float)LEDS_PER_STRIP + position - i, (float)LEDS_PER_STRIP);

    if (distance < trailLength) {
      float brightness = 1.0f - (distance / trailLength);
      CRGB pixel = color;
      pixel.nscale8((uint8_t)(brightness * 255));
      leds_[strip][i] = pixel;
    } else {
      leds_[strip][i] = CRGB::Black;
    }
  }
}
