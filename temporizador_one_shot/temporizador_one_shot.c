#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"

#define RED_LED 13
#define GREEN_LED 11
#define BLUE_LED 12
#define BUTTON_A 5

int led_status = 0;
bool led_on = false;

int64_t turn_off_callback(alarm_id_t, void *user_data) {
    if(led_status == 0){
        gpio_put(RED_LED, 0);
        printf("Led vermelho apagado\n");
        led_status = 1;
        add_alarm_in_ms(3000, turn_off_callback, NULL, false);
    }else if(led_status == 1){
        gpio_put(GREEN_LED, 0);
        printf("Led verde apagado\n");
        led_status = 2;
        add_alarm_in_ms(3000, turn_off_callback, NULL, false);
    }else if(led_status == 2){
        gpio_put(BLUE_LED, 0);
        printf("Led azul apagado\n");
        led_status = 0;
    }
    return 0;
}


int main(){
    stdio_init_all();

    gpio_init(RED_LED);
    gpio_set_dir(RED_LED, GPIO_OUT);

    gpio_init(GREEN_LED);
    gpio_set_dir(GREEN_LED, GPIO_OUT);

    gpio_init(BLUE_LED);
    gpio_set_dir(BLUE_LED, GPIO_OUT);

    gpio_init(BUTTON_A);
    gpio_set_dir(BUTTON_A, GPIO_IN);
    gpio_pull_up(BUTTON_A);


    while (true) {
        if(gpio_get(BUTTON_A) == 0 && !led_on){
            sleep_ms(50);


            if(gpio_get(BUTTON_A)==0){
                gpio_put(RED_LED, 1);
                gpio_put(GREEN_LED, 1);
                gpio_put(BLUE_LED, 1);

                led_on = true;

                led_status = 0;

                add_alarm_in_ms(3000, turn_off_callback, NULL, false);
            }
        }
        sleep_ms(10);
    }

}
