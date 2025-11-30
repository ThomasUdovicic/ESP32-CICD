#pragma once

// Simple POD struct to hold LED levels
struct LedState {
  int led1_level; // Level for LED 1 (E.g. built-in LED)
  int led2_level; // Level for LED 2 (E.g. additional LED)
};

inline LedState compute_led_state(int buttonState) {
  LedState s{};
  if (buttonState == 1) {
    // Button not pressed -> LEDs off (active-low)
    s.led1_level = 1;
    s.led2_level = 0;
  } else {
    // Button pressed -> LEDs on
    s.led1_level = 0;
    s.led2_level = 1;
  }
  return s;
}