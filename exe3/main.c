#include <stdio.h>

#include "hardware/gpio.h"
#include "pico/stdlib.h"

static const int LED_PIN_R = 4;
static const int LED_PIN_G = 6;

static const int BTN_PIN_R = 28;
static const int BTN_PIN_G = 26;

int main(void) {
    stdio_init_all();

    gpio_init(LED_PIN_R);
    gpio_set_dir(LED_PIN_R, GPIO_OUT);

    gpio_init(LED_PIN_G);
    gpio_set_dir(LED_PIN_G, GPIO_OUT);

    gpio_init(BTN_PIN_R);
    gpio_set_dir(BTN_PIN_R, GPIO_IN);
    gpio_pull_up(BTN_PIN_R);

    gpio_init(BTN_PIN_G);
    gpio_set_dir(BTN_PIN_G, GPIO_IN);
    gpio_pull_up(BTN_PIN_G);

    int led_r = 0;
    int led_g = 0;

    int last_r = 1; // pull-up => solto = 1
    int last_g = 1; // pull-up => solto = 1

    while (true) {
        int cur_r = gpio_get(BTN_PIN_R);
        int cur_g = gpio_get(BTN_PIN_G);

        // Detecta borda de descida: 1 -> 0 (apertou)
        if (last_r && !cur_r) {
            led_r = !led_r;
            gpio_put(LED_PIN_R, led_r);
        }

        if (last_g && !cur_g) {
            led_g = !led_g;
            gpio_put(LED_PIN_G, led_g);
        }

        last_r = cur_r;
        last_g = cur_g;

    }
}