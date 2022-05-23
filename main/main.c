#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <string.h>
#include <esp_log.h>

typedef struct
{
  uint16_t r_val;
  uint16_t g_val;
  uint16_t b_val;
} led_cmd_t;

enum
{
  IDX_CMD_OFF,
  IDX_CMD_GREEN,
  IDX_CMD_RED,
  IDX_CMD_YELLOW,
  IDX_CMD_CYAN,
  IDX_CMD_MAGENTA,
  IDX_CMD_BLUE,
};

static led_cmd_t led_cmd_table[] = {
    [IDX_CMD_OFF] = {
        .r_val = 0,
        .g_val = 0,
        .b_val = 0,
    },
    [IDX_CMD_GREEN] = {
        .r_val = 0,
        .g_val = 255,
        .b_val = 0,
    },
    [IDX_CMD_RED] = {
        .r_val = 255,
        .g_val = 0,
        .b_val = 0,
    },
    [IDX_CMD_YELLOW] = {
        .r_val = 255,
        .g_val = 255,
        .b_val = 0,
    },
    [IDX_CMD_CYAN] = {
        .r_val = 0,
        .g_val = 255,
        .b_val = 255,
    },
    [IDX_CMD_MAGENTA] = {
        .r_val = 255,
        .g_val = 0,
        .b_val = 255,
    },
    [IDX_CMD_BLUE] = {
        .r_val = 0,
        .g_val = 0,
        .b_val = 255,
    },
};

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
    // blue(&val);

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
    uint8_t target_number[NUM_LEDS] = {0, 1, 2, 3};

    turn_off_leds();
    send_led_cmd(&target_number[0], &led_cmd_table[3]);
    vTaskDelay(pdMS_TO_TICKS(TIME_BETWEEN_CYCLE_MS));

    turn_off_leds();
    send_led_cmd(&target_number[2], &led_cmd_table[1]);
    vTaskDelay(pdMS_TO_TICKS(TIME_BETWEEN_CYCLE_MS));

    turn_off_leds();
    send_led_cmd(&target_number[3], &led_cmd_table[2]);
    vTaskDelay(pdMS_TO_TICKS(TIME_BETWEEN_CYCLE_MS));

    turn_off_leds();
    send_led_cmd(&target_number[1], &led_cmd_table[4]);
    vTaskDelay(pdMS_TO_TICKS(TIME_BETWEEN_CYCLE_MS));

    turn_off_leds();
    send_led_cmd(&target_number[2], &led_cmd_table[5]);
    vTaskDelay(pdMS_TO_TICKS(TIME_BETWEEN_CYCLE_MS));

    turn_off_leds();
    send_led_cmd(&target_number[0], &led_cmd_table[6]);
    vTaskDelay(pdMS_TO_TICKS(TIME_BETWEEN_CYCLE_MS));

    turn_off_leds();
    send_led_cmd(&target_number[1], &led_cmd_table[7]);
    vTaskDelay(pdMS_TO_TICKS(TIME_BETWEEN_CYCLE_MS));

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