#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"

// Definição dos pinos dos LEDs e do botão
#define RED_LED 13
#define GREEN_LED 11
#define BLUE_LED 12
#define BUTTON_A 5

// Variáveis de controle do estado dos LEDs
int led_status = 0;
bool led_on = false;
bool debounce_lock = false; // Variável para evitar múltiplas ativações durante o debounce

/**
 * @brief Callback do temporizador one-shot para desligar os LEDs.
 * 
 * Essa função apaga os LEDs sequencialmente, com um intervalo de 3 segundos entre cada um.
 * Após apagar todos os LEDs, permite que o botão seja pressionado novamente.
 * 
 * @param alarm_id Identificador do alarme (não utilizado).
 * @param user_data Ponteiro para dados do usuário (não utilizado).
 * @return Retorna 0 para não reagendar automaticamente.
 */
int64_t turn_off_callback(alarm_id_t alarm_id, void *user_data) {
    if (led_status == 0) {
        gpio_put(RED_LED, 0);
        printf("LED vermelho apagado\n");

        // Avança para o próximo estado e agenda o próximo desligamento em 3 segundos
        led_status = 1;
        add_alarm_in_ms(3000, turn_off_callback, NULL, false);
    } else if (led_status == 1) {
        gpio_put(GREEN_LED, 0);
        printf("LED verde apagado\n");

        // Avança para o próximo estado e agenda o próximo desligamento em 3 segundos
        led_status = 2;
        add_alarm_in_ms(3000, turn_off_callback, NULL, false);
    } else if (led_status == 2) {
        gpio_put(BLUE_LED, 0);
        printf("LED azul apagado\n");

        // Retorna ao estado inicial e libera o botão para nova ativação
        led_status = 0;
        led_on = false;
        debounce_lock = false; // Libera o botão para nova ativação
    }
    return 0;
}

/**
 * @brief Função para verificar se o botão foi pressionado com debounce.
 * 
 * Essa função espera um tempo para estabilizar a leitura do botão, evitando múltiplas detecções 
 * durante uma única pressão.
 * 
 * @return true se o botão foi pressionado de forma válida, false caso contrário.
 */
bool button_pressed() {
    if (gpio_get(BUTTON_A) == 0 && !debounce_lock) { 
        sleep_ms(50); // Delay para evitar leitura incorreta (debounce)
        
        if (gpio_get(BUTTON_A) == 0) { // Confirma se o botão ainda está pressionado
            debounce_lock = true; // Bloqueia novas leituras até o ciclo terminar
            return true;
        }
    }
    return false;
}

/**
 * @brief Função principal do programa.
 * 
 * Inicializa os LEDs e o botão. Quando o botão é pressionado, acende os LEDs
 * e inicia um temporizador one-shot para apagá-los sequencialmente.
 */
int main() {
    // Inicializa a comunicação serial para debug via monitor serial
    stdio_init_all();

    // Configuração dos pinos dos LEDs como saída
    gpio_init(RED_LED);
    gpio_set_dir(RED_LED, GPIO_OUT);

    gpio_init(GREEN_LED);
    gpio_set_dir(GREEN_LED, GPIO_OUT);

    gpio_init(BLUE_LED);
    gpio_set_dir(BLUE_LED, GPIO_OUT);

    // Configuração do botão como entrada com pull-up interno ativado
    gpio_init(BUTTON_A);
    gpio_set_dir(BUTTON_A, GPIO_IN);
    gpio_pull_up(BUTTON_A);

    // Loop principal que monitora o botão
    while (true) {
        // Verifica se o botão foi pressionado e se os LEDs já apagaram completamente
        if (button_pressed() && !led_on) {
            // Acende todos os LEDs
            gpio_put(RED_LED, 1);
            gpio_put(GREEN_LED, 1);
            gpio_put(BLUE_LED, 1);

            printf("LEDs acesos!\n");

            // Marca que os LEDs estão acesos para evitar reativação prematura
            led_on = true;
            led_status = 0;

            // Inicia o temporizador one-shot para desligar os LEDs em sequência
            add_alarm_in_ms(3000, turn_off_callback, NULL, false);
        }
        sleep_ms(10); // Pequeno delay para evitar consumo excessivo da CPU
    }
}
