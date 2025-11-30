// tests/test_led_logic.cpp
#include "button_logic.hpp"
#include <cassert>
#include <iostream>

int main() {
  {
    // Not pressed: buttonState = 1
    LedState s = compute_led_state(1);
    assert(s.led1_level == 1); // active-low LED off
    assert(s.led2_level == 0); // second LED off
  }

  {
    // Pressed: buttonState = 0
    LedState s = compute_led_state(0);
    assert(s.led1_level == 0); // active-low LED on
    assert(s.led2_level == 1); // second LED on
  }

  std::cout << "All led_logic tests passed.\n";
  return 0;
}
