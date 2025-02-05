#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"

// Definição dos pinos dos LEDs RGB
#define RED_LED 13
#define GREEN_LED 11
#define BLUE_LED 12    

// Variável de estado para controlar qual LED será aceso
int led_status = 0;

/**
 * @brief Callback do temporizador periódico.
 * 
 * Essa função é chamada a cada intervalo de tempo definido no timer.
 * Ela alterna os LEDs de forma cíclica para simular um semáforo:
 * - Estado 0: LED Vermelho aceso
 * - Estado 1: LED Amarelo aceso (Vermelho + Verde)
 * - Estado 2: LED Verde aceso
 * 
 * @param t Ponteiro para a estrutura do timer (não utilizada no código).
 * @return true Sempre retorna verdadeiro para manter a execução do timer.
 */
bool repeating_timer_callback(struct repeating_timer *t) {
    // Desliga todos os LEDs antes de ativar o próximo estado
    gpio_put(RED_LED, 0);
    gpio_put(GREEN_LED, 0);
    gpio_put(BLUE_LED, 0);

    // Alterna os LEDs de acordo com o estado atual
    if (led_status == 0) { 
        printf("VERMELHO ACESO \n");
        gpio_put(RED_LED, 1); // Acende o LED vermelho
    } else if (led_status == 1) { 
        printf("AMARELO ACESO \n");
        gpio_put(RED_LED, 1);
        gpio_put(GREEN_LED, 1); // Acende o LED vermelho e verde (simulando amarelo)
    } else if (led_status == 2) { 
        printf("VERDE ACESO \n");
        gpio_put(GREEN_LED, 1); // Acende o LED verde
    }

    // Atualiza o estado do LED para o próximo ciclo
    led_status = (led_status + 1) % 3;

    // Retorna true para manter o temporizador ativo
    return true;
}

/**
 * @brief Função principal do programa.
 * 
 * Inicializa os LEDs e configura um temporizador periódico
 * para alternar os estados dos LEDs a cada 3 segundos.
 */
int main() {
    int temp = 0;

    // Inicializa a comunicação serial para debug via monitor serial
    stdio_init_all();

    // Configuração dos pinos dos LEDs como saída
    gpio_init(RED_LED);
    gpio_set_dir(RED_LED, true);

    gpio_init(GREEN_LED);
    gpio_set_dir(GREEN_LED, true);

    gpio_init(BLUE_LED);
    gpio_set_dir(BLUE_LED, true);

    // Declaração do temporizador periódico
    struct repeating_timer timer;

    // Configura o temporizador para chamar a função repeating_timer_callback a cada 3000 ms (3 segundos)
    add_repeating_timer_ms(3000, repeating_timer_callback, NULL, &timer);

    // Loop infinito para manter o programa em execução
    while (true) {
        sleep_ms(1000); // Aguarda 1 segundo
        printf("%ds\n", temp); // Exibe o tempo decorrido no monitor serial
        temp++; // Incrementa a variável de tempo
    }
}
