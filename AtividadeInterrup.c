#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

// Definição dos pinos dos LEDs RGB e botões
#define LED_G_PIN 11
#define LED_B_PIN 12
#define LED_R_PIN 13

#define BUTTON_A_PIN 5
#define BUTTON_B_PIN 6

#define MATRIZ_LEDS_BASE_PIN 7 // Pino da matriz de LEDs
#define NUM_PIXELS 25 // Número de LEDs na matriz

static volatile int numero_atual = 0; // Número exibido na matriz de LEDs
static uint32_t last_interrupt_time_a = 0;
static uint32_t last_interrupt_time_b = 0;

// Função para inicializar os LEDs e botões
void inicializacaocomponentes() {
    gpio_init(LED_G_PIN);
    gpio_set_dir(LED_G_PIN, GPIO_OUT);
    gpio_put(LED_G_PIN, 0);

    gpio_init(LED_B_PIN);
    gpio_set_dir(LED_B_PIN, GPIO_OUT);
    gpio_put(LED_B_PIN, 0);

    gpio_init(LED_R_PIN);
    gpio_set_dir(LED_R_PIN, GPIO_OUT);
    gpio_put(LED_R_PIN, 0);

    gpio_init(BUTTON_A_PIN);
    gpio_set_dir(BUTTON_A_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_A_PIN);

    gpio_init(BUTTON_B_PIN);
    gpio_set_dir(BUTTON_B_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_B_PIN);

    for (int i = 0; i < NUM_PIXELS; i++) {
        gpio_init(MATRIZ_LEDS_BASE_PIN + i);
        gpio_set_dir(MATRIZ_LEDS_BASE_PIN + i, GPIO_OUT);
        gpio_put(MATRIZ_LEDS_BASE_PIN + i, 0);
    }
}

// Função que fará o LED vermelho piscar 5 vezes por segundo
void blink_red() {
    gpio_put(LED_R_PIN, 1);
    sleep_ms(100);
    gpio_put(LED_R_PIN, 0);
    sleep_ms(100);
}

// Definição dos números na matriz de leds 
double numeros[10][25] = {
    {0.0, 0.3, 0.3, 0.3, 0.0,  // Número 0
     0.0, 0.0, 0.0, 0.3, 0.0,
     0.0, 0.0, 0.0, 0.3, 0.0,
     0.0, 0.0, 0.0, 0.3, 0.0,
     0.0, 0.3, 0.3, 0.3, 0.0},

    {0.0, 0.0, 0.3, 0.0, 0.0,  // Número 1
     0.0, 0.3, 0.0, 0.0, 0.0,
     0.0, 0.3, 0.0, 0.0, 0.0,
     0.0, 0.3, 0.0, 0.0, 0.0,
     0.0, 0.3, 0.0, 0.0, 0.0},

    {0.0, 0.3, 0.3, 0.3, 0.0,  // Número 2
     0.0, 0.0, 0.0, 0.3, 0.0,
     0.0, 0.0, 0.3, 0.0, 0.0,
     0.0, 0.3, 0.0, 0.0, 0.0,
     0.3, 0.3, 0.3, 0.3, 0.3},

    {0.0, 0.3, 0.3, 0.3, 0.0,  // Número 3
     0.0, 0.0, 0.0, 0.3, 0.0,
     0.0, 0.0, 0.3, 0.0, 0.0,
     0.0, 0.0, 0.0, 0.3, 0.0,
     0.0, 0.3, 0.3, 0.3, 0.0},

    {0.0, 0.0, 0.3, 0.0, 0.0,  // Número 4
     0.0, 0.3, 0.0, 0.0, 0.0,
     0.0, 0.3, 0.0, 0.0, 0.0,
     0.3, 0.3, 0.3, 0.3, 0.0,
     0.0, 0.0, 0.0, 0.0, 0.0},

    {0.3, 0.3, 0.3, 0.3, 0.0,  // Número 5
     0.3, 0.0, 0.0, 0.0, 0.0,
     0.3, 0.0, 0.3, 0.3, 0.0,
     0.0, 0.0, 0.0, 0.3, 0.0,
     0.0, 0.3, 0.3, 0.3, 0.0},

    {0.0, 0.3, 0.3, 0.3, 0.0,  // Número 6
     0.3, 0.0, 0.0, 0.0, 0.0,
     0.3, 0.0, 0.3, 0.3, 0.0,
     0.0, 0.3, 0.0, 0.3, 0.0,
     0.0, 0.3, 0.3, 0.3, 0.0},

    {0.3, 0.3, 0.3, 0.0, 0.0,  // Número 7
     0.0, 0.0, 0.3, 0.0, 0.0,
     0.0, 0.0, 0.3, 0.0, 0.0,
     0.0, 0.0, 0.3, 0.0, 0.0,
     0.0, 0.0, 0.3, 0.0, 0.0},

    {0.0, 0.3, 0.3, 0.3, 0.0,  // Número 8
     0.0, 0.3, 0.0, 0.3, 0.0,
     0.0, 0.3, 0.3, 0.3, 0.0,
     0.0, 0.3, 0.0, 0.3, 0.0,
     0.0, 0.3, 0.3, 0.3, 0.0},

    {0.0, 0.3, 0.3, 0.3, 0.0,  // Número 9
     0.0, 0.3, 0.0, 0.3, 0.0,
     0.0, 0.3, 0.3, 0.3, 0.0,
     0.0, 0.0, 0.0, 0.3, 0.0,
     0.0, 0.3, 0.3, 0.3, 0.0}
};

// Função para exibir o número na matriz de LEDs
void exibir_numero(double *desenho) {
    for (int i = 0; i < NUM_PIXELS; i++) {
        gpio_put(MATRIZ_LEDS_BASE_PIN + i, desenho[i] > 0 ? 1 : 0);
    }
}

// Função de interrupção com debouncing
void gpio_irq_handler(uint gpio, uint32_t events) {
    uint32_t interrupt_time = to_ms_since_boot(get_absolute_time());

    if (gpio == BUTTON_A_PIN && gpio_get(BUTTON_A_PIN) == 0) {
        if (interrupt_time - last_interrupt_time_a > 200) {
            numero_atual = (numero_atual + 1) % 10; 
        }
        last_interrupt_time_a = interrupt_time;
    }

    if (gpio == BUTTON_B_PIN && gpio_get(BUTTON_B_PIN) == 0) {
        if (interrupt_time - last_interrupt_time_b > 200) {
            numero_atual = (numero_atual - 1 + 10) % 10; 
        }
        last_interrupt_time_b = interrupt_time;
    }
}

// Função principal
int main() {

    stdio_init_all();
    inicializacaocomponentes();

    gpio_set_irq_enabled_with_callback(BUTTON_A_PIN, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);
    gpio_set_irq_enabled_with_callback(BUTTON_B_PIN, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);

    while (true) {
        blink_red();
        exibir_numero(numeros[numero_atual]); // Exibindo número
    }

    return 0;
}