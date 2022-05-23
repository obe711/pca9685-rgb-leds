#include <pca9685.h>

#define ADDR PCA9685_ADDR_BASE
#ifndef APP_CPU_NUM
#define APP_CPU_NUM PRO_CPU_NUM
#endif

#ifndef CONFIG_LED_I2C_MASTER_SDA
#define CONFIG_LED_I2C_MASTER_SDA 21
#endif

#ifndef CONFIG_LED_I2C_MASTER_SCL
#define CONFIG_LED_I2C_MASTER_SCL 22
#endif

#ifndef CONFIG_LED_PWM_FREQ_HZ
#define CONFIG_LED_PWM_FREQ_HZ 60
#endif
#ifndef BLUE_LED_PIN_INDEX
#define BLUE_LED_PIN_INDEX 0
#endif

#ifndef GREEN_LED_PIN_INDEX
#define GREEN_LED_PIN_INDEX 1
#endif

#ifndef RED_LED_PIN_INDEX
#define RED_LED_PIN_INDEX 2
#endif

static const char *PCA_LED_TAG = "pca9685_leds";
static i2c_dev_t dev;

static uint16_t default_led_values[12] = {4096, 4096, 4096, 4096, 4096, 4096, 4096, 4096, 4096, 4096, 4096, 4096};

// LEDs off
void init_leds(void)
{
  for (int i = 0; i < sizeof default_led_values / sizeof *default_led_values; i++)
  {
    default_led_values[i] = 4096;
  }
}

// Value setters
void set_led_value(uint8_t led_index, uint16_t *led_value)
{
  uint16_t pwm_value = 4096 - ((*led_value) * 16);
  default_led_values[0 + led_index] = pwm_value;
  default_led_values[3 + led_index] = pwm_value;
  default_led_values[6 + led_index] = pwm_value;
  default_led_values[9 + led_index] = pwm_value;
}
void set_red(uint16_t *red_value)
{
  set_led_value(RED_LED_PIN_INDEX, red_value);
}
void set_green(uint16_t *green_value)
{
  set_led_value(GREEN_LED_PIN_INDEX, green_value);
}
void set_blue(uint16_t *blue_value)
{
  set_led_value(BLUE_LED_PIN_INDEX, blue_value);
}

// Color setters
void turn_off_leds(void)
{
  init_leds();
  if (pca9685_set_pwm_values(&dev, 0, 12, default_led_values) != ESP_OK)
    ESP_LOGE(PCA_LED_TAG, "Could not set PWM values");
}
void red(uint16_t *red_value)
{
  init_leds();
  set_red(red_value);
  if (pca9685_set_pwm_values(&dev, 0, 12, default_led_values) != ESP_OK)
    ESP_LOGE(PCA_LED_TAG, "Could not set PWM values");
}
void green(uint16_t *green_value)
{
  init_leds();
  set_green(green_value);
  if (pca9685_set_pwm_values(&dev, 0, 12, default_led_values) != ESP_OK)
    ESP_LOGE(PCA_LED_TAG, "Could not set PWM values");
}
void blue(uint16_t *blue_value)
{
  init_leds();
  set_blue(blue_value);
  if (pca9685_set_pwm_values(&dev, 0, 12, default_led_values) != ESP_OK)
    ESP_LOGE(PCA_LED_TAG, "Could not set PWM values");
}
void yellow(uint16_t *yellow_value)
{
  init_leds();
  // Red
  set_red(yellow_value);
  // Green
  set_green(yellow_value);
  if (pca9685_set_pwm_values(&dev, 0, 12, default_led_values) != ESP_OK)
    ESP_LOGE(PCA_LED_TAG, "Could not set PWM values");
}
void magenta(uint16_t *magenta_value)
{
  init_leds();
  // Red
  set_red(magenta_value);
  // Blue
  set_blue(magenta_value);
  if (pca9685_set_pwm_values(&dev, 0, 12, default_led_values) != ESP_OK)
    ESP_LOGE(PCA_LED_TAG, "Could not set PWM values");
}
void cyan(uint16_t *cyan_value)
{
  init_leds();
  // Green
  set_green(cyan_value);
  // Blue
  set_blue(cyan_value);
  if (pca9685_set_pwm_values(&dev, 0, 12, default_led_values) != ESP_OK)
    ESP_LOGE(PCA_LED_TAG, "Could not set PWM values");
}

void led_to_rgb(uint16_t *r_value, uint16_t *g_value, uint16_t *b_value)
{
  init_leds();
  // Red
  set_red(r_value);
  // Green
  set_green(g_value);
  // Blue
  set_blue(b_value);
  if (pca9685_set_pwm_values(&dev, 0, 12, default_led_values) != ESP_OK)
    ESP_LOGE(PCA_LED_TAG, "Could not set PWM values");
}

void init_pca9685_leds(void)
{
  // Init i2cdev library
  ESP_ERROR_CHECK(i2cdev_init());

  memset(&dev, 0, sizeof(i2c_dev_t));
  ESP_ERROR_CHECK(pca9685_init_desc(&dev, ADDR, 0, CONFIG_LED_I2C_MASTER_SDA, CONFIG_LED_I2C_MASTER_SCL));
  ESP_ERROR_CHECK(pca9685_init(&dev));

  ESP_ERROR_CHECK(pca9685_restart(&dev));

  uint16_t freq;
  ESP_ERROR_CHECK(pca9685_set_pwm_frequency(&dev, CONFIG_LED_PWM_FREQ_HZ));
  ESP_ERROR_CHECK(pca9685_get_pwm_frequency(&dev, &freq));

  ESP_LOGI(PCA_LED_TAG, "Freq %dHz, real %d", CONFIG_LED_PWM_FREQ_HZ, freq);
}
