extern "C" {
#include "button_logic.hpp"
#include "driver/gpio.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
}

static const char *TAG = "button_led+cpp";
// Let's see if workflow does what it is supposed to

static constexpr gpio_num_t LED_GPIO = GPIO_NUM_21;   // XIAO user LED (active-low)
static constexpr gpio_num_t LED2_GPIO = GPIO_NUM_1;   // Additional LED GPIO
static constexpr gpio_num_t BUTTON_GPIO = GPIO_NUM_2; // Expansion board button D1

extern "C" void app_main(void) {
  // Reset pins to a known state (good habit on ESP32)
  gpio_reset_pin(LED_GPIO);
  gpio_reset_pin(LED2_GPIO);
  gpio_reset_pin(BUTTON_GPIO);

  // === Arduino: pinMode(LED_BUILTIN, OUTPUT); ===
  gpio_config_t led_conf = {};
  led_conf.pin_bit_mask = 1ULL << LED_GPIO;
  led_conf.mode = GPIO_MODE_OUTPUT;
  led_conf.pull_up_en = GPIO_PULLUP_DISABLE;
  led_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
  led_conf.intr_type = GPIO_INTR_DISABLE;
  gpio_config(&led_conf);

  gpio_config_t led2_conf = {};
  led2_conf.pin_bit_mask = 1ULL << LED2_GPIO;
  led2_conf.mode = GPIO_MODE_OUTPUT;
  led2_conf.pull_up_en = GPIO_PULLUP_DISABLE;
  led2_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
  led2_conf.intr_type = GPIO_INTR_DISABLE;
  gpio_config(&led2_conf);

  // LED is active-low: make sure it starts OFF (HIGH)
  gpio_set_level(LED_GPIO, 1);
  gpio_set_level(LED2_GPIO, 1);

  // === Arduino: pinMode(buttonPin, INPUT_PULLUP); ===
  gpio_config_t btn_conf = {};
  btn_conf.pin_bit_mask = 1ULL << BUTTON_GPIO;
  btn_conf.mode = GPIO_MODE_INPUT;
  btn_conf.pull_up_en = GPIO_PULLUP_ENABLE; // internal pull-up
  btn_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
  btn_conf.intr_type = GPIO_INTR_DISABLE;
  gpio_config(&btn_conf);

  // Print welcome message
  ESP_LOGI(TAG, "Press the button to turn on the LED.");

  while (1) {
    // === Arduino: buttonState = digitalRead(buttonPin); ===
    int buttonState = gpio_get_level(BUTTON_GPIO); // 1 = not pressed, 0 = pressed

    LedState s = compute_led_state(buttonState);
    gpio_set_level(LED_GPIO, s.led1_level);
    gpio_set_level(LED2_GPIO, s.led2_level);

    vTaskDelay(pdMS_TO_TICKS(10)); // small delay like loop()’s timing
  }
}
