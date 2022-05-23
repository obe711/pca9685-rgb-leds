#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <string.h>
#include <esp_log.h>

#include "pca9685_leds.h"

#define TIME_BETWEEN_CYCLE_MS 1000

static const char *TAG = "pca9685_test";

void pca9685_test(void *pvParameters)
{

  uint16_t val = 0;

  while (1)
  {
    if (!(val % 100))
      ESP_LOGI(TAG, "CH0 = %-4d | CH3 = %-4d", val, PCA9685_MAX_PWM_VALUE - val);

    // Red
    // red(&val);

    // Green
    // green(&val);

    // Blue
    blue(&val);

    // Yellow
    // yellow(&val);

    // Magenta
    // magenta(&val);

    // Cyan
    // cyan(&val);

    // To RGB color
    // uint16_t r_val = 255;
    // uint16_t g_val = 0;
    // uint16_t b_val = 170;
    // led_to_rgb(&r_val, &g_val, &b_val);

    // Flicker colors
    // red(&val);
    // green(&val);

    // Reset
    if (val++ > 255)
    {
      val = 0;
      // init_leds();
      // - or -
      turn_off_leds();
      vTaskDelay(pdMS_TO_TICKS(TIME_BETWEEN_CYCLE_MS));
    }
  }
}

void app_main()
{
  // Init LED library
  init_pca9685_leds();

  xTaskCreatePinnedToCore(pca9685_test, TAG, configMINIMAL_STACK_SIZE * 3, NULL, 5, NULL, APP_CPU_NUM);
}