#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"


#define RED_LED 13
#define GREEN_LED 11
#define BLUE_LED 12    

int led_status = 0;

bool repeating_timer_callback(struct repeating_timer *t) {
    gpio_put(RED_LED, 0);
    gpio_put(GREEN_LED, 0);
    gpio_put(BLUE_LED, 0);

    // Verifica o estado do LED e acende o LED correspondente
    if (led_status == 0) { // VERMELHO caso led_status = 0
        printf("VERMELHO ACESO \n");
        gpio_put(RED_LED, 1);
    } else if (led_status == 1) { // AMARELO caso led_status = 1
        printf("AMARELO ACESO \n");
        gpio_put(RED_LED, 1);
        gpio_put(GREEN_LED, 1);
    } else if (led_status == 2) { // VERDE caso led_status = 2
        printf("VERDE ACESO \n");
        gpio_put(GREEN_LED, 1);
    }

    // Atualiza o estado do LED
    led_status = (led_status + 1) % 3;

    // Retorna true para continuar o timer
    return true;
}

int main(){
    int temp = 0;

    stdio_init_all();

    gpio_init(RED_LED);
    gpio_set_dir(RED_LED, true);

    gpio_init(GREEN_LED);
    gpio_set_dir(GREEN_LED, true);

    gpio_init(BLUE_LED);
    gpio_set_dir(BLUE_LED, true);

    struct repeating_timer timer;

    add_repeating_timer_ms(3000, repeating_timer_callback, NULL, &timer);

    while (true) {
        sleep_ms(1000);
        printf("%ds\n", temp);
    }
}
